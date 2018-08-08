//
// Created by ivoako-5 on 3/19/18.
//

#include "Skinning.h"
#include <fcntl.h>
#include <zconf.h>
#include <iostream>
#include <assert.h>
#include <config.h>
#include <cstring>
#include "DDS_TYPES.h"

#if !defined(MAKEFOURCC)
#define MAKEFOURCC(ch0, ch1, ch2, ch3)\
    (uint(uint8(ch0)) | (uint(uint8(ch1)) << 8) | \
    (uint(uint8(ch2)) << 16) | (uint(uint8(ch3)) << 24 ))
#endif

Skinning::Skinning()
{
}

Skinning::~Skinning()
{
    delete[] indexBuf;
    delete[] vertexBuf;
    munmap(beginning, fileSize);
}

void Skinning::setupSkin(const char *fileName, const char *diffuse, const char *specular, const char *normal, Skeleton* skel)
{
    readHeadData(fileName);
    setupVertex();
    setupVertexBuffer();
    setupIndexBuffer();
    loadDDS(diffuse, skel, 0);
    loadDDS(specular, skel, 1);
    loadDDS(normal, skel, 2);
}

void Skinning::readHeadData(const char *fileName)
{
    struct stat st;
    stat(fileName, &st);
    this->fileSize = st.st_size;

    int file = open(fileName, O_RDONLY);

    if(file == -1)
    {
        perror("Could not open file");
    }

    //load the file
    void* ptr = mmap(NULL, this->fileSize, PROT_READ, MAP_PRIVATE, file, 0);
    this->beginning = ptr;

    if(ptr == MAP_FAILED)
    {
        perror("Shit's fucked...");
    }
    assert(0 != ptr);

    Nvx2Header* head = (Nvx2Header*) ptr;

    //check magic
    if(head->magic != 'NVX2')
    {
        perror("Nothing was found >:(");
    }

    this->numGroups = head->numGroups;
    this->numVertices = head->numVertices;
    this->vertexWidth = head->vertexWidth;
    this->numIndices = head->numIndices * 3;
    this->numEdges = head->numEdges;
    this->vertexComponentMask = head->vertexComponentMask;

    this->groupDataSize = 6 * sizeof(unsigned int) * this->numGroups;
    this->vertexDataSize = this->numVertices * this->vertexWidth * sizeof(float);
    this->indexDataSize = this->numIndices * sizeof(int);

    this->groupDataPtr = head + 1;
    this->vertexDataPtr = ((unsigned char*)this->groupDataPtr) + this->groupDataSize;
    this->indexDataPtr = ((unsigned char*)this->vertexDataPtr) + this->vertexDataSize;

    readPrimitive();

    close(file);
}

void Skinning::readPrimitive()
{
    assert(this->numGroups > 0);
    assert(0 != this->groupDataPtr);
    Nvx2Group* group = (Nvx2Group*) this->groupDataPtr;

    for(int i = 0; i < size_t(this->numGroups); i++)
    {
        PrimitiveGroup pg;
        pg.numVertices = group->numVertices;
        pg.baseIndex = group->firstTriangle * 3;
        pg.numIndices = group->numTriangles * 3;
        primitive.push_back(pg);
        group++;
    }
}

void Skinning::setupVertex()
{
    for(int i = 0; i < N2NumVertexComponents; i++)
    {
        VertexComponent::SemanticName sn;
        VertexComponent::Format format;

        int index = 0;

        if(vertexComponentMask & (1<<i))
        {
            switch (1<<i)
            {
                case N2Coord: //In use
                    sn = VertexComponent::Position;
                    format = VertexComponent::Float3;
                    break;

                case N2Normal:
                    sn = VertexComponent::Normal;
                    format = VertexComponent::Float3;
                    break;

                case N2NormalB4N: //In use
                    sn = VertexComponent::Normal;
                    format = VertexComponent::Byte4N;
                    break;

                case N2Uv0: //In use
                    sn = VertexComponent::TexCoord1;
                    format = VertexComponent::Float2;
                    index = 0;
                    break;

                case N2Uv0S2:
                    sn = VertexComponent::TexCoord1;
                    format = VertexComponent::Short2;
                    index = 0;
                    break;

                case N2Uv1:
                    sn = VertexComponent::TexCoord2;
                    format = VertexComponent::Float2;
                    index = 1;
                    break;

                case N2Uv1S2:
                    sn = VertexComponent::TexCoord2;
                    format = VertexComponent::Short2;
                    index = 1;
                    break;

                case N2Color:
                    sn = VertexComponent::Color;
                    format = VertexComponent::Float4;
                    break;

                case N2ColorUB4N:
                    sn = VertexComponent::Color;
                    format = VertexComponent::UByte4N;
                    break;

                case N2Tangent:
                    sn = VertexComponent::Tangent;
                    format = VertexComponent::Float3;
                    break;

                case N2TangentB4N: //In use
                    sn = VertexComponent::Tangent;
                    format = VertexComponent::Byte4N;
                    break;

                case N2Binormal:
                    sn = VertexComponent::Binormal;
                    format = VertexComponent::Float3;
                    break;

                case N2BinormalB4N: //In use
                    sn = VertexComponent::Binormal;
                    format = VertexComponent::Byte4N;
                    break;

                case N2Weights:
                    sn = VertexComponent::SkinWeights;
                    format = VertexComponent::Float4;
                    break;

                case N2WeightsUB4N: //In use
                    sn = VertexComponent::SkinWeights;
                    format = VertexComponent::UByte4N;
                    break;

                case N2JIndices:
                    sn = VertexComponent::SkinJIndices;
                    format = VertexComponent::Float4;
                    break;

                case N2JIndicesUB4: //In use
                    sn = VertexComponent::SkinJIndices;
                    format = VertexComponent::UByte4;
                    break;

                default:
                    std::cout << "Invalid VertexComponent! Default used!"<< std::endl;
                    sn = VertexComponent::Position;
                    format = VertexComponent::Float3;
                    break;
            }
            this->vertexComponents.push_back(VertexComponent(sn, index, format));
        }
    }
}

void Skinning::setupVertexBuffer()
{
    this->vertexBuf = new SkinVertex[this->numVertices];
    this->orgVertexBuf = new SkinVertex[this->numVertices];

    for(int i = 0; i < this->numVertices; i++)
    {
        SkinVertex vertex;
        for(int j = 0; j < this->vertexComponents.size(); j++)
        {
            float x = 0, y = 0, z = 0, w = 0;

            switch(this->vertexComponents[j].semName)
            {
                case VertexComponent::Position:
                    tempVert* pos ;
                    pos = (tempVert*)vertexDataPtr;
                    vertex.pos = Vector4D(pos->x, pos->y, pos->z);
                    this->vertexDataPtr += sizeof(float)*3;
                    break;

                case VertexComponent::Normal:
                    char* normal;
                    normal = (char*)vertexDataPtr;
                    x = (float)normal[0];
                    y = (float)normal[1];
                    z = (float)normal[2];
                    w = (float)normal[3];
                    vertex.normal = Vector4D(x, y, z, w);
                    this->vertexDataPtr += sizeof(signed char)*4;
                    break;

                case VertexComponent::TexCoord1:
                    tempVert* uv;
                    uv = (tempVert*)vertexDataPtr;
                    vertex.uv = Vector4D(uv->x, uv->y, 0);
                    this->vertexDataPtr += sizeof(float)*2;
                    break;

                case VertexComponent::Tangent:
                    char* tan;
                    tan = (char*)vertexDataPtr;
                    x = (float)tan[0];
                    y = (float)tan[1];
                    z = (float)tan[2];
                    w = (float)tan[3];
                    vertex.tangent = Vector4D(x, y, z, w);
                    this->vertexDataPtr += sizeof(unsigned char)*4;
                    break;

                case VertexComponent::Binormal:
                    char* bi;
                    bi = (char*)vertexDataPtr;
                    x = (float)bi[0];
                    y = (float)bi[1];
                    z = (float)bi[2];
                    w = (float)bi[3];
                    vertex.biNormal = Vector4D(x, y, z, w);
                    this->vertexDataPtr += sizeof(signed char)*4;
                    break;

                case VertexComponent::SkinWeights:
                    unsigned char* sw;
                    sw = (unsigned char*)vertexDataPtr;
                    x = (float)sw[0];
                    y = (float)sw[1];
                    z = (float)sw[2];
                    w = (float)sw[3];
                    vertex.skinWeight = Vector4D(x, y, z, w);
                    vertex.skinWeight = vertex.skinWeight * (1.0f/(vertex.skinWeight.dot(Vector4D(1.0f, 1.0f, 1.0f, 1.0f))));
                    this->vertexDataPtr += sizeof(unsigned char)*4;
                    break;

                case VertexComponent::SkinJIndices:
                    unsigned char* si;
                    si = (unsigned char*)vertexDataPtr;
                    x = (float)si[0];
                    y = (float)si[1];
                    z = (float)si[2];
                    w = (float)si[3];
                    vertex.indice = Vector4D(x, y, z, w);
                    this->vertexDataPtr += sizeof(unsigned char)*4;
                    break;
            }
        }
        this->vertexBuf[i] = vertex;
        this->orgVertexBuf[i] = vertex;
    }
}

void Skinning::setupIndexBuffer()
{
    this->indexBuf = new int[this->numIndices];
    for(int i = 0; i < this->numIndices; i++)
    {
        int* value = (int*)this->indexDataPtr;
        this->indexBuf[i] = *value;
        this->indexDataPtr += sizeof(int);
    }
}

void Skinning::setBuffers()
{
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, this->numVertices*sizeof(SkinVertex), this->vertexBuf, GL_STATIC_DRAW);

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32)*this->numIndices, this->indexBuf, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skinning::draw(Skeleton *skel)
{
    setBuffers();
    skel->convertJointsToArray();
    //skel->calculate();

    Matrix4D temp = skel->test;
    temp.transpose();
    skel->shader->modifyMat("rotation", &temp[0][0]);

    GLint pos = glGetUniformLocation(skel->shader->program, "skeleton");
    glUniformMatrix4fv(pos, 21, GL_TRUE, (float*)skel->mat);

    //bindToSkeleton(skel);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, NULL);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 4));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 8));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 12));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 16));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 20));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 28, (GLvoid*)(sizeof(float32) * 24));


    glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_INT, NULL);
    //glDrawArrays(GL_TRIANGLES, 0, this->numIndices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skinning::bindToSkeleton(Skeleton *skel)
{
    //skel->convertJointsToArray();
    skel->calculate();
    int arr[21] = {19, 18, 17, 0, 20, 15, 13, 1, 12, 9, 2, 10, 3, 11, 14, 16, 4, 5, 8, 6, 7};
    for(int i = 0; i < this->numVertices; i++)
    {
        Vector4D np;

        int first, second, third, fourth;
        first = arr[(int)this->orgVertexBuf[i].indice[0]];
        second = arr[(int)this->orgVertexBuf[i].indice[1]];
        third = arr[(int)this->orgVertexBuf[i].indice[2]];
        fourth = arr[(int)this->orgVertexBuf[i].indice[3]];


        Matrix4D m1 = skel->bindPose[first].transform.inverse() * skel->tempJoints[first].transform;
        Matrix4D m2 = skel->bindPose[second].transform.inverse() * skel->tempJoints[second].transform;
        Matrix4D m3 = skel->bindPose[third].transform.inverse() * skel->tempJoints[third].transform;
        Matrix4D m4 = skel->bindPose[fourth].transform.inverse() * skel->tempJoints[fourth].transform;

        m1.transpose();
        m2.transpose();
        m3.transpose();
        m4.transpose();

        m1 = m1 * this->orgVertexBuf[i].skinWeight[0];
        m2 = m2 * this->orgVertexBuf[i].skinWeight[1];
        m3 = m3 * this->orgVertexBuf[i].skinWeight[2];
        m4 = m4 * this->orgVertexBuf[i].skinWeight[3];
        m1 = m1 + m2 + m3 + m4;

        //m1.transpose();

        np = m1 * this->orgVertexBuf[i].pos;
        this->vertexBuf[i].pos = np * 0.2f;
    }
    setBuffers();
}

GLuint Skinning::loadDDS(const char *fileName, Skeleton *skel, int texType)
{
    struct stat st;
    stat(fileName, &st);
    this->fileSize = st.st_size;

    int fd = open(fileName, O_RDONLY);

    if(fd == -1)
    {
        perror("Could not open file");
    }

    void* ptr = mmap(NULL, this->fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    this->beginning = ptr;
    uint32* magic = (uint32*)ptr;
    ptr+= sizeof(uint32);
    DDS_HEADER* head = (DDS_HEADER*)ptr;
    ptr += sizeof(DDS_HEADER);

    int width = head->dwWidth;
    int height = head->dwHeight;
    int mipMapCount = head->dwMipMapCount;

    int fourCC = head->ddspf.dwFourCC;
    DXT10Header* dx10Head = nullptr;
    unsigned int format;

    GLint texRes;
    switch(fourCC)
    {
        case MAKEFOURCC('D', 'X', 'T', '1'):
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case MAKEFOURCC('D', 'X', 'T', '3'):
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case MAKEFOURCC('D', 'X', 'T', '5'):
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;

            glActiveTexture(GL_TEXTURE1);
            glGenTextures(1, &normalID);
            glBindTexture(GL_TEXTURE_2D, normalID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            texRes = glGetUniformLocation(skel->shader->program, "normalTex");
            glUniform1i(texRes, 1);

            break;
        case MAKEFOURCC('D', 'X', '1', '0'):
            dx10Head = (DXT10Header*) ptr;
            ptr += sizeof(DXT10Header);
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;

            if(texType == 0)
            {
                glActiveTexture(GL_TEXTURE0);
                glGenTextures(1, &diffuseID);
                glBindTexture(GL_TEXTURE_2D, diffuseID);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                texRes = glGetUniformLocation(skel->shader->program, "diffuseTex");
                glUniform1i(texRes, 0);

            }
            else
            {
                glActiveTexture(GL_TEXTURE1);
                glGenTextures(1, &specularID);
                glBindTexture(GL_TEXTURE_2D, specularID);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                texRes = glGetUniformLocation(skel->shader->program, "specTex");
                glUniform1i(texRes, 0);
            }
            break;
    }
    int offset = 0;
    glBindTexture(GL_TEXTURE_2D, texRes);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;

    for(unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,0 , size, ptr + offset);

        offset += size;
        width *= 0.5f;
        height *= 0.5f;

        if(width < 1) width = 1;
        if(height < 1) height = 1;
    }
}
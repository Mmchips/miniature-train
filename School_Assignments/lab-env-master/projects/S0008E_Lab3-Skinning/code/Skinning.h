//
// Created by ivoako-5 on 3/19/18.
//

#ifndef GSCEPT_LAB_ENV_SKINNING_H
#define GSCEPT_LAB_ENV_SKINNING_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <vector>
#include <GL/glew.h>
#include "MathLibrary.h"
#include "VertexComponent.h"
#include "Skeleton.h"

struct SkinVertex
{
    Vector4D pos;
    Vector4D uv;
    Vector4D normal;
    Vector4D tangent;
    Vector4D biNormal;
    Vector4D skinWeight;
    Vector4D indice;
};

struct tempVert
{
    float x, y, z;
};

struct Nvx2Header
{
    unsigned int magic;
    unsigned int numGroups;
    unsigned int numVertices;
    unsigned int vertexWidth;
    unsigned int numIndices;
    unsigned int numEdges;
    unsigned int vertexComponentMask;
};

struct Nvx2Group
{
    unsigned int firstVertex;
    unsigned int numVertices;
    unsigned int firstTriangle;
    unsigned int numTriangles;
    unsigned int firstEdge;
    unsigned int numEdges;
};

struct PrimitiveGroup
{
    unsigned int baseVert;
    size_t numVertices;
    int baseIndex;
    size_t numIndices;
};

class Skinning
{
public:
    Skinning();
    ~Skinning();

    void setupSkin(const char *fileName, const char *diffuse, const char *specular, const char *normal, Skeleton* skel);
    void readHeadData(const char* fileName);
    void readPrimitive();
    void setupVertex();
    void setupVertexBuffer();
    void setupIndexBuffer();
    void setBuffers();
    void draw(Skeleton* skel);
    void bindToSkeleton(Skeleton* skel);
    GLuint loadDDS(const char* fileName, Skeleton* skel, int texType);

protected:

    enum N2VertexComponent
    {
        N2Coord        = (1<<0),      // 3 floats
        N2Normal       = (1<<1),      // 3 floats
        N2NormalB4N    = (1<<2),      // 4 unsigned bytes, normalized
        N2Uv0          = (1<<3),      // 2 floats
        N2Uv0S2        = (1<<4),      // 2 shorts, 4.12 fixed point
        N2Uv1          = (1<<5),      // 2 floats
        N2Uv1S2        = (1<<6),      // 2 shorts, 4.12 fixed point
        N2Uv2          = (1<<7),      // 2 floats
        N2Uv2S2        = (1<<8),      // 2 shorts, 4.12 fixed point
        N2Uv3          = (1<<9),      // 2 floats
        N2Uv3S2        = (1<<10),     // 2 shorts, 4.12 fixed point
        N2Color        = (1<<11),     // 4 floats
        N2ColorUB4N    = (1<<12),     // 4 unsigned bytes, normalized
        N2Tangent      = (1<<13),     // 3 floats
        N2TangentB4N   = (1<<14),     // 4 unsigned bytes, normalized
        N2Binormal     = (1<<15),     // 3 floats
        N2BinormalB4N  = (1<<16),     // 4 unsigned bytes, normalized
        N2Weights      = (1<<17),     // 4 floats
        N2WeightsUB4N  = (1<<18),     // 4 unsigned bytes, normalized
        N2JIndices     = (1<<19),     // 4 floats
        N2JIndicesUB4  = (1<<20),     // 4 unsigned bytes

        N2NumVertexComponents = 21,
        N2AllComponents = ((1<<N2NumVertexComponents) - 1),
    };

    size_t fileSize;
    size_t groupDataSize;
    size_t vertexDataSize;
    size_t indexDataSize;

    void* beginning = nullptr;
    void* groupDataPtr = nullptr;
    void* vertexDataPtr = nullptr;
    void* indexDataPtr = nullptr;

    SkinVertex* vertexBuf = nullptr;
    SkinVertex* orgVertexBuf = nullptr;
    int* indexBuf = nullptr;
    GLuint vbo, ebo;

private:
    bool rawMode;

    unsigned int numGroups;
    unsigned int numVertices;
    unsigned int vertexWidth;
    unsigned int numIndices;
    unsigned int numEdges;
    unsigned int vertexComponentMask;
    std::vector<PrimitiveGroup> primitive;
    std::vector<VertexComponent> vertexComponents;
    Matrix4D* calcdMat;

    GLuint normalID;
    GLuint diffuseID;
    GLuint specularID;
};


#endif //GSCEPT_LAB_ENV_SKINNING_H

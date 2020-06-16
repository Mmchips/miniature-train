//
// Created by ivoako-5 on 10/31/17.
//

#include <cstring>
#include "config.h"
#include "MeshResource.h"

//Konstruktor som inte g�r n�got just nu
MeshResource::MeshResource()
{
}

//Dekonstruktor som inte g�r n�got just nu
MeshResource::~MeshResource()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &index_buffer);
}

MeshResource* MeshResource::loadOBJ(const char* filePath)
{
    MeshResource* mesh = new MeshResource;

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices, indices;
    std::vector<Vector4D> temp_vertices;
    std::vector<Vector2D> temp_uvs;
    std::vector<Vector4D> temp_normals;


    FILE* file = fopen(filePath, "r");
    if (file == NULL)
    {
        std::cout << "Unable to open file " << filePath << std::endl;
        return false;
    }

    while (true)
    {
        char lineHeader[128];
        int rest = fscanf(file, "%s", lineHeader);
        if (rest == EOF)
        {
            break;
        }

        if (strcmp(lineHeader, "v") == 0)
        {
            Vector4D vert;
            fscanf(file, "%f %f %f\n", &vert[0], &vert[1], &vert[2]);
            temp_vertices.push_back(vert);
        }

        else if (strcmp(lineHeader, "vt") == 0)
        {
            Vector2D uv;
            fscanf(file, "%f %f\n", &uv[0], &uv[1]);
            temp_uvs.push_back(uv);
        }

        else if (strcmp(lineHeader, "vn") == 0)
        {
            Vector4D normal;
            fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
            temp_normals.push_back(normal);
        }

        else if (strcmp(lineHeader, "f") == 0)
        {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
            if (matches == 9)
            {
                Vertex v1;
                Vertex v2;
                Vertex v3;

                v1.pos = temp_vertices[vertexIndex[0] - 1];
                v1.uv = temp_uvs[uvIndex[0] - 1];
                v1.norm = temp_normals[normalIndex[0] - 1];

                v2.pos = temp_vertices[vertexIndex[1] - 1];
                v2.uv = temp_uvs[uvIndex[1] - 1];
                v2.norm = temp_normals[normalIndex[1] - 1];

                v3.pos = temp_vertices[vertexIndex[2] - 1];
                v3.uv = temp_uvs[uvIndex[2] - 1];
                v3.norm = temp_normals[normalIndex[2] - 1];

                mesh->vertices.push_back(v1);
                indices.push_back(mesh->vertices.size() - 1);

                mesh->vertices.push_back(v2);
                indices.push_back(mesh->vertices.size() - 1);

                mesh->vertices.push_back(v3);
                indices.push_back(mesh->vertices.size() - 1);

            }
            else if (matches == 12)
            {
                Vertex v1;
                Vertex v2;
                Vertex v3;
                Vertex v4;

                v1.pos = temp_vertices[vertexIndex[0] - 1];
                v1.uv = temp_uvs[uvIndex[0] - 1];
                v1.norm = temp_normals[normalIndex[0] - 1];

                v2.pos = temp_vertices[vertexIndex[1] - 1];
                v2.uv = temp_uvs[uvIndex[1] - 1];
                v2.norm = temp_normals[normalIndex[1] - 1];

                v3.pos = temp_vertices[vertexIndex[2] - 1];
                v3.uv = temp_uvs[uvIndex[2] - 1];
                v3.norm = temp_normals[normalIndex[2] - 1];

                v4.pos = temp_vertices[vertexIndex[3] - 1];
                v4.uv = temp_uvs[uvIndex[3] - 1];
                v4.norm = temp_normals[normalIndex[3] - 1];

                mesh->vertices.push_back(v1);
                indices.push_back(mesh->vertices.size() - 1);

                mesh->vertices.push_back(v2);
                indices.push_back(mesh->vertices.size() - 1);

                mesh->vertices.push_back(v3);
                indices.push_back(mesh->vertices.size() - 1);

                mesh->vertices.push_back(v4);
                indices.push_back(mesh->vertices.size() - 1);
            }
            else
            {
                std::cout << "Unable to read " << filePath << std::endl;
                return false;
            }
        }
    }
    mesh->setupStruct(&mesh->vertices[0], mesh->vertices.size(), &indices[0], indices.size());

    for (int i = 0; i < mesh->vertices.size(); i++)
    {
        if (mesh->vertices[i].pos[0] > mesh->box.max[0])
        {
            mesh->box.max[0] = mesh->vertices[i].pos[0];
        }
        if (mesh->vertices[i].pos[1] > mesh->box.max[1])
        {
            mesh->box.max[1] = mesh->vertices[i].pos[1];
        }
        if (mesh->vertices[i].pos[2] > mesh->box.max[2])
        {
            mesh->box.max[2] = mesh->vertices[i].pos[2];
        }

        if (mesh->vertices[i].pos[0] < mesh->box.min[0])
        {
            mesh->box.min[0] = mesh->vertices[i].pos[0];
        }
        if (mesh->vertices[i].pos[1] < mesh->box.min[1])
        {
            mesh->box.min[1] = mesh->vertices[i].pos[1];
        }
        if (mesh->vertices[i].pos[2] < mesh->box.min[2])
        {
            mesh->box.min[2] = mesh->vertices[i].pos[2];
        }
    }

    mesh->box.obb[0] = Vector4D(mesh->box.min[0], mesh->box.min[1], mesh->box.min[2]);
    mesh->box.obb[1] = Vector4D(mesh->box.min[0], mesh->box.max[1], mesh->box.min[2]);
    mesh->box.obb[2] = Vector4D(mesh->box.max[0], mesh->box.max[1], mesh->box.min[2]);
    mesh->box.obb[3] = Vector4D(mesh->box.max[0], mesh->box.min[1], mesh->box.min[2]);

    mesh->box.obb[4] = Vector4D(mesh->box.min[0], mesh->box.min[1], mesh->box.max[2]);
    mesh->box.obb[5] = Vector4D(mesh->box.min[0], mesh->box.max[1], mesh->box.max[2]);
    mesh->box.obb[6] = Vector4D(mesh->box.max[0], mesh->box.max[1], mesh->box.max[2]);
    mesh->box.obb[7] = Vector4D(mesh->box.max[0], mesh->box.min[1], mesh->box.max[2]);

    return mesh;
}

void MeshResource::updateAABB(Matrix4D model)
{
    box.min = Vector4D(INFINITY, INFINITY, INFINITY);
    box.max = Vector4D(-INFINITY, -INFINITY, -INFINITY);

    std::vector<Vertex> copyVert;
    copyVert = vertices;

    for(int i = 0; i < copyVert.size(); i++)
    {
        copyVert[i].pos = model * copyVert[i].pos;

        if(copyVert[i].pos[0] > box.max[0])
        {
            box.max[0] = copyVert[i].pos[0];
        }
        if(copyVert[i].pos[1] > box.max[1])
        {
            box.max[1] = copyVert[i].pos[1];
        }
        if(copyVert[i].pos[2] > box.max[2])
        {
            box.max[2] = copyVert[i].pos[2];
        }

        if(copyVert[i].pos[0] < box.min[0])
        {
            box.min[0] = copyVert[i].pos[0];
        }
        if(copyVert[i].pos[1] < box.min[1])
        {
            box.min[1] = copyVert[i].pos[1];
        }
        if(copyVert[i].pos[2] < box.min[2])
        {
            box.min[2] = copyVert[i].pos[2];
        }
    }
}

void MeshResource::setupStruct(Vertex* vertbuf, int vertices, unsigned int* indices, unsigned int size)
{

    glGenBuffers(1, &vertex_buffer);                                                //Genererar en buffer med adressen till VBO
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);                                    //Binder buffern till grafikkortet, GL_ARRAY_BUFFER menas att buffern inneh�ller en array med vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices, vertbuf, GL_STATIC_DRAW);    //Fyller buffern med data fr�n v�ran buf-array
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &index_buffer);                                            //Genererar en buffer med adressen till EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);                        //Binder buffern till grafikortet, GL_ELEMENT_ARRAY_BUFFER menas att buffern inneh�ller indices till en vertice i en annan buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indices, GL_STATIC_DRAW); //Fyller buffern med data fr�n v�ran indices array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    count = size;
}

bool MeshResource::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);                                                            //aktiverar buffern
    glEnableVertexAttribArray(0);                                                                            //enablar v�ra vertexattributes hos shadern
    glEnableVertexAttribArray(1);                                                                            //enablar v�ra vertexattributes hos shadern
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);                                //definerar en array med attribut data. 3 betyder hur m�nga element som ska anv�ndas. Storleken av v�r struct vertex ger v�r offset NULL �r inneb�r att vi b�rjar fr�n b�rjan.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector4D)));        //samma som ovanst�ende men denna g�ng b�rjar vi efter 3:e elementet f�r att forts�tta d�r vi slutatde
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vector4D) * 2));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);                                                    //aktiverar min index buffer
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);    //renderar
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return true;
}

std::vector<MeshResource::Vertex> MeshResource::getVertBuf()
{
    return vertices;
}

AABB MeshResource::getAABB()
{
    return box;
}



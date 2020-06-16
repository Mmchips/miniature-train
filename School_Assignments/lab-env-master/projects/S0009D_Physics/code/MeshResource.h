//
// Created by ivoako-5 on 10/31/17.
//

#pragma once
#include "MathLibrary.h"
#include "Vector2D.hpp"
#include "GL/glew.h"

class MeshResource
{
public:
    MeshResource(); //Deklaration av konstruktor f�r meshes
    ~MeshResource(); //Deklaration av dekonstruktor f�r meshes

    struct Vertex
    {
        Vector4D pos;
        Vector2D uv;
        Vector4D norm;
    };

    AABB box;

    bool draw(); //Deklaration av draw-funktion f�r meshes
    void setupStruct(Vertex* vertbuf, int vertices, unsigned int* indices, unsigned int size);

    static MeshResource* loadOBJ(const char* filePath);

    std::vector<Vertex> getVertBuf();

    AABB getAABB();
    void updateAABB(Matrix4D model);

private:


    float width, height;
    Vector4D bottomLeft;
    GLuint vertex_buffer, index_buffer; //Vertex-, och index-buffers
    unsigned int count;
    Vertex* VertBuf;
    std::vector<Vertex> vertices;
    int* vertIndices, texIndices, normIndices;
};

//
// Created by ivoako-5 on 12/6/17.
//

#include "GraphicsNode.h"
#include "RigidBody.h"

class Cube
{
public:
    Cube();
    Cube(float width, float height, float depth);
    ~Cube();

    void updateCube(float dt);
    void updatePosition(float dt);
    void updateRotation(float dt);
    void updateCoM();
    void reset();

    Vector4D getFarthestPoint(Vector4D dir);

    GraphicsNode* node;
    RigidBody* rb;
    Vector4D CoM;
    Vector4D intersect;
    float width, height, depth;
};



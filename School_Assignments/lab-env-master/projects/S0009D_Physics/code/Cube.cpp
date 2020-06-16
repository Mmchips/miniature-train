//
// Created by ivoako-5 on 12/6/17.
//

#include "Cube.h"

Cube::Cube()
{
    this->width = 0;
    this->height = 0;
    this->depth = 0;
    this->rb = new RigidBody();
    this->node = new GraphicsNode();
}

Cube::Cube(float width, float height, float depth)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->rb = new RigidBody();
    this->node = new GraphicsNode();
}

Cube::~Cube()
{
    delete this->rb;
    delete this->node;
}

void Cube::updateCube(float dt) {
    rb->calcInertiaTensor(node->rotation);
    rb->calcAcceleration();
    updatePosition(dt);
    rb->calcVelocity(dt);
    rb->calcTorque(intersect, CoM);
    rb->calcAngularMomentum();
    rb->calcSpin();
    rb->calcRotation(node->rotation, dt);
    updateRotation(dt);

    updateCoM();
    rb->addForce(Vector4D());
}

void Cube::updatePosition(float dt)
{
    node->translation[0][3] = node->translation[0][3] + rb->velocity[0] * dt + (0.5f * rb->acceleration[0] * (dt * dt));
    node->translation[1][3] = node->translation[1][3] + rb->velocity[1] * dt + (0.5f * rb->acceleration[1] * (dt * dt));
    node->translation[2][3] = node->translation[2][3] + rb->velocity[2] * dt + (0.5f * rb->acceleration[2] * (dt * dt));
}

void Cube::updateRotation(float dt)
{
    node->rotation =  rb->dRot + (node->rotation*Matrix4D());
    node->rotation.gramSchmidtOrto();
}

void Cube::updateCoM()
{
    CoM[0] = node->origin[0] + width * 0.5f;
    CoM[1] = node->origin[1] + height * 0.5f;
    CoM[2] = node->origin[2] - depth * 0.5f;
}

void Cube::reset()
{
    node->clicked = false;
    rb->resting = true;
    rb->force = Vector4D();
    rb->acceleration = Vector4D();
    rb->velocity = Vector4D();
    rb->torque = Vector4D();
    rb->angularMomentum = Vector4D();
    rb->spin = Vector4D();
    rb->dRot = Matrix4D();
    node->rotation = Matrix4D();
    node->translation.setPosition(node->spawn);
}

Vector4D Cube::getFarthestPoint(Vector4D dir)
{
    float maxDot = -INFINITY;
    float tempDot = 0;
    Vector4D temp;
    Vector4D point;

    for(int i = 0; i < 8; i++)
    {
        temp = node->modelMat * node->getMesh()->box.obb[i];

        tempDot = temp.dot(dir);
        if(tempDot > maxDot)
        {
            maxDot = tempDot;
            point = temp;
        }
    }
    return point;
}
//
// Created by ivoako-5 on 12/6/17.
//

#include "RigidBody.h"

RigidBody::RigidBody()
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::setupCubeInertiaTensor(float width, float height, float depth)
{
    cubeInertiaTensor = Matrix4D(1.0f / 12.0f * mass * (height * height + depth * depth), 0, 0,
                             0, 1.0f / 12.0f * mass * (width * width + depth * depth), 0,
                             0, 0, 1.0f / 12.0f * mass * (width * width + height * height));
}

void RigidBody::calcInertiaTensor(Matrix4D modelMat)
{
    Matrix4D modelMatT = modelMat;
    modelMatT.transpose();
    inertiaTensor = modelMat * cubeInertiaTensor.inverse() * modelMatT;
}

void RigidBody::calcVelocity(float dt)
{
    velocity = velocity + acceleration * dt;
}

void RigidBody::calcAcceleration()
{
    acceleration = force / mass;
}

void RigidBody::calcTorque(Vector4D intersect, Vector4D CoM)
{
    Vector4D r = intersect - CoM;
    torque = r.cross(force);
}

void RigidBody::calcSpin()
{
    spin = inertiaTensor * angularMomentum;
    //spin.normalize();
    skew[0][0] = 0;
    skew[1][1] = 0;
    skew[2][2] = 0;

    skew[0][1] = -spin[2];
    skew[0][2] = spin[1];
    skew[1][2] = -spin[0];

    skew[1][0] = spin[2];
    skew[2][0] = -spin[1];
    skew[2][1] = spin[0];
}

void RigidBody::calcRotation(Matrix4D modelMat, float dt)
{
    dRot = (skew * modelMat) * (dt * 0.5f);
}

void RigidBody::calcAngularMomentum()
{
    angularMomentum = angularMomentum + torque;
}

void RigidBody::addForce(Vector4D force)
{
    this->force = force;
}
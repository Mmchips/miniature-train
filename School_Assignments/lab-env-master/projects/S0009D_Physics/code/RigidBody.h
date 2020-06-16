//
// Created by ivoako-5 on 12/6/17.
//

#include "MathLibrary.h"

class RigidBody
{
public:
    RigidBody();
    ~RigidBody();

    void setupCubeInertiaTensor(float width, float height, float depth);
    void calcInertiaTensor(Matrix4D modelMat);
    void calcVelocity(float dt);
    void calcAcceleration();
    void calcTorque(Vector4D intersect, Vector4D CoM);
    void calcAngularMomentum();
    void calcSpin();
    void calcRotation(Matrix4D modelMat, float dt);

    void addForce(Vector4D force);

    Matrix4D cubeInertiaTensor;
    Matrix4D inertiaTensor;
    Matrix4D inverseInertiaTensor;
    Matrix4D skew;
    Matrix4D dRot;

    Vector4D force;
    Vector4D acceleration;
    Vector4D velocity;
    Vector4D torque;
    Vector4D angularMomentum;
    Vector4D spin;

    float mass; // in kg

    bool resting = true;
};



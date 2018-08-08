//
// Created by ivoako-5 on 9/6/17.
//

#include <vector>
#include "tinyxml.h"
#include "MathLibrary.h"
#include "ShaderObject.h"
#include <GL/glut.h>


#ifndef GSCEPT_LAB_ENV_SKELETON_H
#define GSCEPT_LAB_ENV_SKELETON_H

struct Joint
{
    const char* name;
    int index, parent;
    Vector4D pos, scale;
    Matrix4D rot, transform;
    std::vector<Joint*> children;
};

class Skeleton
{
public:
    Skeleton();
    ~Skeleton();
    void loadSkel(const char *fileName);
    Vector4D ConvertString(std::string str);
    void setRotation(int joint, int axis, float deg);
    void setPosition(int axis, float val);
    void update();
    void calculateOrg();
    void calculate();
    void convertJointsToArray();

    void JointTransform(Joint*, Matrix4D);
    std::vector<Joint> joints;
    std::vector<Joint> tempJoints;
    std::vector<Joint> bindPose;

    float mat[21][16];
    ShaderObject* shader;
    Matrix4D test;

private:
};


#endif //GSCEPT_LAB_ENV_SKELETON_H

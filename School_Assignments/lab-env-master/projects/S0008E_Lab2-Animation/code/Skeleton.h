//
// Created by ivoako-5 on 9/6/17.
//

#include <vector>
#include "tinyxml.h"
#include "MathLibrary.h"
#include <GL/glut.h>

#ifndef GSCEPT_LAB_ENV_SKELETON_H
#define GSCEPT_LAB_ENV_SKELETON_H


class Skeleton
{
public:
    Skeleton();
    ~Skeleton();
    void loadFile(const char* fileName);
    Vector4D ConvertString(std::string str);
    void setRotation(int joint, int axis, float deg);
    void setPosition(int axis);
    void draw();
    void calculate();

    struct Joint
    {
        const char* name;
        int index, parent;
        Vector4D pos, scale;
        Matrix4D rot, translate;
        std::vector<Joint*> children;
    };

    void JointTransform(Joint*, Matrix4D);
    std::vector<Joint> Joints;
    std::vector<Joint> orgJoints;

private:
};


#endif //GSCEPT_LAB_ENV_SKELETON_H

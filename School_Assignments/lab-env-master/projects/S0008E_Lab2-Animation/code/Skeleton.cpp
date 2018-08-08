//
// Created by ivoako-5 on 9/6/17.
//

#include "Skeleton.h"
#include <stdlib.h>


Skeleton::Skeleton()
{

}

Skeleton::~Skeleton()
{

}

void Skeleton::JointTransform(Joint* joint, Matrix4D mat)
{
    joint->translate = joint->translate * mat;
    for(int i = 0; i < joint->children.size(); i++)
    {
        JointTransform(joint->children[i], joint->translate);
    }
}

Vector4D Skeleton::ConvertString(std::string str)
{
    std::stringstream input(str);
    std::string sgmnt;
    std::vector<std::string> sgmntlst;
    Vector4D tempVec;
    int i = 0;
    while (std::getline(input, sgmnt, ','))
    {
        sgmntlst.push_back(sgmnt);
        tempVec[i] = std::stof(sgmntlst[i]);
        i++;
    }
    return tempVec;
}

void Skeleton::loadFile(const char *fileName)
{
    TiXmlDocument doc(fileName);
    if(doc.LoadFile())
    {
        for (TiXmlElement* parent = doc.FirstChildElement("Nebula3")->FirstChildElement("Model")->FirstChildElement(
                "CharacterNodes")->FirstChildElement("CharacterNode")->FirstChildElement("Joint");
             parent != 0; parent = parent->NextSiblingElement())
        {

            Joint joint;
            joint.name   = parent->ToElement()->Attribute("name");
            joint.index  = atoi(parent->ToElement()->Attribute("index"));
            joint.parent = atoi(parent->ToElement()->Attribute("parent"));
            joint.pos    = ConvertString(parent->ToElement()->Attribute("position"));
            Vector4D temp = ConvertString(parent->ToElement()->Attribute("rotation"));
            joint.rot    = Matrix4D::QuatToMat(temp);
            joint.scale  = ConvertString(parent->ToElement()->Attribute("scale"));

            joint.translate = joint.rot;
            joint.translate[0][3] = joint.pos[0]*0.2;
            joint.translate[1][3] = joint.pos[1]*0.2;
            joint.translate[2][3] = joint.pos[2]*0.2;

            orgJoints.push_back(joint);

        }
    }

}

void Skeleton::calculate() {
    for (int i = 0; i < Joints.size(); i++) {
        if (Joints[i].parent == -1)
            continue;

        Joints[i].translate = (Joints[Joints[i].parent].translate) * Joints[i].translate;
    }
    for (int i = 0; i < Joints.size(); i++)
    {
        Joints[i].translate.transp();
    }
}

void Skeleton::draw()
{

    Joints = orgJoints;

    calculate();

    for (int i = 0; i < Joints.size(); i++)
    {
        if (i == 0)
        {
            glColor3f(255, 0, 0);
        }
        else
        {
            glColor3f(0, 0, 0);
        }


        glPushMatrix();
        glLoadMatrixf(Joints[i].translate.TransformFrom2DTo1D());
        glutWireSphere(0.02, 8, 8);
        glPopMatrix();

        if (Joints[i].parent > 0)
        {
            Joint parent = Joints[Joints[i].parent];

            glLineWidth(1);
            glColor3f(0, 0, 255);
            glBegin(GL_LINES);
            glVertex3f(Joints[i].translate[3][0], Joints[i].translate[3][1], Joints[i].translate[3][2]);
            glVertex3f(parent.translate[3][0], parent.translate[3][1], parent.translate[3][2]);
            glEnd();
        }
    }
}

void Skeleton::setRotation(int joint, int axis, float deg)
{
    Matrix4D mat;

    switch (axis)
    {
        case 0:
            mat = mat.rotateX(deg);
            break;
        case 1:
            mat = mat.rotateY(deg);
            break;
        case 2:
            mat = mat.rotateZ(deg);
            break;
    }
    mat.transp();
    orgJoints[joint].translate = orgJoints[joint].translate * mat;
}

void Skeleton::setPosition(int axis)
{
    switch (axis)
    {
        case 0:
            Joints[0].translate[3][0] = Joints[0].translate[3][0] + 0.05f;
            break;
        case 1:
            Joints[0].translate[3][1] = Joints[0].translate[3][1] + 0.05f;
            break;
        case 2:
            Joints[0].translate[3][0] = Joints[0].translate[3][0] - 0.05f;
            break;
        case 3:
            Joints[0].translate[3][1] = Joints[0].translate[3][1] - 0.05f;

    }
}

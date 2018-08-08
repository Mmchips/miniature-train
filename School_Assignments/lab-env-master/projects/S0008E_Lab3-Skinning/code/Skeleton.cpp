//
// Created by ivoako-5 on 9/6/17.
//

#include "Skeleton.h"

Skeleton::Skeleton()
{
    shader = new ShaderObject();
    shader->loadShader("vs.txt", "ps.txt");
}

Skeleton::~Skeleton()
{
    delete shader;
}

void Skeleton::JointTransform(Joint* joint, Matrix4D mat)
{
    joint->transform = joint->transform * mat;
    for(int i = 0; i < joint->children.size(); i++)
    {
        //JointTransform(joint->children[i], joint->transform);
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

void Skeleton::loadSkel(const char *fileName)
{
    TiXmlDocument doc(fileName);
    if(doc.LoadFile())
    {
        for (TiXmlElement* parent = doc.FirstChildElement("Nebula3")->FirstChildElement("Model")->FirstChildElement("CharacterNodes")->FirstChildElement("CharacterNode")->FirstChildElement("Joint");
             parent != 0; parent = parent->NextSiblingElement())
        {
            Joint joint;
            joint.name   = parent->ToElement()->Attribute("name");
            joint.index  = atoi(parent->ToElement()->Attribute("index"));
            joint.parent = atoi(parent->ToElement()->Attribute("parent"));
            joint.pos    = ConvertString(parent->ToElement()->Attribute("position"));
            Vector4D temp = ConvertString(parent->ToElement()->Attribute("rotation"));
            joint.transform = Matrix4D::QuatToMat(temp);
            joint.transform.transpose();
            joint.scale  = ConvertString(parent->ToElement()->Attribute("scale"));

            joint.transform.setPosition(joint.pos);;

            joints.push_back(joint);
        }
    }
    tempJoints = joints;
}

void Skeleton::calculateOrg()
{
    bindPose = joints;
    for (int i = 1; i < bindPose.size(); i++) {
        if (bindPose[i].parent == -1)
            continue;

        bindPose[i].transform = (bindPose[bindPose[i].parent].transform) * bindPose[i].transform;
    }
    for (int i = 0; i < bindPose.size(); i++)
    {
        bindPose[i].transform.transpose();
    }
}

void Skeleton::calculate()
{
    for (int i = 1; i < tempJoints.size(); i++) {
        if (tempJoints[i].parent == -1)
            continue;

        tempJoints[i].transform = (tempJoints[tempJoints[i].parent].transform) * tempJoints[i].transform;
    }
    for (int i = 0; i < tempJoints.size(); i++)
    {
        tempJoints[i].transform.transpose();
    }
}

void Convert(float arr[], Matrix4D &mat)
{
    arr[0] = mat[0][0];
    arr[1] = mat[0][1];
    arr[2] = mat[0][2];
    arr[3] = mat[0][3];

    arr[4] = mat[1][0];
    arr[5] = mat[1][1];
    arr[6] = mat[1][2];
    arr[7] = mat[1][3];

    arr[8] = mat[2][0];
    arr[9] = mat[2][1];
    arr[10] = mat[2][2];
    arr[11] = mat[2][3];

    arr[12] = mat[3][0];
    arr[13] = mat[3][1];
    arr[14] = mat[3][2];
    arr[15] = mat[3][3];
}

void Skeleton::convertJointsToArray()
{
    calculate();
    for(int i = 1; i < this->joints.size(); i++)
    {
        float arr[16];
        Matrix4D temp = this->bindPose[i].transform.inverse() * this->tempJoints[i].transform;
        temp.transpose();

        Convert(arr, temp);
        for(int j = 0; j < 16; j++)
        {
            mat[i][j] = arr[j];
        }
    }
}

void Skeleton::update()
{
    tempJoints = joints;


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
    mat.transpose();
    joints[joint].transform = joints[joint].transform * mat;
}

void Skeleton::setPosition(int axis, float val)
{
    switch (axis)
    {
        case 0:
            tempJoints[0].transform[3][0] = tempJoints[0].transform[3][0] + val;
            break;
        case 1:
            tempJoints[0].transform[3][1] = tempJoints[0].transform[3][1] + val;
            break;
        case 2:
            tempJoints[0].transform[3][2] = tempJoints[0].transform[3][2] + val;
            break;
    }
}

//
// Created by ivoako-5 on 9/19/17.
//

#include <sys/mman.h>
#include <vector>
#include "Skeleton.h"

#ifndef GSCEPT_LAB_ENV_ANIMLOADER_H
#define GSCEPT_LAB_ENV_ANIMLOADER_H

class Animation
{
public:
    struct Nax3Header
    {
        unsigned int magic;
        unsigned int numClips;
        unsigned int numKeys;
    };

    struct Nax3Clip
    {
        unsigned short numCurves;
        unsigned short startKeyIndex;
        unsigned short numKeys;
        unsigned short keyStride;
        unsigned short keyDuration;
        unsigned char preInfType;
        unsigned char postInfType;
        unsigned short numEvents;
        char name[50];
    };

    struct Nax3AnimEvent
    {
        char name[47];
        char category[15];
        unsigned short keyIndex;
    };

    struct Nax3Curve
    {
        unsigned int firstKeyIndex;
        unsigned char isActive;
        unsigned char isStatic;
        unsigned char curveType;
        unsigned char _padding;

        float staticKeyX;
        float staticKeyY;
        float staticKeyZ;
        float staticKeyW;
    };

    struct Nax3Group
    {
        Nax3Clip clip;
        Nax3Curve* curveList;
    };


    bool loadAnim(const char* filenName);
    void setupAnim(Skeleton* skel, int clipIndex);

private:

    Vector4D* keyArrPtr;
    Nax3Group* groupArrPtr;

    struct timeval startT, currT;

    int keyFrameIndex;
    bool startTSet = false;
};


#endif //GSCEPT_LAB_ENV_ANIMLOADER_H

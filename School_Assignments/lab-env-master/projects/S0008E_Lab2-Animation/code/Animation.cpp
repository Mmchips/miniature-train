//
// Created by ivoako-5 on 9/19/17.
//

#include <config.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "Animation.h"
#include <sys/time.h>

bool Animation::loadAnim(const char* fileName)
{
    struct stat st;
    stat(fileName, &st);
    size_t size = st.st_size;

    int fd = open(fileName, O_RDONLY);

    void* ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    void* start = ptr;

    if (ptr != (void*)-1)
    {
        Nax3Header* naxHead = (Nax3Header*) ptr;
        ptr += sizeof(Nax3Header);

        if(naxHead->numClips > 0)
        {
            groupArrPtr = new Nax3Group[naxHead->numClips];
            keyArrPtr = new Vector4D[naxHead->numKeys];

            size_t numClips = (size_t) naxHead->numClips;
            for (int clipIndex = 0; clipIndex < numClips; clipIndex++)
            {
                Nax3Clip *naxClip = (Nax3Clip *) ptr;
                ptr += sizeof(Nax3Clip);

                groupArrPtr[clipIndex].clip = *naxClip;

                for (int eventIndex = 0; eventIndex < naxClip->numEvents; eventIndex++)
                {
                    Nax3AnimEvent* naxEvent = (Nax3AnimEvent*)ptr;
                    ptr += sizeof(Nax3AnimEvent);
                }

                groupArrPtr[clipIndex].curveList = new Nax3Curve[naxClip->numCurves];
                for (int curveIndex = 0; curveIndex < naxClip->numCurves; curveIndex++)
                {
                    Nax3Curve* naxCurve = (Nax3Curve*)ptr;
                    ptr += sizeof(Nax3Curve);

                    groupArrPtr[clipIndex].curveList[curveIndex] = *naxCurve;
                }
            }

            size_t numKeys = (size_t)naxHead->numKeys;
            for (int keyIndex = 0; keyIndex < numKeys; keyIndex++)
            {
                Vector4D* key = (Vector4D*)ptr;
                ptr += sizeof(Vector4D);

                keyArrPtr[keyIndex] = *key;
            }
        }
        munmap(start, size);
        return true;
    }
    return false;
}

void Animation::setupAnim(Skeleton* skel, int clipIndex)
{
    Nax3Clip clip = groupArrPtr[clipIndex].clip;

    //set the startime
    if(!startTSet)
    {
        gettimeofday(&startT, NULL);
        startTSet = true;
    }

    gettimeofday(&currT, NULL);

    double elapsedTime = 0.000000000000001;//(currT.tv_sec - startT.tv_sec) * 1000.0f;   //seconds to milliseconds
    //elapsedTime += (currT.tv_usec - startT.tv_usec) / 1000.0f;  //microseconds to milliseconds


    double frameDuration = fmod(elapsedTime, (double)clip.keyDuration);

    if (frameDuration <= clip.keyDuration)
    {
        //Change keyframe
        if(keyFrameIndex >= clip.numKeys)
        {
            //if next keyframe would be out of range set keyFrameIndex to 0
            keyFrameIndex = 0;
        }
        else
        {
            keyFrameIndex += 1;
        }
        gettimeofday(&startT, NULL);
    }

    frameDuration = frameDuration/clip.keyDuration;

    for (int i=0, j=0; i<skel->orgJoints.size(); i++, j+=4)
    {
        //get the right curves for the joint
        Nax3Curve* posCurve = &groupArrPtr[clipIndex].curveList[j];
        Nax3Curve* rotCurve = &groupArrPtr[clipIndex].curveList[j+1];
        Nax3Curve* scaleCurve = &groupArrPtr[clipIndex].curveList[j+2];
        Nax3Curve* velCurve = &groupArrPtr[clipIndex].curveList[j+3];

        //get the right keys
        Vector4D pos = keyArrPtr[posCurve->firstKeyIndex+clip.keyStride*keyFrameIndex];
        Vector4D rot = keyArrPtr[rotCurve->firstKeyIndex+clip.keyStride*keyFrameIndex];
        Vector4D scale = keyArrPtr[scaleCurve->firstKeyIndex+clip.keyStride*keyFrameIndex];
        Vector4D vel = keyArrPtr[velCurve->firstKeyIndex+clip.keyStride*keyFrameIndex];

        Vector4D lerpPos = Vector4D::lerp(pos, keyArrPtr[posCurve->firstKeyIndex+clip.keyStride*(keyFrameIndex+1)], frameDuration);
        Vector4D slerpRot = Vector4D::slerp(rot, keyArrPtr[rotCurve->firstKeyIndex+clip.keyStride*(keyFrameIndex+1)], frameDuration);
        Vector4D lerpScale = Vector4D::lerp(scale, keyArrPtr[scaleCurve->firstKeyIndex+clip.keyStride*(keyFrameIndex+1)], frameDuration);
        Vector4D lerpVel = Vector4D::lerp(vel, keyArrPtr[velCurve->firstKeyIndex+clip.keyStride*(keyFrameIndex+1)], frameDuration);

        skel->orgJoints[i].rot = Matrix4D::QuatToMat(slerpRot);
        skel->orgJoints[i].rot.transp();
        skel->orgJoints[i].pos = lerpPos * 0.3f;
        skel->orgJoints[i].translate = skel->orgJoints[i].rot;

        skel->orgJoints[i].translate[3][0] = skel->orgJoints[i].pos[0];
        skel->orgJoints[i].translate[3][1] = skel->orgJoints[i].pos[1];
        skel->orgJoints[i].translate[3][2] = skel->orgJoints[i].pos[2];
        skel->orgJoints[i].translate.transp();
    }

}
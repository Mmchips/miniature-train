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

void Animation::updateAnimation(Skeleton *skel, int clipIndex, float dt)
{
    Nax3Clip clip = groupArrPtr[clipIndex].clip;
    time += dt;

    if (time > clip.keyDuration) {
        nextKeyFrame++;
        time = 0;
        //Change keyframe
    }
    if(nextKeyFrame >= clip.numKeys)
    {
        //if next keyframe would be out of range set keyFrameIndex to 0
       nextKeyFrame = 0;
    }

    keyFrameIndex = nextKeyFrame > 0 ? nextKeyFrame -1 : clip.numKeys-1;

    Vector4D curPosKey, curRotKey, nextPosKey, nextRotKey;

    float frameDuration = time/clip.keyDuration;

    for (int i=0; i<skel->joints.size(); i++)
    {
        int key = groupArrPtr[clipIndex].curveList[i*4].firstKeyIndex + keyFrameIndex * clip.keyStride;
        int nextKey = groupArrPtr[clipIndex].curveList[i*4].firstKeyIndex + clip.keyStride*nextKeyFrame;

        curPosKey = this->keyArrPtr[key];
        curRotKey = this->keyArrPtr[key+1];

        nextPosKey = this->keyArrPtr[nextKey];
        nextRotKey = this->keyArrPtr[nextKey+1];

        Vector4D curPos(curPosKey[0], curPosKey[1], curPosKey[2], 1);
        Vector4D curRot(curRotKey[0], curRotKey[1], curRotKey[2], curRotKey[3]);

        Vector4D nextPos(nextPosKey[0], nextPosKey[1], nextPosKey[2], 1);
        Vector4D nextRot(nextRotKey[0], nextRotKey[1], nextRotKey[2], nextRotKey[3]);

        Vector4D pos = Vector4D::lerp(curPos, nextPos, frameDuration);
        Vector4D rot = Vector4D::slerp(curRot, nextRot, frameDuration);

        Matrix4D rotMat;
        rotMat = Matrix4D::QuatToMat(rot);
        rotMat.transpose();
        rotMat.setPosition(pos);
        skel->tempJoints[i].transform = rotMat;
    }

}
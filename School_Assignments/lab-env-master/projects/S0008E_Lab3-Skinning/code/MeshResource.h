//
// Created by ivoako-5 on 10/3/17.
//

#ifndef GSCEPT_LAB_ENV_MESHRESOURCE_H
#define GSCEPT_LAB_ENV_MESHRESOURCE_H

#include <sys/mman.h>

class MeshResource
{
public:

    MeshResource();
    ~MeshResource();

    bool loadMesh(const char* fileName);

private:
};


#endif //GSCEPT_LAB_ENV_MESHRESOURCE_H

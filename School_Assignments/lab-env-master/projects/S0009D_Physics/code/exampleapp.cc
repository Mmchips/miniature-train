//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>

using namespace Display;
namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ExampleApp::ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
ExampleApp::Open()
{

	App::Open();
	this->window = new Display::Window;
    window->SetKeyPressFunction([this](int32 key, int32 scancode, int32 action, int32 mods)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                this->window->Close();
                break;
            case GLFW_KEY_W:
                if(action == GLFW_PRESS || action == GLFW_REPEAT)
                    camPos[2] -= 0.01f;
                    target[2] -= 0.01f;
                break;
            case GLFW_KEY_A:
                if(action == GLFW_PRESS || action == GLFW_REPEAT)
                    camPos[0] -= 0.01f;
                    target[0] -= 0.01f;
                break;
            case GLFW_KEY_S:
                if(action == GLFW_PRESS || action == GLFW_REPEAT)
                    camPos[2] += 0.01f;
                    target[2] += 0.01f;
                break;
            case GLFW_KEY_D:
                if(action == GLFW_PRESS || action == GLFW_REPEAT)
                    camPos[0] += 0.01f;
                    target[0] += 0.01f;
                break;
            case GLFW_KEY_SPACE:
                if(action == GLFW_PRESS || action == GLFW_REPEAT)
                    camPos[1] += 0.01f;
                    target[1] += 0.01f;
                break;
            case GLFW_KEY_LEFT_CONTROL:
                if(action == GLFW_PRESS || action == GLFW_REPEAT)
                    camPos[1] -= 0.01f;
                    target[1] -= 0.01f;
                break;
            case GLFW_KEY_R:
                if(action == GLFW_PRESS)
                    camPos = Vector4D(0.0f, 0.0f, 1.0f);
                    target = Vector4D(0.0f, 0.0f, 0.0f);
                    for(int i = 0; i < objLst.size(); i++)
                    {
                        objLst[i]->reset();
                    }
                break;
            case GLFW_KEY_Q:
                if(action == GLFW_PRESS)
                    camPos = Vector4D(1.0f, 0.0f, 1.0f);
                break;
            case GLFW_KEY_E:
                if(action == GLFW_PRESS)
                    camPos = Vector4D(-1.0f, 0.0f, 1.0f);
                break;
            case GLFW_KEY_Z:
                if(action == GLFW_PRESS)
                    camPos = Vector4D(0.0f, 0.5f, 1.0f);
                break;
            case GLFW_KEY_X:
                if(action == GLFW_PRESS)
                    camPos = Vector4D(0.0f, -0.5f, 1.0f);
                break;
        }
    });

    window->SetMousePressFunction([this](int32, int32 state, int32)
    {
        if (state == 1)
        {
            if(quadLst.size() > 0)
                clickQuad();
            if(objLst.size() > 0)
                clickCube();
        }

    });

    window->SetMouseMoveFunction([this](float64 xM, float64 yM)
    {
        //normalizes the mouse position so it ranges from -1 to 1
        normalizedX = (xM*2/window->GetWindowWidth())-1.0f;
        normalizedY = 1.0f-((yM*2/window->GetWindowHeight()));

    });

	if (this->window->Open())
	{

		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        //glFrontFace(GL_CCW);
        //glCullFace(GL_FRONT_AND_BACK);

        //camPos = Vector4D(0.0f, 0.0f, 1.0f);

        //Loads textures
		green = std::make_shared<TextureResource>();
        green->loadFromFile("Green.png");

        red = std::make_shared<TextureResource>();
        red->loadFromFile("Red.png");

        cat = std::make_shared<TextureResource>();
        cat->loadFromFile("AIK.png");

        rtl = std::make_shared<TextureResource>();
        rtl->loadFromFile("ride_the_lightning.jpg");

        SO = std::make_shared<ShaderObject>();
        SO->loadShader("vs.txt", "ps.txt");

        //loads meshes
        quad = std::shared_ptr<MeshResource>(MeshResource::loadOBJ("quad.obj"));
        cubeM = std::shared_ptr<MeshResource>(MeshResource::loadOBJ("cube.obj"));
        cubeM2 = std::shared_ptr<MeshResource>(MeshResource::loadOBJ("cube.obj"));
        gun = std::shared_ptr<MeshResource>(MeshResource::loadOBJ("KSR-29.obj"));

        //Setup graphicnodes
        cube = new Cube(1.0f, 1.0f, 1.0f);
        cube->node->setMesh(cubeM);
        cube->node->setZValue(-1.5f);
        cube->node->setShader(SO);
        cube->node->setTexture(green, cat);
        cube->node->setOrigin(cube->node->getMesh()->getVertBuf()[0].pos, cube->node->getMesh()->getVertBuf()[1].pos, cube->node->getMesh()->getVertBuf()[2].pos);
        cube->node->setSpawn(Vector4D(0,0,cube->node->zValue));
        cube->node->scale.setScale(Vector4D(0.25f,0.25f,0.25f));
        cube->rb->mass = 10.0f;
        cube->rb->setupCubeInertiaTensor(cube->width, cube->height, cube->depth);
        objLst.push_back(cube);

        cube1 = new Cube(1.0f, 1.0f, 1.0f);
        cube1->node->setMesh(cubeM2);
        cube1->node->setZValue(0.0f);
        cube1->node->setShader(SO);
        cube1->node->setTexture(red, rtl);
        cube1->node->setOrigin(cube1->node->getMesh()->getVertBuf()[0].pos, cube1->node->getMesh()->getVertBuf()[1].pos, cube1->node->getMesh()->getVertBuf()[2].pos);
        cube1->node->setSpawn(Vector4D(0,0,cube1->node->zValue));
        cube1->node->scale.setScale(Vector4D(0.25f,0.25f,0.25f));
        cube1->rb->mass = 10.0f;
        cube1->rb->setupCubeInertiaTensor(cube1->width, cube1->height, cube1->depth);
        objLst.push_back(cube1);


        SO->applyShader();
        light.setShader(SO);
        light.setDiffColour(Vector4D(0.1f, 0.1f, 0.1f));
        light.setSpecColour(Vector4D(1.0f, 1.0f, 1.0f));
        light.setLightPos(Vector4D(1.0f, 1.0f, 1.0f));
        light.generateLight();

        //generate view and projection matrices
        projection = Matrix4D::ProjectionMat(fov, near, far);

		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;

	while (this->window->IsOpen())
	{
        start = std::chrono::system_clock::now();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();

        view = Matrix4D::ViewMat(camPos, target, up);
        vp = projection * view;

        for(int i = 0; i < objLst.size(); i++)
        {
            objLst[i]->node->modelMat = objLst[i]->node->scale * objLst[i]->node->translation * objLst[i]->node->rotation;

            objLst[i]->node->getMesh()->updateAABB(objLst[i]->node->modelMat);
            objLst[i]->updateCube(0.05f);
            DrawAABB(objLst[i]->node->getAABB());

            objLst[i]->node->setTransform(vp*objLst[i]->node->modelMat);
            objLst[i]->node->draw(objLst[i]->node->clicked);
        }

        collisions = colHandler.checkCollisions(objLst);
        if(collisions.size() > 0)
        {
            for(std::set<std::pair<int,int>>::iterator it = collisions.begin(); it != collisions.end(); it++)
            {
                std::pair<int,int> pair = *it;

                if(objLst[pair.first]->rb->resting && objLst[pair.second]->rb->resting)
                {
                    break;
                }
                if(colHandler.GJK(*objLst[pair.first], *objLst[pair.second]))
                {
                    printf("Collision\n");
                    colInfo = colHandler.EPA(*objLst[pair.first], *objLst[pair.second]);
                    colHandler.calcImpulse(*objLst[pair.first], *objLst[pair.second], colInfo, dt, 1);
                }
            }
        }

        SO->modifyMat("rotMat", &vp[0][0]);
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex3f(lastOutVec2[0], lastOutVec2[1], lastOutVec2[2]);
        glEnd();

        end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end-start;
        dt = elapsed_seconds.count();

		this->window->SwapBuffers();
	}
}

void ExampleApp::clickQuad()
{
    hitQuadLst.clear();
    outVec = Vector4D();

    currDir = Vector4D(normalizedX, normalizedY, -1.0f);

    currDir = projection.inverse() * currDir;
    currDir[2] = -1.0f;
    currDir[3] = 0;
    currDir = view.inverse() * currDir;
    currDir = currDir.normalize();

    Ray ray(currDir, camPos);

    float nearZ = -10000000.0f;
    int nearestQuad = 0;
    for(int i = 0; i < quadLst.size(); i++)
    {
        if(ray.intersect(quadLst[i]->getPlane(), outVec))
        {
            Vector4D v0 = quadLst[i]->modelMat * quadLst[i]->getMesh()->getVertBuf()[0].pos;
            Vector4D v1 = quadLst[i]->modelMat * quadLst[i]->getMesh()->getVertBuf()[1].pos;
            Vector4D v2 = quadLst[i]->modelMat * quadLst[i]->getMesh()->getVertBuf()[4].pos;

            if(ray.pointInPlane(outVec, v0, v1, v2))
            {
                hitQuadLst.push_back(quadLst[i]);
                lastOutVec = outVec;
            }
        }
    }

    for (int i = 0; i < hitQuadLst.size(); i++)
    {
        if (hitQuadLst[i]->getPlane().getPoint()[2] > nearZ)
        {
            nearestQuad = i;
            nearZ = hitQuadLst[i]->getPlane().getPoint()[2];
        }
    }

    if(nearZ != -10000000.0f)
    {
        hitQuadLst[nearestQuad]->clicked = !hitQuadLst[nearestQuad]->clicked;
    }
}

void ExampleApp::clickCube()
{
    hitObjLst.clear();
    outVec2 = Vector4D();

    currDir = Vector4D(normalizedX, normalizedY, -1.0f);
    currDir = projection.inverse() * currDir;
    currDir[2] = -1.0f;
    currDir[3] = 0;
    currDir = view.inverse() * currDir;
    currDir = currDir.normalize();

    Ray ray(currDir, camPos);

    float nearZ = -INFINITY;
    float nearestObj = 0;

    for(int i = 0; i < objLst.size(); i++)
    {
        if(ray.intersectAABB(objLst[i]->node->getAABB(), outVec2))
        {
            hitObjLst.push_back(objLst[i]);
            lastOutVec2 = outVec2;
        }
    }
    for(int i = 0; i < hitObjLst.size(); i++)
    {
        if(hitObjLst[i]->node->getAABB().max[2] > nearZ)
        {
            nearestObj = i;
            nearZ = hitObjLst[i]->node->getAABB().max[2];
        }
    }
    if(nearZ !=-INFINITY)
    {
        hitObjLst[nearestObj]->node->clicked = !hitObjLst[nearestObj]->node->clicked;
        hitObjLst[nearestObj]->rb->resting = false;
        hitObjLst[nearestObj]->rb->addForce(currDir * 2.0f);
        hitObjLst[nearestObj]->intersect = outVec2;
    }
}

void ExampleApp::DrawAABB(AABB bBox)
{
    Vector4D tempMin = bBox.min;
    Vector4D tempMax = bBox.max;

    SO->modifyMat("rotMat", &vp[0][0]);
    glLineWidth(2);
    glBegin(GL_LINES);

    glVertex3f(tempMax[0], tempMax[1], tempMax[2]);
    glVertex3f(tempMax[0], tempMin[1], tempMax[2]);

    glVertex3f(tempMax[0], tempMin[1], tempMax[2]);
    glVertex3f(tempMin[0], tempMin[1], tempMax[2]);

    glVertex3f(tempMin[0], tempMin[1], tempMax[2]);
    glVertex3f(tempMin[0], tempMax[1], tempMax[2]);

    glVertex3f(tempMin[0], tempMax[1], tempMax[2]);
    glVertex3f(tempMax[0], tempMax[1], tempMax[2]);

    glVertex3f(tempMax[0], tempMax[1], tempMin[2]);
    glVertex3f(tempMax[0], tempMin[1], tempMin[2]);

    glVertex3f(tempMax[0], tempMin[1], tempMin[2]);
    glVertex3f(tempMin[0], tempMin[1], tempMin[2]);

    glVertex3f(tempMin[0], tempMin[1], tempMin[2]);
    glVertex3f(tempMin[0], tempMax[1], tempMin[2]);

    glVertex3f(tempMin[0], tempMax[1], tempMin[2]);
    glVertex3f(tempMax[0], tempMax[1], tempMin[2]);

    glVertex3f(tempMax[0], tempMax[1], tempMin[2]);
    glVertex3f(tempMax[0], tempMax[1], tempMax[2]);

    glVertex3f(tempMax[0], tempMin[1], tempMin[2]);
    glVertex3f(tempMax[0], tempMin[1], tempMax[2]);

    glVertex3f(tempMin[0], tempMin[1], tempMin[2]);
    glVertex3f(tempMin[0], tempMin[1], tempMax[2]);

    glVertex3f(tempMin[0], tempMax[1], tempMin[2]);
    glVertex3f(tempMin[0], tempMax[1], tempMax[2]);

    glEnd();

}
} // namespace Example
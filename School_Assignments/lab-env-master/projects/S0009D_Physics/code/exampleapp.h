#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2016 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include <memory>
#include "core/app.h"
#include "render/window.h"
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "LightNode.h"
//#include "Cube.h"
#include "CollisionHandler.h"
#include <chrono>

namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();

	/// open app
	bool Open();
	/// run app
	void Run();

    void clickQuad();
    void clickCube();
    void DrawAABB(AABB bBox);
private:

	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;
	Display::Window* window;

    std::shared_ptr<ShaderObject> SO;

    std::shared_ptr<MeshResource> quad;
    std::shared_ptr<MeshResource> cubeM;
    std::shared_ptr<MeshResource> cubeM2;
    std::shared_ptr<MeshResource> gun;

    std::shared_ptr<TextureResource> green;
    std::shared_ptr<TextureResource> red;
    std::shared_ptr<TextureResource> cat;
    std::shared_ptr<TextureResource> rtl;

    CollisionHandler colHandler;
    CollisionInfo colInfo;

    Cube* cube;
    Cube* cube1;

    LightNode light;

	Matrix4D projection;// = Matrix4D(90.0f, 0.01f, 100.0f);
	Matrix4D view;// = Matrix4D(Vector4D(0,0,1), Vector4D(0,0,0), Vector4D(0,1,0));
	Matrix4D vp;

    Vector4D outVec;
    Vector4D outVec2;
    Vector4D lastOutVec;
    Vector4D lastOutVec2;
    Vector4D currDir;
	Vector4D camPos = Vector4D(0, 0, 1.0f);
	Vector4D target = Vector4D(0.0f, 0.0f, 0.0f);
	Vector4D up = Vector4D(0.0f, 1.0f, 0.0f);

	float fov = 90.0f;
	float near = 0.1f;
	float far = -100.0f;

    float currentMousePosX = 0.0f;
    float currentMousePosY = 0.0f;
    float normalizedX = 0.0f;
    float normalizedY = 0.0f;

    float xinc = 0.0f;
    float yinc = 0.0f;
    float zinc = 0.0f;

    float dt = 0;

    std::vector<GraphicsNode*> quadLst;
    std::vector<GraphicsNode*> hitQuadLst;

    std::vector<Cube*> objLst;
    std::vector<Cube*> hitObjLst;

    std::set<std::pair<int,int>> collisions;

};
} // namespace Example
#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2016 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "MathLibrary.h"
#include "Skeleton.h"
#include "Animation.h"
#include "Skinning.h"
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
private:

	GLuint program;
	Display::Window* window;
    Skeleton* skel;
    Animation* animcontroller;
    Skinning* skin;

	Matrix4D finalRot;


    int animClip = 0;
    float xinc = 0.0f;
    float yinc = 0.0f;
    float angleX = 0.0f;
    float angleY = 0.0f;
    double lastMousePosX = 0.0f;
    double lastMousePosY = 0.0f;
    double currentMousePosX = 0.0f;
    double currentMousePosY = 0.0f;
    bool mousePressed = false;
    bool playAnim = false;
    float dt = 0.001;
};
} // namespace Example
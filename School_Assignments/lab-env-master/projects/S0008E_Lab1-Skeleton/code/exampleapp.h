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
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;
	Display::Window* window;
    Skeleton skel;

    double xinc = 0.0f;
    double yinc = 0.0f;
    double angleX = 0.0f;
    double angleY = 0.0f;
    double lastMousePosX = 0.0f;
    double lastMousePosY = 0.0f;
    double currentMousePosX = 0.0f;
    double currentMousePosY = 0.0f;
    bool mousePressed = false;
};
} // namespace Example
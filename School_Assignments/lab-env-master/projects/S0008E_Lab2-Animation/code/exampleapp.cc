//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>

const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec4 color;\n"
"layout(location=0) out vec4 Color;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(pos, 1);\n"
"	Color = color;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"layout(location=0) in vec4 color;\n"
"out vec4 Color;\n"
"void main()\n"
"{\n"
"	Color = color;\n"
"}\n";

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
            case GLFW_KEY_W:
                if (action == GLFW_PRESS || action == GLFW_REPEAT)
                {
                    yinc += 0.01f;
                }
                break;
            case GLFW_KEY_S:
                if (action == GLFW_PRESS || action == GLFW_REPEAT)
                {
                    yinc += -0.01f;
                }
                break;
            case GLFW_KEY_A:
                if (action == GLFW_PRESS || action == GLFW_REPEAT)
                {
                    xinc += -0.01f;
                }
                break;
            case GLFW_KEY_D:
                if (action == GLFW_PRESS|| action == GLFW_REPEAT)
                {
                    xinc += 0.01f;
                }
                break;
            case GLFW_KEY_1:
                if (action == GLFW_PRESS)
                {
                    animClip = 0;
                }
                break;
            case GLFW_KEY_2:
                if (action == GLFW_PRESS)
                {
                    animClip = 1;
                }
                break;
            case GLFW_KEY_3:
                if (action == GLFW_PRESS)
                {
                    animClip = 2;
                }
                break;
            case GLFW_KEY_4:
                if (action == GLFW_PRESS)
                {
                    animClip = 3;
                }
                break;
            case GLFW_KEY_5:
                if (action == GLFW_PRESS)
                {
                    animClip = 4;
                }
                break;
            case GLFW_KEY_6:
                if (action == GLFW_PRESS)
                {
                    animClip = 5;
                }
                break;
            case GLFW_KEY_7:
                if (action == GLFW_PRESS)
                {
                    animClip = 6;
                }
                break;
            case GLFW_KEY_8:
                if (action == GLFW_PRESS)
                {
                    animClip = 7;
                }
                break;
            case GLFW_KEY_ESCAPE:
                this->window->Close();
                break;
        }
    });

    window->SetMousePressFunction([this](int32, int32 state, int32)
    {
        if (state == 1)
        {
            this->mousePressed = true;
        }
        else
        {
            this->mousePressed = false;
        }
    });

    window->SetMouseMoveFunction([this](float64 yM, float64 xM)
    {
        this->lastMousePosX = this->currentMousePosX;
        this->lastMousePosY = this->currentMousePosY;
        this->currentMousePosX = xM;
        this->currentMousePosY = yM;
     });

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        skel.loadFile("Unit_Footman.constants");
        anim.loadAnim("Unit_Footman.nax3");

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
    Matrix4D mat;
    mat.transp();
	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();
        glMatrixMode(GL_MODELVIEW);

        skel.orgJoints[0].translate.set(0, 3, xinc);
        skel.orgJoints[0].translate.set(1, 3, yinc);

        skel.setRotation(0, 0, angleX*0.05f);
        skel.setRotation(0, 1, angleY*0.05f);

        anim.setupAnim(&skel, animClip);
        skel.draw();

		this->window->SwapBuffers();
	}
}

} // namespace Example
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
	delete skin;
	delete animcontroller;
	delete skel;
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
            case GLFW_KEY_SPACE:
                if(action == GLFW_PRESS)
                {
                    playAnim = !playAnim;
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

    window->SetMouseMoveFunction([this](float64 xM, float64 yM)
    {
        this->lastMousePosX = this->currentMousePosX;
        this->lastMousePosY = this->currentMousePosY;

        if(mousePressed)
        {
            angleX = currentMousePosX - lastMousePosX;
            angleY = currentMousePosY - lastMousePosY;

            //finalRot = finalRot * finalRot.rotateX(angleX * 0.05f) * finalRot.rotateY(angleY * 0.05f);
        }

        this->currentMousePosX = xM;
        this->currentMousePosY = yM;
     });

	if (this->window->Open())
	{
	    //glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        skel = new Skeleton();
        glUseProgram(skel->shader->program);
        skel->shader->applyShader();
        skel->loadSkel("Unit_Footman.constants");
        skel->calculateOrg();

        animcontroller = new Animation();
        animcontroller->loadAnim("Unit_Footman.nax3");

        skin = new Skinning();
        skin->setupSkin("Unit_Footman.nvx2", "Footman_Diffuse.dds", "Footman_Specular.dds", "Footman_Normal.dds", skel);

        finalRot = finalRot * finalRot.rotateY(180);

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

	while (this->window->IsOpen())
	{
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();

		skel->test = finalRot;

        if(playAnim)
            animcontroller->updateAnimation(skel, animClip, dt);
        skin->draw(skel);
        skel->update();
		this->window->SwapBuffers();

        end = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed_seconds = end-start;
        dt = elapsed_seconds.count() * 1000;
	}
}

} // namespace Example
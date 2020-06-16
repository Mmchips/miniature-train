#include "LightNode.h"

LightNode::LightNode()
{
}

LightNode::~LightNode()
{
}

void LightNode::setShader(std::shared_ptr<ShaderObject> s)
{
	shader = s;
}

void LightNode::setSpecColour(Vector4D vec)
{
	specColour = vec;
}

void LightNode::setSpecColour(int x, int y, int z)
{
	specColour[0] = x;
	specColour[1] = y;
	specColour[2] = z;
}

void LightNode::setDiffColour(Vector4D vec)
{
	diffColour = vec;
}
void LightNode::setDiffColour(int x, int y, int z)
{
	diffColour[0] = x;
	diffColour[1] = y;
	diffColour[2] = z;
}

void LightNode::setLightPos(Vector4D vec)
{
	lightPos = vec;
}

void LightNode::setLightPos(int x, int y, int z)
{
	lightPos[0] = x;
	lightPos[1] = y;
	lightPos[2] = z;
}

void LightNode::setIntensity(float i)
{
	intensity = i;
	specColour = specColour * intensity;
	diffColour = diffColour * intensity;
}

void LightNode::generateLight()
{
	shader->modifyVec("specColour", &specColour[0]);
	shader->modifyVec("diffuseColour", &diffColour[0]);
	shader->modifyVec("lightPos", &lightPos[0]);
}
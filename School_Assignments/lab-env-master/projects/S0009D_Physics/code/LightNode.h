#pragma once
#include <memory>
#include "ShaderObject.h"
#include "MathLibrary.h"

class LightNode
{
public:
	LightNode();
	~LightNode();
	
	void setShader(std::shared_ptr<ShaderObject> s);

	void setSpecColour(Vector4D vec);
	void setSpecColour(int x, int y, int z);

	void setDiffColour(Vector4D vec);
	void setDiffColour(int x, int y, int z);

	void setLightPos(Vector4D vec);
	void setLightPos(int x, int y, int z);

	void setIntensity(float i);
	void generateLight();

private:
	std::shared_ptr<ShaderObject> shader;
	Vector4D specColour;
	Vector4D diffColour;
	Vector4D lightPos;
	float intensity;
	
};
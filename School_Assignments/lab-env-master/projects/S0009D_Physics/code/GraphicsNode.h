#pragma once
#include <memory>
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "GL/glew.h"


using namespace std;

class GraphicsNode
{
public:
	GraphicsNode();
	~GraphicsNode();

	shared_ptr<MeshResource> getMesh();
	shared_ptr<TextureResource> getTexture();
	shared_ptr<ShaderObject> getShader();
	Matrix4D getTransform();
	Matrix4D getCamera();
	Plane getPlane();
	AABB getAABB();

	void setMesh(std::shared_ptr<MeshResource> m);
	void setTexture(std::shared_ptr<TextureResource> t, std::shared_ptr<TextureResource> t2);
	void setShader(std::shared_ptr<ShaderObject> s);
	void setTransform(Matrix4D temp);
	void setCamera(Matrix4D temp);
	void setPlane(Vector4D normal, Vector4D point);
	void setOrigin(Vector4D orig, Vector4D up, Vector4D right);
	void setZValue(float z);
	void setSpawn(Vector4D pos);

	void draw(bool clicked);

	bool clicked = false;
	bool hit = false;
	Vector4D origin;
	Vector4D spawn;
	float width, height;
	Matrix4D modelMat;
    Matrix4D rotation, translation, scale;
	float zValue;
private:
	shared_ptr<MeshResource> mesh;
	shared_ptr<TextureResource> texture;
	shared_ptr<TextureResource> texture2;
	shared_ptr<ShaderObject> shader;

	Plane plane;

	Matrix4D transform;
	Matrix4D cam;
};


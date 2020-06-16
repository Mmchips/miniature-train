#include "GraphicsNode.h"


GraphicsNode::GraphicsNode()
{
}


GraphicsNode::~GraphicsNode()
{
}

shared_ptr<MeshResource> GraphicsNode::getMesh()
{
	return mesh;
}

shared_ptr<TextureResource> GraphicsNode::getTexture()
{
	return texture;
}

shared_ptr<ShaderObject> GraphicsNode::getShader()
{
	return shader;
}

Matrix4D GraphicsNode::getTransform()
{
    return transform;
}

Matrix4D GraphicsNode::getCamera()
{
    return cam;
}

Plane GraphicsNode::getPlane()
{
    return plane;
}

AABB GraphicsNode::getAABB()
{
    return mesh->getAABB();
}

void GraphicsNode::setMesh(std::shared_ptr<MeshResource> m)
{
	mesh = m;
}

void GraphicsNode::setTexture(std::shared_ptr<TextureResource> t, std::shared_ptr<TextureResource> t2)
{
	texture = t;
    texture2 = t2;
}

void GraphicsNode::setShader(std::shared_ptr<ShaderObject> s)
{
	shader = s;
}

void GraphicsNode::setTransform(Matrix4D temp)
{
	transform = temp;
}

void GraphicsNode::setCamera(Matrix4D temp)
{
	cam = temp;
}

void GraphicsNode::setPlane(Vector4D normal, Vector4D point)
{
    plane = Plane(normal, point);
}

void GraphicsNode::setOrigin(Vector4D orig, Vector4D up, Vector4D right)
{
    origin = orig;
    height = fabsf(orig[1]-up[1]);
    width = fabsf(up[0]-right[0]);
}

void GraphicsNode::setZValue(float z)
{
    zValue = z;
}

void GraphicsNode::setSpawn(Vector4D pos)
{
    translation.setPosition(pos);
    spawn = pos;
}

void GraphicsNode::draw(bool clicked)
{
	shader->modifyMat("rotMat", &transform[0][0]);
	shader->modifyMat("normMat", &cam[0][0]);
	if(!clicked)
    {
        texture->bindTexture();
    }
    else
    {
        texture2->bindTexture();
    }
	mesh->draw();
}
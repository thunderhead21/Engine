#include "RigidBody.h"

RigidBody::RigidBody() : Entity()
{
	_name = "RigidBody";
	this->layers = Layers::Physics | Layers::Renderable;
}

RigidBody::RigidBody(Mesh mesh): Entity(mesh)
{
	_name = "RigidBody";
	this->layers = Layers::Physics | Layers::Renderable;
}




/////////////////FACTORIES/////////////////
RigidBody* RigidBody::Cube(float side)
{

	RigidBody* body = new RigidBody(Cube::Cube(side));


	body->_name = "Cube";
	return body;

}

RigidBody* RigidBody::Rectangle(float width, float height)
{
	RigidBody* body = new RigidBody(Rectangle::Rectangle(width, height));

	body->_name = "Rectangle";
	return body;
}

RigidBody* RigidBody::Triangle(float width, float height)
{
	RigidBody* body = new RigidBody(Triangle::Triangle(width, height));

	body->_name = "Triangle";
	return body;
}
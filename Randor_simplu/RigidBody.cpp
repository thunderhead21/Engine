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
RigidBody RigidBody::Cube(float side)
{

	RigidBody cube(Cube::Cube(side));


	cube._name = "Cube";
	return cube;


}

RigidBody RigidBody::Rectangle(float width, float height)
{
	RigidBody rectangle(Rectangle::Rectangle(width, height));

	rectangle._name = "Rectangle";
	return rectangle;
}

RigidBody RigidBody::Triangle(float width, float height)
{
	RigidBody triangle(Triangle::Triangle(width, height));

	triangle._name = "Triangle";
	return triangle;
}
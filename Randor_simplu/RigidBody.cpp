#include "RigidBody.h"

RigidBody::RigidBody() : Entity()
{
	name = "RigidBody";
	this->layers = Layers::Physics | Layers::Renderable;
}

RigidBody::RigidBody(Mesh mesh): Entity(mesh)
{
	name = "RigidBody";
	this->layers = Layers::Physics | Layers::Renderable;
}




/////////////////FACTORIES/////////////////
RigidBody RigidBody::Cube(float side)
{

	RigidBody cube(Cube::Cube(side));


	cube.name = "Cube";
	return cube;


}

RigidBody RigidBody::Rectangle(float width, float height)
{
	RigidBody rectangle(Rectangle::Rectangle(width, height));

	rectangle.name = "Rectangle";
	return rectangle;
}

RigidBody RigidBody::Triangle(float width, float height)
{
	RigidBody triangle(Triangle::Triangle(width, height));

	triangle.name = "Triangle";
	return triangle;
}
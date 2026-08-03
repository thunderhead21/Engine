#include "Entity.h"

/*
DO NOT DO THIS
Mesh vertices are stored in LOCAL SPACE.

    The renderer computes:

        worldVertex = Entity::Transform * localVertex

    every frame.

    Modifying the mesh destroys its canonical mesh and prevents:
        - instancing
        - shared meshes
        - stable transforms
        - animation
        - correct scaling/rotation

    Transform the vertex during rendering, never the mesh itself.
void Entity::apply_transform()
{
	for (auto& i : mesh) {		//Each triangle
		for (auto& vertex : i) {	//Each point
			auto tmp = transform.matrix() * vertex;

			vertex.x = tmp.x;
			vertex.y = tmp.y;
			vertex.z = tmp.z;


		}
	}
}
*/



bool Entity::toggle_visibility() noexcept
{
	visible = (!visible);
	return visible;
}

Entity::Entity() noexcept :
	_mesh({}), visible(1), _id(0), _name("Entity")
{
}

Entity::Entity(Mesh m) noexcept:
	_mesh(m), visible(1), _id(0), _name("Entity")
{

}



Entity::~Entity()
{
	//Annul its components
	_mesh = {};		
	visible = 0;
}


//////////////////////   FACTORIES   //////////////////////
Entity Entity::Cube(float side)
{
	
	Entity cube(Cube(side));

	cube._name = "Cube";
	return cube;

	
}

Entity Entity::Rectangle(float width, float height)
{
	Entity rectangle(Rectangle(width, height));

	rectangle._name = "Rectangle";
	return rectangle;
}

Entity Entity::Triangle(float width, float height)
{
	Entity triangle(Triangle(width, height));

	triangle._name = "Triangle";
	return triangle;
}
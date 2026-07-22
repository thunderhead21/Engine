#include "Entity.h"

/*
DO NOT DO THIS
Mesh vertices are stored in LOCAL SPACE.

    The renderer computes:

        worldVertex = Entity::Transform * localVertex

    every frame.

    Modifying the mesh destroys its canonical geometry and prevents:
        - instancing
        - shared meshes
        - stable transforms
        - animation
        - correct scaling/rotation

    Transform the vertex during rendering, never the mesh itself.
void Entity::apply_transform()
{
	for (auto& i : geometry) {		//Each triangle
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
	geometry({}), visible(1)
{
}

Entity::Entity(Mesh m) noexcept:
	geometry(m), visible(1) 
{

}



Entity::~Entity()
{
	//Annul its components
	geometry = {};		
	visible = 0;
}
//
namespace Geometry
{

	
}


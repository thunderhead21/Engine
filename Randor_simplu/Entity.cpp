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
	vec3d minimum, maximum; minimum = maximum = {0,0,0};
	minimum.x;
	//Find Center
	/*
	for (auto& tri : m) {
		for (int i = 0; i < 3; i++) {
			if (tri.points[i].x > maximum.x) maximum.x = tri.points[i].x;	//Find maximum X
			if (tri.points[i].x < minimum.x) minimum.x = tri.points[i].x;	//Find minimum X

			if (tri.points[i].y > maximum.y) maximum.y = tri.points[i].y;	//Find maximum Y
			if (tri.points[i].y < minimum.y) minimum.y = tri.points[i].y;	//Find minimum Y

			if (tri.points[i].z > maximum.z) maximum.z = tri.points[i].z;	//Find maximum Z
			if (tri.points[i].z < minimum.z) minimum.z = tri.points[i].z;	//Find minimum Z

		}
	}
	*/

	//Determine center position
	center.x = (minimum.x + maximum.x) / 2;
	center.y = (minimum.y + maximum.y) / 2;
	center.z = (minimum.z + maximum.z) / 2;

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


#pragma once
#include <vector>
#include "../Mesh/Mesh.h"

class Rectangle : public Mesh {

public:
	Rectangle(float width, float height);
	Rectangle(vec3d& a, vec3d& b, vec3d& c, vec3d& d);

};

#pragma once
#include <vector>
#include "Mesh.h"

class rectangle : public Mesh {

public:
	rectangle(float width, float height);
	rectangle(vec3d& a, vec3d& b, vec3d& c, vec3d& d);

};

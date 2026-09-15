#include <Components/Math/Matrix/Matrix.hpp>
#include <Components/Math/Vector/Vector.h>
#include <Components/Transform/Transform.h>

class Camera {
private:
	//Rigid Transform. Scale is locked to {1,1,1}
	Transform _tform;
	mutable mat4 view;	//Cache. Mutable


public:
	mat4 view_matrix();
	const Transform& transform() const { return _tform; };	//Camera position in the world

	////Set position
	////Set rotation
	////Set transform. !ENFORCE RIGIDITY!
};

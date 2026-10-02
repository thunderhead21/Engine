#include "Components/Math/Math.h"
#include "Components/Transform/Transform.h"

class Camera {
private:
	//Rigid Transform. Scale is locked to {1,1,1}
	//If this tranform didn't change, no need to 
	Transform _tform;

	mutable mat4 view;	//Cache. Mutable


public:

	Camera() = default;
	~Camera() = default;

	mat4 view_matrix() const;

	////////////// EVENTS //////////////

	void on_create();
	void on_update();
	void on_delete();

	////Set position
	vec3d position() { return _tform.position(); };
	void position(vec3d position) { _tform.position(position); };
	
	////Set rotation
	vec3d rotation() { return _tform.rotation(); };
	void rotation(vec3d rotation) { _tform.rotation(rotation); };

	
	////Set transform. !ENFORCE RIGIDITY!
	/// @brief Transform getter
	/// @return Transform const reference
	const Transform& transform() const { return _tform; };	//Camera position in the world

	/// @brief Transform getter
	/// @return non-const Transform reference
	Transform& transform() { return _tform; };

	/// @brief Updates the Camera transform with the provided one
	/// @param tform transform to copy
	/// @return TRUE if the parameter transform's scale is different from (1, 1, 1)
	bool transform(const Transform& tform);
};

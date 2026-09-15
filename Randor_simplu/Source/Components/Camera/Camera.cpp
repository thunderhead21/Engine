#include "Camera.h"

mat4 Camera::view_matrix() const 
{
    if (_tform.changed()) {
        //REBUILD cache matrix
        _tform.clean();
        view = _tform.inverse_matrix();
    }
    return view;
}

bool Camera::transform(const Transform& tform)
{

    _tform.position(tform.position());
    _tform.rotation(tform.rotation());

    //If the provided transform was not rigid
    if (tform.scale() != 1) {
        return 1;
    }
    
    return 0;
}

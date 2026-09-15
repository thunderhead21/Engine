#include "Camera.h"

mat4 Camera::view_matrix()
{
    if (_tform.changed()) {
        //REBUILD cache matrix
        _tform.matrix();    //Optimization - delete and clear flag manually
        view = _tform.inverse_matrix();
    }
    return view;
}

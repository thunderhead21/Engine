#include "rectangle.h"

std::vector<triangle> rectangle::to_tris() const {
	//KEEP THE TRIGONOMETRIC ORDER
	
	//Remove intrinsic projection

	//Top left
	vec3d p1 = { x - (w / 2), y - (h / 2), z /*- (d / 2)*/ };
	//Down Left --- p1 is perpendicular to p2
	vec3d p2 = { x - (w / 2), y + (h / 2), z /*- (d / 2)*/ };
	//Down Right
	vec3d p3 = { x + (w / 2), y + (h / 2), z /*+ (d / 2)*/ };
	//Up Right
	vec3d p4 = { x + (w / 2), y - (h / 2), z /*+ (d / 2)*/ };

	return { { p1, p2, p4 }, {p2, p3, p4} };



}
#include "Cube.h"

Cube::Cube(float side)
{
	float hs = side/2;
	

	///{0,0,0} center
	vertices = {
		{-hs, -hs, -hs},	//Far Bottom Left	0
		{ hs, -hs, -hs},	//Far Bottom Right	1
		{ hs,  hs, -hs},	//Far   Top  Right	2
		{-hs,  hs, -hs},	//Far   Top  Left	3
		
		{-hs, -hs, hs},		//Near Bottom Left	4
		{ hs, -hs, hs},		//Near Bottom Right	5
		{ hs,  hs, hs},		//Near   Top  Right	6
		{-hs,  hs, hs},		//Near   Top  Left	7
	};

	indices = {
		0,1,2, 2,3,0,
		4,5,6, 6,7,4,
		0,1,5, 5,4,0,
		1,2,6, 6,5,1,
		6,2,3, 3,7,6,
		0,4,7, 7,3,0
	};

}

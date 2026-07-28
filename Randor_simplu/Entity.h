#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

#include "Transform.h"
#include "Mesh.h"


//using points = std::vector<SDL_Point> ;







/**
* @brief Base for "Assets" to be used and presented by engine and game
* @details Contains a Mesh of vertices. Visible by default.
*/

class Entity
{
protected:
	
	Mesh geometry;
	Transform transform;
	
	bool visible;
	//SDL_Colour colour
	//bool fill


public:

	Transform& get_transform() { return transform; };
	const Transform& get_transform() const { return transform; };

	/**
	* @brief Changes the visibility of the entity
	* @returns bool Visibility of the entity
	*/
	bool toggle_visibility() noexcept;
	
	/**
	* @brief Gets the Mesh object.
	* @returns Mesh& to the entity's geometry
	*/
	inline Mesh& get_Mesh() noexcept { return geometry; };
	inline const Mesh& get_Mesh() const noexcept { return geometry; };
	
	/**
	* @brief Gets the visibility of the entity
	* @returns True  (1) if the entity is visible.
	* @returns False (0) for invisible
	*/
	inline bool get_visibility() const noexcept { return visible; };

	/**
	* @brief Default Ctor. Initializes empty Mesh geometry.
	*/
	Entity() noexcept;
	
	/**
	* @brief Creates entity with Mesh.
	* @param m Mesh to associate to the Entity
	*/
	Entity(Mesh m) noexcept;
	virtual ~Entity();

};



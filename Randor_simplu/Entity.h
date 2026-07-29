#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

#include "Transform.h"
#include "Mesh.h"
#include "Entity_Data.h"




///////////////////////////////   IDENTITY   ///////////////////////////////
/*
*	Entity has an ID and tag.
* 
*/
///////////////////////////////   IDENTITY   ///////////////////////////////

//using points = std::vector<SDL_Point> ;

/**
* @brief Base for "Assets" to be used and presented by engine and game
* @details Contains a Mesh of vertices. Visible by default.
*/

class Entity
{
	friend class Scene;
protected:
	
	Mesh mesh;
	Transform transform;
	
	bool visible;
	size_t id;
	std::string name;

	
	//SDL_Colour colour
	//bool fill


	Tags tags;
	Layers layers;

public:

	void set_mesh(Mesh mesh) { mesh = mesh; }
	void set_transform(Transform& t ) { transform = t; }

	Transform& get_transform() { return transform; };
	const Transform& get_transform() const { return transform; };
	
	/**
	* @brief Gets the Mesh object.
	* @returns Mesh& to the entity's mesh
	*/
	inline Mesh& get_Mesh() noexcept { return mesh; };
	inline const Mesh& get_Mesh() const noexcept { return mesh; };
	/// @brief Getter for Entity's ID
	/// @return size_t ID
	inline const size_t& get_id() const { return id; }
	/// @brief Getter for Entity's name
	/// @return string name
	inline const std::string& get_name() const { return name; };

	inline Layers enable_layer(Layers layer) { return layers |= layer; }
	inline Layers disable_layer(Layers layer) { layers = layers & (~layer); }
	inline Layers has_layer(Layers layer) { layers &= layer; }

	/**
	* @brief Changes the visibility of the entity
	* @returns bool Visibility of the entity
	*/
	bool toggle_visibility() noexcept;
	
	/**
	* @brief Gets the visibility of the entity
	* @returns True  (1) if the entity is visible.
	* @returns False (0) for invisible
	*/
	inline bool is_visibile() const noexcept { return visible; };

	/**
	* @brief Default Ctor. Initializes empty Mesh mesh.
	*/
	Entity() noexcept;
	
	/**
	* @brief Creates entity with Mesh.
	* @param m Mesh to associate to the Entity
	*/
	Entity(Mesh m) noexcept;
	virtual ~Entity();

};



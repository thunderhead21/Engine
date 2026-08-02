#pragma once

#include <SDL3/SDL_render.h>
#include <vector>

#include "Transform.h"
#include "Geometry.h"
#include "Entity_Data.h"




///////////////////////////////   IDENTITY   ///////////////////////////////
/*
*	Entity has an ID and tag.
* 
*/
///////////////////////////////   IDENTITY   ///////////////////////////////

/**
* @brief Base for "Assets" to be used and presented by engine and game
* @details Contains a Mesh of vertices. Visible by default.
*/
class Entity
{
	friend class Scene;		//Modify the ID and Name upon entering Scene
protected:
	

	Transform _transform;
	
	size_t _id;
	std::string _name;

	bool visible;		//Whether it is rendered or not.

	Tags tags{Tags::None};	//Not needed now. Useful for gameplay and categorisation
	Layers layers{Layers::Renderable};		//Subsystem responsible for the entity. Inheritors modify it in CTORs

	Mesh _mesh;
	mutable std::vector<vec4d> _world_cache;
	mutable std::vector<SDL_Vertex> _projection_cache;
	mutable bool _dirty = 1;

public:
	/// @brief Sets the visible component that represents the entity
	/// @param mesh - Mesh object to copy into the mesh member
	void set_mesh(const Mesh& mesh) { _mesh = mesh;  }

	/// @brief Changes the entity's transform (Postion, Rotation, Scale)
	/// @param &t to the transform to copy from
	void transform(Transform& t ) { _transform = t; }

	void clean() { _dirty = 0; };
	void set_dirty() { _dirty = 1; }

	/// @brief Transform getter
	/// @return Reference to Entity's Transform
	Transform& transform() { return _transform; };
	const Transform& transform() const { return _transform; };
	
	std::vector<SDL_Vertex>& projection_buffer() { return _projection_cache; }
	std::vector<vec4d>& world_buffer() { return _world_cache; }

	/**
	* @brief Gets the Mesh object.
	* @returns Mesh& to the entity's mesh
	*/
	inline Mesh& mesh() noexcept { return _mesh; };
	inline const Mesh& mesh() const noexcept { return _mesh; };
	/// @brief Getter for Entity's ID
	/// @return size_t ID
	inline const size_t& id() const { return _id; }
	/// @brief Getter for Entity's name
	/// @return string name
	inline const std::string& name() const { return _name; };

	/// @brief Sets the required layer flags
	/// @param Layer flag to append
	/// @return - up-to-date layer flag enum
	inline Layers enable_layer(Layers layer) { return layers |= layer; }
	/// @brief Disables the required layer flags
	/// @param Layer flag to remove
	/// @return - up-to-date layer flag enum
	inline Layers disable_layer(Layers layer) { layers &= (~layer); }
	/// @brief Checks for the requested layer flags
	/// @param Layer flag to check for
	/// @return bool value answering "are all the flags present?"
	inline bool has_layer(Layers layers_to_check) const { return layers_to_check == 0 ? layers_to_check == layers : (layers_to_check & layers) == layers_to_check; }	//Checks the Layer flags

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




	/////////////////FACTORIES/////////////////
	
	/// @brief Creates an entity with a Cube mesh
	/// @param side of the cube
	/// @return Entity with the requested Mesh
	static Entity Cube(float side = 400);
	/// @brief Creates an entity with a Rectangle mesh
	/// @param width of the rectangle
	/// @param height of the rectangle
	/// @return Entity with the requested Mesh
	static Entity Rectangle(float width = 300, float height = 150);
	/// @brief Creates and entity with a Triangle mesh
	/// @param width of the traingle's base
	/// @param height of the traingle
	/// @return Entity with the requested Mesh
	static Entity Triangle(float width = 300, float height = 300);
};



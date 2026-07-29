#pragma once

#include <type_traits>

#define ENTITY_ENUM_TYPE unsigned int

enum class Layers : ENTITY_ENUM_TYPE {

	None = 0,
	Physics = 1 << 0,
	Renderable = 1 << 1,
	UI = 1 << 2

};

enum class Tags : ENTITY_ENUM_TYPE {

	None = 0

};

using real_type = std::underlying_type_t<Layers>;	//Whichever one. Tags and Layers are of same type.

///////////OPERATOR BITWISE_OR() 
inline Layers operator|(Layers a, Layers b) {
	return static_cast<Layers>(static_cast<real_type>(a) | static_cast<real_type>(b));
}

inline Tags operator|(Tags a, Tags b) {
	return static_cast<Tags>(static_cast<real_type>(a) | static_cast<real_type>(b));
}

inline Layers& operator|=(Layers& a, Layers& b) {
	a = static_cast<Layers>(static_cast<real_type>(a) | static_cast<real_type>(b));
	return a;
}

inline Tags& operator|=(Tags& a, Tags& b) {
	a = static_cast<Tags>(static_cast<real_type>(a) | static_cast<real_type>(b));
	return a;
}


///////////OPERATOR BITWISE_AND()
inline Layers operator&(Layers a, Layers b) {
	return static_cast<Layers>(static_cast<real_type>(a) & static_cast<real_type>(b));
}

inline Tags operator&(Tags a, Tags b) {
	return static_cast<Tags>(static_cast<real_type>(a) & static_cast<real_type>(b));
}

inline Layers& operator&=(Layers& a, Layers b) {
	a = a & b;
	return a;
}

inline Tags& operator&=(Tags& a, Tags b) {
	a = a & b;
	return a;
}

///////////OPERATOR BITWISE_NOT()
inline Layers operator~(Layers l) { return static_cast<Layers>(~static_cast<real_type>(l)); }

inline Tags operator~(Tags l) { return static_cast<Tags>(~static_cast<real_type>(l)); }

///////////OPERATOR<<()
inline std::ostream& operator<<(std::ostream& os, Layers l) { return (os << l); }

inline std::ostream& operator<<(std::ostream& os, Tags t) { return (os << t); }

///////////OPERATOR==()
template<typename T>
inline bool operator==(Layers a, T b) { return static_cast<real_type>(a) == static_cast<real_type>(b); }

template<typename T>
inline bool operator==(Tags a, T b) { return static_cast<real_type>(a) == static_cast<real_type>(b); }

///////////OPERATOR!=()
template<typename T>
inline bool operator!=(Layers a, T b) { return static_cast<real_type>(a) != static_cast<real_type>(b); }

template<typename T>
inline bool operator!=(Tags a, T b) { return static_cast<real_type>(a) != static_cast<real_type>(b); }

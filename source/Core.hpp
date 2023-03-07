#pragma once

enum class Directions { left, right, up, down };

inline const sf::Vector2f left		{ -1.0f,  0.0f };
inline const sf::Vector2f right		{  1.0f,  0.0f };
inline const sf::Vector2f up		{  0.0f, -1.0f };
inline const sf::Vector2f down		{  0.0f,  1.0f };

inline const std::unordered_map <Directions, sf::Vector2f> directionVectors
{
	{ Directions::left,		left	},
	{ Directions::right,	right	},
	{ Directions::up,		up		},
	{ Directions::down,		down	}
};

inline const Directions allDirections [] { Directions::left, Directions::right, Directions::up, Directions::down };

sf::Vector2i DirectionToVector ( Directions );
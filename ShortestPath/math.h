#pragma once
#include <SFML/Graphics.hpp>
#include "globals.h"

inline constexpr double RADIANS_TO_DEGREES_MULTIPLE() { return 180 / PI; }
inline constexpr double DEGREES_TO_RADIANS_MULTIPLE() { return PI / 180; }

namespace MathHelper
{
	namespace Trigonometry
	{
		inline double fromDegreesToRadians(double degrees) { return degrees * DEGREES_TO_RADIANS_MULTIPLE(); }
		inline double fromRadiansToDegrees(double radii) { return radii * RADIANS_TO_DEGREES_MULTIPLE(); }
	}

	namespace LinearAlgebra
	{
		inline double getVectorMagnitude(sf::Vector2f currentVector) { return std::hypot(currentVector.x, currentVector.y); };
		inline double getVectorMagnitude(sf::Vector2i currentVector) { return std::hypot(currentVector.x, currentVector.y); }
	}

}
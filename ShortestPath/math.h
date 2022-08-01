#pragma once
#include <iostream>
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

		double atanFullRotation(double yComponent, double xComponent);
	}

	namespace LinearAlgebra
	{
		inline double getVectorMagnitude(sf::Vector2f currentVector) { return std::hypot(currentVector.x, currentVector.y); };
		inline double getVectorMagnitude(sf::Vector2i currentVector) { return std::hypot(currentVector.x, currentVector.y); }
	}

	namespace Planar
	{
		template<typename T>
		inline T clamp(T lowerBound, T higherBound, T value) { return std::min(std::max(lowerBound, value), higherBound); }
		
		
		inline sf::Vector2i clampVector(sf::Vector2i lowerBound, sf::Vector2i higherBound, sf::Vector2i value)
		{
			return sf::Vector2i(MathHelper::Planar::clamp(lowerBound.x, higherBound.x, value.x), MathHelper::Planar::clamp(lowerBound.y, higherBound.y, value.y));
		}
	}

	
}
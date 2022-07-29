#pragma once
#include <SFML/Graphics.hpp>

namespace SFMLHelper
{
	namespace Vectorf
	{
		sf::Vector2f SFMLCoordinateToCartesian(sf::Vector2f, int);

		sf::Vector2f cartesianToSFMLCoordinate(sf::Vector2f, int);
	}
}

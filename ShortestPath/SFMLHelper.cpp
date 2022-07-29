#include "SFMLHelper.h"

sf::Vector2f SFMLHelper::Vectorf::SFMLCoordinateToCartesian(sf::Vector2f vector, int screenHeight)
{
	vector.y = vector.y - (screenHeight / 2);

	return vector;
}

sf::Vector2f SFMLHelper::Vectorf::cartesianToSFMLCoordinate(sf::Vector2f vector, int screenHeight)
{
	vector.y = vector.y + (screenHeight / 2);

	return vector;
}
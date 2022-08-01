#include <iostream>
#include <math.h>

#include "globals.h"
#include "math.h"


double MathHelper::Trigonometry::atanFullRotation(double yComponent, double xComponent)
{
	double radians = std::atan2(yComponent, xComponent);

	return radians;
	if (yComponent > 0)
	{
		return radians;
	}
	else if (yComponent < 0)
	{
		return radians + std::atan2(-yComponent, xComponent);
	}
	else
	{
		if (xComponent > 0)
		{
			return 0;
		}
		else
		{
			return PI;
		}
	}
}
//double MathHelper::LinearAlgebra::getVectorMagnitude(sf::Vector2f currentVector)
//{
//    return std::hypot(currentVector.x, currentVector.y);
//}

//double MathHelper::LinearAlgebra::getVectorMagnitude(sf::Vector2i currentVector)
//{
//    return std::hypot(currentVector.x, currentVector.y);
//}

//double MathHelper::Trigonometry::fromDegreesToRadians(double degrees)
//{
//    return degrees * DEGREES_TO_RADIANS_MULTIPLE();
//}

//double MathHelper::Trigonometry::fromRadiansToDegrees(double radii)
//{
//    return radii * RADIANS_TO_DEGREES_MULTIPLE();
//}
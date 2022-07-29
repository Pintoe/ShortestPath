#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "globals.h"

inline double GET_DIAGONAL_LENGTH() { return std::hypot(SCREEN_WIDTH, SCREEN_HEIGHT); }

namespace LineShapeProperties {
	const sf::Color FILL_COLOR = sf::Color(255, 255, 255, 128);
}

class LineShape : public sf::Shape
{
public:
	LineShape(sf::Vector2f, sf::Vector2f, bool, double);	

	std::size_t getPointCount() const override;
	sf::Vector2f getPoint(std::size_t) const override;

	void update();
	void updateFillColor();

	void setTargetVector(sf::Vector2f);
	void setStartVector(sf::Vector2f);

private:

	sf::RectangleShape m_rectangleRepresentation;

	sf::Vector2f m_targetVector;
	sf::Vector2f m_startVector;

	double m_thickness;
};
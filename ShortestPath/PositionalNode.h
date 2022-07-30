#pragma once
#include <SFML/Graphics.hpp>

namespace NodeShapeProperties {
	const sf::Color FILL_COLOR = sf::Color(255, 0, 0, 128);
	const float RADIUS = 10;
}


class Node
{
public:
	Node(sf::Vector2i, bool);

	void draw(sf::RenderWindow&);

	void setCurrentPosition(sf::Vector2i);

	sf::Vector2i& correctVector(sf::Vector2i&);

	sf::Vector2i getCurrentPosition();
private:
	sf::Vector2i m_currentPosition;
	sf::CircleShape m_nodeShape;

	bool m_positionChangedFlag;
	friend class AdjacencyMatrix;
};

namespace NodeShapeUtilities
{
	double distanceBetweenTwoNodes(Node&, Node&);
}
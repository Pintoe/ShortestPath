#include <iostream>

#include "PositionalNode.h"
#include "math.h"

const sf::Vector2i g_LOWER_BOUND_VECTOR = sf::Vector2i(0, 0);
const sf::Vector2i g_HIGHER_BOUND_VECTOR = sf::Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT);

double NodeShapeUtilities::distanceBetweenTwoNodes(Node& startNode, Node& endNode)
{
	return MathHelper::LinearAlgebra::getVectorMagnitude(startNode.getCurrentPosition() - endNode.getCurrentPosition());
}

Node::Node(sf::Vector2i currentPosition, bool correctVector=false)
{
	// this->m_currentPosition = correctVector ? this->correctVector(currentPosition) : currentPosition;

	this->m_positionChangedFlag = false;

	this->m_currentPosition = currentPosition;

	this->m_nodeShape.setOrigin(sf::Vector2f(NodeShapeProperties::RADIUS, NodeShapeProperties::RADIUS));
	this->m_nodeShape.setRadius(NodeShapeProperties::RADIUS);
	this->m_nodeShape.setFillColor(NodeShapeProperties::FILL_COLOR);
}

void Node::draw(sf::RenderWindow& renderWindow)
{
	sf::CircleShape copyOfNodeShape = this->m_nodeShape;
	copyOfNodeShape.setPosition(
		renderWindow.mapPixelToCoords(
			this->m_currentPosition
		)
	);

	renderWindow.draw(copyOfNodeShape);
}

void Node::setCurrentPosition(sf::Vector2i newPosition)
{
	this->m_positionChangedFlag = true;
	this->m_currentPosition = MathHelper::Planar::clampVector(
		g_LOWER_BOUND_VECTOR,
		g_HIGHER_BOUND_VECTOR,
		newPosition
	);
}

sf::Vector2i Node::getCurrentPosition()
{
	return this->m_currentPosition;
}

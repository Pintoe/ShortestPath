#include <iostream>

#include "PositionalNode.h"
#include "math.h"

double NodeShapeUtilities::distanceBetweenTwoNodes(Node& startNode, Node& endNode)
{
	sf::Vector2f distanceBetweenVectors = sf::Vector2f(startNode.getCurrentPosition() - endNode.getCurrentPosition());

	return MathHelper::LinearAlgebra::getVectorMagnitude(distanceBetweenVectors);
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
	copyOfNodeShape.setPosition(renderWindow.mapPixelToCoords(this->m_currentPosition));

	renderWindow.draw(copyOfNodeShape);
}

void Node::setCurrentPosition(sf::Vector2i newPosition)
{
	this->m_positionChangedFlag = true;
	this->m_currentPosition = newPosition;
}

sf::Vector2i& Node::correctVector(sf::Vector2i& oldVector)
{
	// oldVector = oldVector - sf::Vector2i(NodeShapeProperties::RADIUS, NodeShapeProperties::RADIUS);

	return oldVector;
}

sf::Vector2i Node::getCurrentPosition()
{
	return this->m_currentPosition;
}

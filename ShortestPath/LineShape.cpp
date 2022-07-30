#include <iostream>

#include "globals.h"
#include "LineShape.h"
#include "PositionalNode.h"
#include "math.h"
#include "SFMLHelper.h"

LineShape::LineShape(sf::Vector2f currentPosition, sf::Vector2f targetPoisiton, bool opacity, double thickness=10)
{
    // std::cout << "Current Position: " << currentPosition.x << ", " << currentPosition.y << std::endl;
    this->m_startVector = currentPosition;
    this->m_targetVector = targetPoisiton;
    this->m_thickness = thickness;

    this->m_rectangleRepresentation.setOrigin(sf::Vector2f(0, thickness / 2));
    this->setFillColor(LineShapeProperties::FILL_COLOR);
    this->update();
}

void LineShape::updateFillColor()
{
    sf::Color newFillColor(LineShapeProperties::FILL_COLOR);
    double percentFullVector = MathHelper::LinearAlgebra::getVectorMagnitude(this->m_startVector - this->m_targetVector) / GET_DIAGONAL_LENGTH();
    newFillColor.a = std::min((1 - percentFullVector), (double) 1) * 255 * TRANSPARENCY_CONSTANT;

    
    this->setFillColor(newFillColor);
}

void LineShape::setTargetVector(sf::Vector2f newTarget)
{
    this->m_targetVector = newTarget;
    this->update();
}

void LineShape::setStartVector(sf::Vector2f newStart)
{
    this->m_startVector = newStart;
    this->update();
}

std::size_t LineShape::getPointCount() const
{
    return 4;
}

sf::Vector2f LineShape::getPoint(std::size_t index) const
{
    return this->m_rectangleRepresentation.getTransform().transformPoint(this->m_rectangleRepresentation.getPoint(index));
}

void LineShape::update()
{

    sf::Vector2f currentToTargetDifference = this->m_targetVector - this->m_startVector;


    sf::Vector2f sizeOfRectangle = sf::Vector2f(
        MathHelper::LinearAlgebra::getVectorMagnitude(currentToTargetDifference),
        this->m_thickness
    );

    double rotationAmount = std::atan2(currentToTargetDifference.y, currentToTargetDifference.x);
    
    this->m_rectangleRepresentation.setPosition(this->m_startVector);
    this->m_rectangleRepresentation.setSize(sizeOfRectangle);
    this->m_rectangleRepresentation.setRotation(MathHelper::Trigonometry::fromRadiansToDegrees(rotationAmount));
    
    // std::cout << "position: " << centeredPositionalVector.x << ", " << centeredPositionalVector.y << " Rotation: " << rotationAmount << " Size: " << sizeOfRectangle.x << ", " << sizeOfRectangle.y << std::endl;
   
    this->updateFillColor();
    sf::Shape::update();
}
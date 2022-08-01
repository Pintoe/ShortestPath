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
    // std::cout << this->m_vertexPositions[index].x << " Y: " << this->m_vertexPositions[index].y << std::endl;
    return this->m_vertexPositions[index];
}

void LineShape::update()
{

    sf::Vector2f currentToTargetDifference = this->m_targetVector - this->m_startVector;


    // double distanceBetweenPoints = MathHelper::LinearAlgebra::getVectorMagnitude(currentToTargetDifference);

    double rotationAmount = std::atan2(-currentToTargetDifference.y, currentToTargetDifference.x);
    double radius = this->m_thickness / 2;

    //this->m_rectangleRepresentation.setPosition(this->m_startVector);
    //this->m_rectangleRepresentation.setSize(sizeOfRectangle);
    //this->m_rectangleRepresentation.setRotation(MathHelper::Trigonometry::fromRadiansToDegrees(rotationAmount));
    
    // std::cout << "Rotation: " << rotationAmount << std::endl;
    // std::cout << "position: " << centeredPositionalVector.x << ", " << centeredPositionalVector.y << " Rotation: " << rotationAmount << " Size: " << sizeOfRectangle.x << ", " << sizeOfRectangle.y << std::endl;
   
    //sf::Vector2f originalPoint0 = sf::Vector2f(this->m_startVector.x, this->m_startVector.y - radius);
    //sf::Vector2f originalPoint1 = sf::Vector2f(this->m_startVector.x, this->m_startVector.y + radius);
    //sf::Vector2f originalPoint2 = sf::Vector2f(this->m_startVector.x + distanceBetweenPoints, this->m_startVector.y + radius);
    //sf::Vector2f originalPoint3 = sf::Vector2f(this->m_startVector.x + distanceBetweenPoints, this->m_startVector.y - radius);

    sf::Vector2f& rotationAboutPoint = this->m_startVector;

    //sf::Vector2f transformedPoint0 = sf::Vector2f(
    //    rotationAboutPoint.x + (originalPoint0.x - rotationAboutPoint.x) * std::cos(rotationAmount) + (originalPoint0.y - rotationAboutPoint.y) * std::sin(rotationAmount),
    //    rotationAboutPoint.y - (originalPoint0.x - rotationAboutPoint.x) * std::sin(rotationAmount) + (originalPoint0.y - rotationAboutPoint.y) * std::cos(rotationAmount)
    //);

    double xPositionOffset = radius * std::cos(rotationAmount);
    double yPositionOffset = radius * std::sin(rotationAmount);
    
    sf::Vector2f transformedPoint0(
        rotationAboutPoint.x - yPositionOffset,
        rotationAboutPoint.y - xPositionOffset
    );

    sf::Vector2f transformedPoint1(
        rotationAboutPoint.x + yPositionOffset,
        rotationAboutPoint.y + xPositionOffset
    );

    this->m_vertexPositions[0] = transformedPoint0;// sf::Vector2f(this->m_startVector.x - std::sin(rotationAmount) * this->m_thickness, this->m_startVector.y - (this->m_thickness / 2) + (this->m_thickness / 2) * std::sin(rotationAmount));
    this->m_vertexPositions[1] = transformedPoint1; // sf::Vector2f(this->m_startVector.x + std::sin(rotationAmount) * this->m_thickness, this->m_startVector.y + (this->m_thickness / 2) - (this->m_thickness / 2) * std::sin(rotationAmount));
    this->m_vertexPositions[2] = transformedPoint1 + currentToTargetDifference; // sf::Vector2f(this->m_startVector.x + distanceBetweenPoints * std::cos(rotationAmount), std::cos(rotationAmount) * this->m_startVector.y + this->m_thickness / 2);
    this->m_vertexPositions[3] = transformedPoint0 + currentToTargetDifference;// sf::Vector2f(this->m_startVector.x + distanceBetweenPoints * std::cos(rotationAmount), std::cos(rotationAmount) * this->m_startVector.y - this->m_thickness / 2);

    //double tangentRotationAmountPositive = rotationAmount + PI / 2;
    //double tangentRotationAmountNegative = rotationAmount - PI / 2;

    //double radius = this->m_thickness / 2;

    //sf::Vector2f& startVector = this->m_startVector;

    //// [xcos(a) - ysin(a)]
    //// [ysin(a) + xcos(a)]

    //this->m_vertexPositions[0] = sf::Vector2f(
    //    startVector.x + radius * std::cos(tangentRotationAmountNegative) ,
    //    startVector.y + radius * std::cos(tangentRotationAmountNegative)
    //);

    //this->m_vertexPositions[1] = sf::Vector2f(
    //    startVector.x + radius * std::cos(tangentRotationAmountPositive),
    //    startVector.y + radius * std::cos(tangentRotationAmountPositive)
    //);

    //this->m_vertexPositions[2] = this->m_vertexPositions[1] + currentToTargetDifference;

    //this->m_vertexPositions[3] = this->m_vertexPositions[0] + currentToTargetDifference;

    this->updateFillColor();
    sf::Shape::update();
}
#include <SFML/Graphics.hpp>
#include <iostream>

#include "LineShape.h"

#include "PositionalNode.h"
#include "AdjacencyMatrix.h"

#include "globals.h"
#include "math.h"

int getCollidingNodesFromClick(sf::Vector2i mouseClickPosition, AdjacencyMatrix& visibleNodesMatrix)
{
	for (int currentNodeIndex = 0; currentNodeIndex < visibleNodesMatrix.size; currentNodeIndex++)
	{
		Node* currentNode = visibleNodesMatrix.getNodePointerFromKey(currentNodeIndex);
		sf::Vector2i distanceBetweenVectors = mouseClickPosition - currentNode->getCurrentPosition();

		// std::cout << "Mouse position: " << mouseClickPosition.x << " " << mouseClickPosition.y << " Node Posiiton: " << currentNode.getCurrentPosition().x << " " << currentNode.getCurrentPosition().y << " Distance: " << distanceBetweenVectors.x << " " << distanceBetweenVectors.y << std::endl;
		if (MathHelper::LinearAlgebra::getVectorMagnitude(distanceBetweenVectors) <= NodeShapeProperties::RADIUS)
		{
			// std::cout << "Within range" << std::endl;
			return currentNodeIndex;
		}
	}

	return -1;
}

int main()
{
	const sf::Mouse::Button NODE_MOVEMENT_BUTTON = sf::Mouse::Button::Left;
	const sf::Mouse::Button NODE_CONNECTION_BUTTION = sf::Mouse::Button::Right;

    sf::RenderWindow renderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Shortest Path");
	renderWindow.setFramerateLimit(144);

	// std::vector<Node> visibleNodes;

	sf::Vector2i lastMousePosition(0, 0);
	
	AdjacencyMatrix visibleNodesMatrix;

	int movementNodeIndex = -1;
	bool leftClickHeldDown = sf::Mouse::isButtonPressed(NODE_MOVEMENT_BUTTON);
	
	int startConnectionNodeIndex = -1;
	bool currentlyCreatingConnection = false;

	bool queueAllConnectionCreate = false;

	sf::Clock framesPerSecondClock;
	double lastFrameTime = 0;

	for (int i = 0; i < 100; i++)
	{
		double xPos = rand() % SCREEN_WIDTH;
		double yPos = rand() % SCREEN_HEIGHT;

		// std::cout << xPos << std::endl;
		Node* pNewNode = new Node(sf::Vector2i(xPos, yPos), true);
		// visibleNodes.push_back(*pNewNode);
		visibleNodesMatrix.addVertex(pNewNode);
	}

	queueAllConnectionCreate = false;
	for (int i = 0; i < visibleNodesMatrix.size; i++)
	{
		Node* currentNode = visibleNodesMatrix.getNodePointerFromKey(i);

		for (int j = 0; j < visibleNodesMatrix.size; j++)
		{
			Node* currentNode2 = visibleNodesMatrix.getNodePointerFromKey(j);
			if (i != j)
			{
				visibleNodesMatrix.addEdge(i, j);
			}
		}
	}
    while (renderWindow.isOpen())
    {
		sf::Vector2i currentMousePosition = sf::Mouse::getPosition(renderWindow);

		sf::Event event;

		while (renderWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				renderWindow.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					renderWindow.close();
					break;
				case sf::Keyboard::N:
				{
					// std::cout << "New Node" << std::endl;
					Node* pNewNode = new Node(currentMousePosition, true);
					// visibleNodes.push_back(*pNewNode);
					visibleNodesMatrix.addVertex(pNewNode);
				}
					break;
				case sf::Keyboard::P:
					std::cout << visibleNodesMatrix << std::endl;
					break;
				case sf::Keyboard::R:
					queueAllConnectionCreate = true;
					break;
				}	
			break;
			default:
				break;
			}
		}

		if (queueAllConnectionCreate)
		{
			queueAllConnectionCreate = false;
			for (int i = 0; i < visibleNodesMatrix.size; i++)
			{
				Node* currentNode = visibleNodesMatrix.getNodePointerFromKey(i);

				for (int j = 0; j < visibleNodesMatrix.size; j++)
				{
					Node* currentNode2 = visibleNodesMatrix.getNodePointerFromKey(j);
					if (i != j)
					{
						visibleNodesMatrix.addEdge(i, j);
					}
				}
			}
		}
		if (leftClickHeldDown && sf::Mouse::isButtonPressed(NODE_MOVEMENT_BUTTON))
		{
			// visibleNodes[movementNodeIndex].setCurrentPosition(currentMousePosition);
			visibleNodesMatrix.getNodePointerFromKey(movementNodeIndex)->setCurrentPosition(currentMousePosition);
		}
		else if (sf::Mouse::isButtonPressed(NODE_MOVEMENT_BUTTON) && currentMousePosition != lastMousePosition)
		{
			movementNodeIndex = getCollidingNodesFromClick(currentMousePosition, visibleNodesMatrix);

			if (movementNodeIndex != -1)
			{
				leftClickHeldDown = true;
			}
		}
		else
		{
			leftClickHeldDown = false;
		}
		
		if (!currentlyCreatingConnection && sf::Mouse::isButtonPressed(NODE_CONNECTION_BUTTION))
		{
			startConnectionNodeIndex = getCollidingNodesFromClick(currentMousePosition, visibleNodesMatrix);

			if (startConnectionNodeIndex != -1)
			{
				currentlyCreatingConnection = true;
			}
		}
		else if (!sf::Mouse::isButtonPressed(NODE_CONNECTION_BUTTION))
		{

			if (currentlyCreatingConnection && startConnectionNodeIndex != -1)
			{
				int endConnectionNodeIndex = getCollidingNodesFromClick(currentMousePosition, visibleNodesMatrix);
				std::cout << "Reference node: " << endConnectionNodeIndex << std::endl;

				if (endConnectionNodeIndex != -1)
				{
					//nodeConnections.push_back(
					//	connectingLine(LineShape(
					//		sf::Vector2f(visibleNodes[startConnectionNodeIndex].getCurrentPosition()),
					//		sf::Vector2f(visibleNodes[endConnectionNodeIndex].getCurrentPosition()),
					//		CONNECTION_THICKNESS
					//	),
					//		startConnectionNodeIndex,
					//		endConnectionNodeIndex
					//		
					//));

					visibleNodesMatrix.addEdge(
						startConnectionNodeIndex,
						endConnectionNodeIndex
					);
				}
			}
			currentlyCreatingConnection = false; 
		}

		renderWindow.clear();

		if (currentlyCreatingConnection)
		{

			sf::Vector2f linePosition = sf::Vector2f(visibleNodesMatrix.getNodePointerFromKey(startConnectionNodeIndex)->getCurrentPosition());
			sf::Vector2f targetLinePosition = sf::Vector2f(currentMousePosition);

			renderWindow.draw(
				LineShape(
					sf::Vector2f(visibleNodesMatrix.getNodePointerFromKey(startConnectionNodeIndex)->getCurrentPosition()),
					sf::Vector2f(currentMousePosition),
					true,
					CONNECTION_THICKNESS
				)
			);
			
			std::cout << "Line Position: (" << linePosition.x << ", " << linePosition.y << ") Target Position: (" << targetLinePosition.x << ", " << targetLinePosition.y << ")" << std::endl;
		}

		//for (int currentLineIndex = 0; currentLineIndex < nodeConnections.size(); currentLineIndex++)
		//{
		//	connectingLine currentLineProperties = nodeConnections[currentLineIndex];
		//	LineShape currentLine = currentLineProperties.line;

		//	currentLine.setTargetVector(sf::Vector2f(visibleNodes[currentLineProperties.endPointIndex].getCurrentPosition()));
		//	currentLine.setStartVector(sf::Vector2f(visibleNodes[currentLineProperties.startPointIndex].getCurrentPosition()));

		//	// std::cout << visibleNodes[currentLineProperties.startPointIndex].getCorrectedPosition().x << std::endl;
		//	renderWindow.draw(currentLine);
		//}

		// int currentStartColumnIndex = 0;

		//for (int currentRowIndex = 0; currentRowIndex < visibleNodesMatrix.size; currentRowIndex++)
		//{

		//	Node* currentRowNode = visibleNodesMatrix.getNodePointerFromKey(currentRowIndex);

		//	currentRowNode->draw(renderWindow);

		//	for (int currentColumnIndex = currentStartColumnIndex; currentColumnIndex < visibleNodesMatrix.size; currentColumnIndex++)
		//	{

		//		double currentConnectionWeight = visibleNodesMatrix.getWeightFromKey(currentRowIndex, currentColumnIndex);

		//		//if (currentConnectionWeight != 0)
		//		//{
		//			LineShape connectingLine(
		//				sf::Vector2f(currentRowNode->getCurrentPosition()),
		//				sf::Vector2f(visibleNodesMatrix.getNodePointerFromKey(currentColumnIndex)->getCurrentPosition()),
		//				true,
		//				10
		//			);

		//			renderWindow.draw(connectingLine);
		//		// }
		//	}
		//}
		

		visibleNodesMatrix.drawConnections(renderWindow);

		renderWindow.display();

  		lastMousePosition = currentMousePosition;

		double currentFrameTime = framesPerSecondClock.getElapsedTime().asSeconds();


		double fps = 1 / (currentFrameTime - lastFrameTime);

		std::cout << "FPS: " << fps << " LastTime: " << lastFrameTime << " CurrentTime: " << currentFrameTime << std::endl;

		lastFrameTime = currentFrameTime;



    }

	{
		int a;
		std::cin >> a;
	}
	return 0;
}
#include "AdjacencyMatrix.h"
#include "math.h"

AdjacencyMatrix::AdjacencyMatrix() : size(0), m_pStartNode(nullptr) {}

void AdjacencyMatrix::addVertex(Node* pNodeToAdd)
{
	this->m_pointerToNodes.push_back(pNodeToAdd);

	for (int row = 0; row < this->size; row++)
	{
		this->m_matrix[row].push_back(new AdjacencyMatrixNode(0, nullptr));
	}

	this->m_matrix.push_back(std::vector<AdjacencyMatrixNode*>(++this->size));

	for (int column = 0; column < this->size; column++)
	{
		this->m_matrix[this->size - 1][column] = new AdjacencyMatrixNode(0, nullptr);
	}
}

void AdjacencyMatrix::addEdge(Node* pNode1, Node* pNode2)
{

	int indexToFirstNode = -1;
	int indexToSecondNode = -1;

	for (int currentElementIndex = 0; currentElementIndex < this->m_pointerToNodes.size(); currentElementIndex++)
	{
		if (this->m_pointerToNodes[currentElementIndex] == pNode1)
		{
			indexToFirstNode = currentElementIndex;
		}
		else if (this->m_pointerToNodes[currentElementIndex] == pNode2)
		{
			indexToSecondNode = currentElementIndex;
		}
	}

	if (indexToFirstNode != -1 && indexToSecondNode != -1)
	{
		double differenceInPosition = MathHelper::LinearAlgebra::getVectorMagnitude(pNode1->getCurrentPosition() - pNode2->getCurrentPosition());
		
		AdjacencyMatrixNode* pWeightNode1 = new AdjacencyMatrixNode(
			differenceInPosition,
			new LineShape(
				sf::Vector2f(pNode1->getCurrentPosition()),
				sf::Vector2f(pNode2->getCurrentPosition()),
				true,
				CONNECTION_THICKNESS
			)
		);

		AdjacencyMatrixNode* pWeightNode2 = new AdjacencyMatrixNode(
			differenceInPosition,
			new LineShape(
				sf::Vector2f(pNode2->getCurrentPosition()),
				sf::Vector2f(pNode1->getCurrentPosition()),
				true,
				CONNECTION_THICKNESS
			)
		);

		delete this->m_matrix[indexToFirstNode][indexToSecondNode];
		delete this->m_matrix[indexToSecondNode][indexToFirstNode];

		this->m_matrix[indexToFirstNode][indexToSecondNode] = pWeightNode1;
		this->m_matrix[indexToSecondNode][indexToFirstNode] = pWeightNode2;
	}
}

void AdjacencyMatrix::addEdge(int indexNode1, int indexNode2)
{
	this->addEdge(this->m_pointerToNodes[indexNode1], this->m_pointerToNodes[indexNode2]);
}

void AdjacencyMatrix::drawConnections(sf::RenderWindow& renderWindow)
{
	int currentStartColumnIndex = 0;

	for (int currentRowIndex = 0; currentRowIndex < this->size; currentRowIndex++)
	{

		Node* pCurrentRowNode = this->getNodePointerFromKey(currentRowIndex);


		if (pCurrentRowNode->m_positionChangedFlag)
		{
			pCurrentRowNode->m_positionChangedFlag = false;

			for (int currentColumnIndex = 0; currentColumnIndex < this->size; currentColumnIndex++)
			{
				if (this->m_matrix[currentRowIndex][currentColumnIndex]->getWeight())
				{
					// delete this->m_matrix[currentRowIndex][currentColumnIndex]->getConnectingLine();
					this->addEdge(currentRowIndex, currentColumnIndex);
				}
			}
		}

		for (int currentColumnIndex = currentStartColumnIndex; currentColumnIndex < this->size; currentColumnIndex++)
		{

			AdjacencyMatrixNode* pCurrentConnectionNode = this->m_matrix[currentRowIndex][currentColumnIndex];

			if (pCurrentConnectionNode->getWeight())
			{
				renderWindow.draw(*pCurrentConnectionNode->getConnectingLine());
			}
		 }

		pCurrentRowNode->draw(renderWindow);

		currentStartColumnIndex++;
	}
}

Node* AdjacencyMatrix::getNodePointerFromKey(int index)
{
	return this->m_pointerToNodes[index];
}

double AdjacencyMatrix::getWeightFromKey(int index1, int index2)
{
	return this->m_matrix[index1][index2]->getWeight();
}

void AdjacencyMatrix::setStartNode(Node* pNode)
{
	this->m_pStartNode = pNode;
}

std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& currentMatrix)
{
	for (int currentRow = 0; currentRow < currentMatrix.m_matrix.size(); currentRow++)
	{
		std::string currentRowParsed(std::to_string(currentRow));

		std::string currentRowString("Row " + std::to_string(currentRow) + ": [");

		for (int currentColumn = 0; currentColumn < currentMatrix.m_matrix.size(); currentColumn++)
		{
			currentRowString = currentRowString.append(std::to_string(static_cast<int>(currentMatrix.m_matrix[currentRow][currentColumn]->getWeight())));

			if (currentColumn != currentMatrix.m_matrix.size()-1)
			{
				currentRowString.append(", ");
			}
			 
		}

		os << currentRowString << "]" << std::endl;
	}
	return os;
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	for (Node* pCurrentNode : this->m_pointerToNodes)
	{
		delete pCurrentNode;
	}

	for (std::vector<AdjacencyMatrixNode*>& currentRow : this->m_matrix)
	{
		for (AdjacencyMatrixNode* pCurrentMatrixNode : currentRow)
		{
			delete pCurrentMatrixNode;
		}
	}
}

AdjacencyMatrixNode::AdjacencyMatrixNode(double weight, LineShape* connectingLine)
{
	this->weight = weight;
	this->connectingLine = connectingLine;
}

double AdjacencyMatrixNode::getWeight()
{
	return this->weight;
}

LineShape* AdjacencyMatrixNode::getConnectingLine()
{
	return this->connectingLine;
}

void AdjacencyMatrixNode::updateWeight(double newWeight)
{
	this->weight = newWeight;
}

void AdjacencyMatrixNode::updateConnectingLine(LineShape* newConnectingLine)
{
	this->connectingLine = newConnectingLine;
}

AdjacencyMatrixNode::~AdjacencyMatrixNode()
{
	delete this->connectingLine;
}
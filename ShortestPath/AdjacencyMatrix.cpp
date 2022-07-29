#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix() : size(0) {}

void AdjacencyMatrix::addVertex(Node* pNodeToAdd)
{
	this->m_pointerToNodes.push_back(pNodeToAdd);

	for (int row = 0; row < this->size; row++)
	{
		this->m_matrix[row].push_back(0);
	}

	this->m_matrix.push_back(std::vector<double>(++this->size));
}

void AdjacencyMatrix::addEdge(Node* pNode1, Node* pNode2, double weight)
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
		this->m_matrix[indexToFirstNode][indexToSecondNode] = weight;
		this->m_matrix[indexToSecondNode][indexToFirstNode] = weight;
	}
}

void AdjacencyMatrix::addEdge(int indexNode1, int indexNode2, double weight)
{
	this->addEdge(this->m_pointerToNodes[indexNode1], this->m_pointerToNodes[indexNode2], weight);
}


Node* AdjacencyMatrix::getNodePointerFromKey(int index)
{
	return this->m_pointerToNodes[index];
}

double AdjacencyMatrix::getWeightFromKey(int index1, int index2)
{
	return this->m_matrix[index1][index2];
}

std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& currentMatrix)
{
	for (int currentRow = 0; currentRow < currentMatrix.m_matrix.size(); currentRow++)
	{
		std::string currentRowParsed(std::to_string(currentRow));

		std::string currentRowString("Row " + std::to_string(currentRow) + ": [");

		for (int currentColumn = 0; currentColumn < currentMatrix.m_matrix.size(); currentColumn++)
		{
			currentRowString = (currentRowString.append(std::to_string(static_cast<int>(currentMatrix.m_matrix[currentRow][currentColumn]))));

			if (currentColumn != currentMatrix.m_matrix.size()-1)
			{
				currentRowString.append(", ");
			}
			 
		}

		os << currentRowString << "]" << std::endl;
	}
	return os;
}
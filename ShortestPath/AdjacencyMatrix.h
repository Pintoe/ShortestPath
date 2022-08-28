#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "PositionalNode.h"
#include "LineShape.h"

class AdjacencyMatrixNode
{
public:

	AdjacencyMatrixNode(double, LineShape*);

	double getWeight();
	LineShape* getConnectingLine();

	void updateWeight(double);
	void updateConnectingLine(LineShape*);

	~AdjacencyMatrixNode();
private:
	double weight;
	LineShape* connectingLine;
};

class AdjacencyMatrix
{
public:
	AdjacencyMatrix();

	int size;

	void addVertex(Node*);
	void addEdge(Node*, Node*);
	void addEdge(int, int);

	// std::vector<std::vector<double>>& getMatrix();
	// std::vector<Node*>& getPointerToNodes();

	void drawConnections(sf::RenderWindow&);

	double getWeightFromKey(int, int);
	Node* getNodePointerFromKey(int);

	void setStartNode(Node*);

	friend std::ostream& operator<<(std::ostream&, const AdjacencyMatrix&);

	~AdjacencyMatrix();
private:
	Node* m_pStartNode;
	std::vector<std::vector<AdjacencyMatrixNode*>> m_matrix;
	std::vector<Node*> m_pointerToNodes;
};


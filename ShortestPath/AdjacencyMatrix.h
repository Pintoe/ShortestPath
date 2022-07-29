#pragma once

#include <iostream>
#include "PositionalNode.h"

class AdjacencyMatrix
{
public:
	AdjacencyMatrix();

	int size;

	void addVertex(Node*);
	void addEdge(Node*, Node*, double);
	void addEdge(int, int, double);

	// std::vector<std::vector<double>>& getMatrix();
	// std::vector<Node*>& getPointerToNodes();

	double getWeightFromKey(int index1, int index2);
	Node* getNodePointerFromKey(int index);

	friend std::ostream& operator<<(std::ostream&, const AdjacencyMatrix&);
private:
	std::vector<std::vector<double>> m_matrix;
	std::vector<Node*> m_pointerToNodes;
};


// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// cheapnode.hpp

#ifndef CHEAPNODE_H
#define CHEAPNODE_H

#include "node.hpp"

#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class CheapNode
{
	public:
		// Methods
		CheapNode();
		CheapNode(Node* parent);
		CheapNode(const CheapNode &parent);
		CheapNode(unsigned long long incomingCurrentState, unsigned short incomingDepth);
		~CheapNode();

		// Psuedo-DFA values
		unsigned long long currentState;
		unsigned short depth;

		// Nodes
		vector<CheapNode*>* children;
};

#endif

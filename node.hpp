// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// node.hpp

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include "stdlib.h"

using namespace std;

class Node
{
	public:
		// Methods
		Node();
		Node(unsigned long long currentState, unsigned short prevInput, Node* parent);
		~Node();

		unsigned int heuristic();
		void printChildren();
		void print();

		// Psuedo-DFA values
		unsigned long long currentState;
		unsigned short prevInput;

		// Nodes
		vector<Node*>* children;
		Node* parent;
};

#endif

// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// tree.hpp

#ifndef TREE_H
#define TREE_H

#include "node.hpp"
#include "stdlib.h"
#include <functional>
#include <stack>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

class Tree
{
	public:
		Tree(unsigned long long incomingMultiple, vector<unsigned short>* incomingSymbols);
		~Tree();
		Node* solve();
		Node* root;

	private:
		unsigned long long multiple;
		vector<unsigned short>* symbols;
		vector<unsigned short>* relaxed;

		void setChildren(Node* currentNode);
		void setChildrenRelaxed(Node* currentNode);
		void sortChildren(Node* currentNode);
		unsigned long long transition(unsigned long long currentState, unsigned short nextInput);
		unsigned short solveDFS();
};

#endif

// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// node.cpp

#include "node.hpp"

using namespace std;

// Used for root node in tree
Node::Node()
{
	this->currentState = 0;
	this->prevInput = 0;
	this->parent = NULL;
	this->children = NULL;
}

// Supply with both value of node (transition function) and input symbol used to arrive there.
Node::Node(unsigned long long currentState, unsigned short prevInput, Node* parent)
{
	this->currentState = currentState;
	this->prevInput = prevInput;
	this->parent = parent;
	this->children = NULL;
}

Node::~Node()
{
	free(parent);
	free(children);
}

unsigned int Node::heuristic()
{
	return 0;
}

void Node::printChildren()
{
	for(unsigned short i = 0; i < this->children->size(); i++)
	{
		cout << endl;
		cout << "CHILD NUMBER: " << i << endl;
		cout << "CURRENT STATE: " << this->children->at(i)->currentState << endl;
		cout << "PREVIOUS INPUT: " << this->children->at(i)->prevInput << endl;
	}
}

void Node::print()
{
	cout << endl;
        cout << "CURRENT STATE: " << this->currentState << endl;
        cout << "PREVIOUS INPUT: " << this->prevInput << endl;
}

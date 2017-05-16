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
	this->gvalue = 0;
	this->hvalue = 65535;
	this->fvalue = 0;
}

// Supply with both value of node (transition function) and input symbol used to arrive there.
Node::Node(unsigned long long currentState, unsigned short prevInput, Node* parent)
{
	this->currentState = currentState;
	this->prevInput = prevInput;
	this->parent = parent;
	this->children = NULL;
	this->gvalue = parent->gvalue + 1;
	this->hvalue = 65535;
	this->fvalue = 0;
}

Node::~Node()
{
	free(parent);
	free(children);
}

void Node::printChildren()
{
	for(unsigned short i = 0; i < this->children->size(); i++)
	{
		cout << endl;
		cout << "CHILD NUMBER: " << i << endl;
		this->children->at(i)->print();
	}
}

void Node::print()
{
	cout << endl;
        cout << "CURRENT STATE: " << this->currentState << endl;
        cout << "PREVIOUS INPUT: " << this->prevInput << endl;
	cout << "H-VALUE: " << this->hvalue << endl;
	cout << "G-VALUE: " << this->numParents() << endl;
}

unsigned short Node::numParents() const
{
	unsigned short parents = 0;
	Node * T = this->parent;

	while(T != NULL)
	{
		T = T->parent;
		parents++;
	}

	return parents;
}

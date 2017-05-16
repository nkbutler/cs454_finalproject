// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// cheapnode.cpp

#include "cheapnode.hpp"

using namespace std;

// Used for allowing array [] construction of CheapNode class
CheapNode::CheapNode()
{
	this->currentState = 0;
	this->depth = 0;
	this->children = NULL;
}

// Used for root node in tree
CheapNode::CheapNode(Node* parent)
{
	this->currentState = parent->currentState;
	this->depth = parent->gvalue;
	this->children = NULL;
}

CheapNode::CheapNode(const CheapNode &parent)
{
	this->currentState = parent.currentState;
	this->depth = parent.depth;
	this->children = NULL;
}

// Supply with both value of node (transition function) and input symbol used to arrive there.
CheapNode::CheapNode(unsigned long long incomingCurrentState, unsigned short incomingDepth)
{
	this->currentState = incomingCurrentState;
	this->depth = incomingDepth;
	this->children = NULL;
}

CheapNode::~CheapNode()
{
	for(unsigned short i = 0; i < 9; i++)
	{
		free(this->children->at(i));
	}

	free(this->children);
}

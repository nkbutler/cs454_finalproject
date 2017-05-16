// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// tree.cpp

#include "tree.hpp"

using namespace std;

// Custom struct to use equality operator in the unordered_set hash of Node pointers
struct PointedObjEq
{
	bool operator()(Node const * a, Node const * b) const
	{
		return a->currentState == b->currentState;
	}
};

// Custom struct to use in creating hash key values for Node pointers
struct PointedObjHash
{
	size_t operator()(Node* const &c) const
	{
		return hash<unsigned long long>{}(c->currentState);
	}
};

// Comparator class for use in the priority queue (want lowest values at top so provide Greater Than function).
class Comparator  
{
        public:
                bool operator()(const Node * a, const Node * b)
                {
                        return (a->fvalue > b->fvalue);
                	// return (a->gvalue + a->hvalue > b->gvalue + b->hvalue);
		}
};

Tree::Tree(unsigned long long incomingMultiple, vector<unsigned short>* incomingSymbols)
{
	this->multiple = incomingMultiple;
	this->symbols = incomingSymbols;
	this->root = new Node();
}

// Used for DFS searches from the supplied node
Tree::Tree(unsigned long long incomingMultiple, Node* currentNode)
{
	this->multiple = incomingMultiple;
	this->symbols = new vector<unsigned short>;
        for(unsigned short i = 1; i < 10; i++)
        {
                symbols->push_back(i);
        }
	this->root = currentNode;
}

Tree::~Tree()
{
	free(symbols);
	free(root);
}

Node* Tree::solve()
{
	unsigned long long parentMod;
	unsigned long long childMod;
	Node *N = NULL;
	Node *C = NULL;
	Node *X = NULL;

	unordered_map<unsigned long long, Node*> openSet;
	unordered_map<unsigned long long, Node*> closedSet;
	priority_queue<Node*, vector<Node*>, Comparator> Q;

	Q.push(root);

	while(!Q.empty())
	{
		N = Q.top();
		Q.pop();
		
		parentMod = N->currentState;

		// Delete current node from open set
		if(openSet.find(parentMod) != openSet.end())
		{
			openSet.erase(parentMod);	
			// cout << "ERASED FROM OPEN SET" << endl;
		}		

		// Add current node to closed set
		if(N != root)
		{
			closedSet.insert({parentMod, N});
			// cout << "INSERTED INTO CLOSED SET" << endl;
		}

		if(N->currentState == 0 && N != root)
		{
			Node * P = N;
			vector<unsigned short> transitions;

			while(P->parent != NULL)
			{
				transitions.push_back(P->prevInput);
				P = P->parent;
			}

			cout << endl << "Solution = ";

			string solution;
			for(int i = transitions.size() - 1; i >= 0; i--)
			{
				solution += to_string(transitions.at(i));
			}
			cout << solution << endl << endl;
			
			cout << "QUEUE SIZE: " << Q.size() << endl;
			return N;
		}

		setChildren(N);

		// Push children of current node if child modulo values have not yet been encountered.
		for(unsigned int i = 0; i < N->children->size(); i++)
		{
			childMod = N->children->at(i)->currentState;
			// cout << "CHILDMOD: " << childMod << endl;

			// Skip child if already in the Closed Set
			if(closedSet.find(childMod) != closedSet.end())
			{
				// cout << "SKIP" << endl;
				continue;
			}
			
			// Skip child if already in the Open Set and child node is worse
			if(openSet.find(childMod) != openSet.end())
			{
				// cout << "MADE IT IN" << endl;
				N->children->at(i)->gvalue = N->gvalue + 1;
				X = openSet[childMod];

				if(X->gvalue <= N->children->at(i)->gvalue)
				{
					// cout << "SKIP" << endl;
					continue;
				}

				openSet.insert({childMod, N->children->at(i)});
				// N->children->at(i)->hvalue = solveDFS(N->children->at(i));
                                N->children->at(i)->hvalue = 0;
				N->children->at(i)->fvalue = N->children->at(i)->hvalue + N->children->at(i)->gvalue;
				Q.push(N->children->at(i));
				// cout << "QUEUE SIZE: " << Q.size() << endl;
			}

			// Add child to Open Set if not already there
			if(openSet.find(childMod) == openSet.end())
			{
				openSet.insert({childMod, N->children->at(i)});
				N->children->at(i)->gvalue = N->gvalue + 1;
				// N->children->at(i)->hvalue = solveDFS(N->children->at(i));
                        	N->children->at(i)->hvalue = 0;
				N->children->at(i)->fvalue = N->children->at(i)->hvalue + N->children->at(i)->gvalue;
				Q.push(N->children->at(i));
				// cout << "QUEUE SIZE: " << Q.size() << endl;
			}
			// cout << "NOTHING PUSHED" << endl;
		}
	}

	return NULL;
}

void Tree::setChildren(Node* currentNode)
{
        currentNode->children = new vector<Node*>;

        for(unsigned short i = 0; i < this->symbols->size(); i++)
        {
                currentNode->children->
		push_back(new Node(transition(currentNode->currentState, this->symbols->at(i)), this->symbols->at(i), currentNode));
	}
}

// Create children using all symbols 1-9 for use in DFS
void Tree::setChildrenRelaxed(CheapNode* currentNode)
{
	
	// cout << "RELAXED" << endl;
	// cout << "CURRENT STATE: " << currentNode.currentState << endl;
	// cout << "CURRENT DEPTH: " << currentNode.depth << endl;

        currentNode->children = new vector<CheapNode*>(9);

        for(unsigned short i = 0; i < 9; i++)
        {
		// cout << "PUSH CHILD" << endl;
               	CheapNode * temp = new CheapNode(transition(currentNode->currentState, i + 1), currentNode->depth + 1);
		currentNode->children->push_back(temp);
	}
	

	/*
	currentNode.children = new CheapNode[9];
	for(unsigned short i = 0; i < 9; i++)
	{
		currentNode.children[i] = CheapNode(transition(currentNode.currentState, i + 1), currentNode.depth + 1);
		cout << "CHILD: " << i << endl;
		cout << "STATE: " << currentNode.children[i].currentState << endl;
		cout << "DEPTH: " << currentNode.children[i].depth << endl;
	}
	*/
}

void Tree::sortChildren(Node* N)
{
	sort(N->children->begin(), N->children->end(), [](Node * A, Node * B)
                {return (A->hvalue + A->numParents()) < (B->hvalue + B->numParents());});
}

unsigned long long Tree::transition(unsigned long long currentState, unsigned short nextInput)
{
        return (currentState * 10 + nextInput) % this->multiple;
}

unsigned short Tree::solveDFS(Node* currentNode)
{
	// cout << "DFS" << endl;
	// CheapNode * C; // "root" node of tree
	// CheapNode * N; // current node under examination
	// CheapNode * X; // current child node of N

	unsigned long long currentMod;
	unsigned long long parentMod;
	unsigned long long childMod;
                        
	unordered_map<unsigned long long, CheapNode*> closedSet;                       
	queue<CheapNode*> Q;

	// Create new CheapNode "root" using old Node pointer
        CheapNode * C = new CheapNode(currentNode);

	Q.push(C);	

	currentMod = C->currentState;
	// cout << "ROOT STATE: " << currentMod << endl;
                              
        while(!Q.empty())
        {
                CheapNode * N = Q.front();
                Q.pop();

		parentMod = N->currentState;
		// cout << "PARENT STATE: " << parentMod << endl;

		// Add current parent node to the closed set                        
                if(parentMod != currentMod)
			closedSet.insert({parentMod, N});

		// If solution is found, return length of solution
                if(parentMod == 0)
                {
                	return N->depth;
		}

		N->children = new vector<CheapNode*>(9);
		// cout << "N SIZE: " << N->children->size() << endl;

        	for(unsigned short i = 0; i < 9; i++)
        	{
                	// cout << "PUSH CHILD" << endl;
                	CheapNode * temp = new CheapNode(transition(N->currentState, i + 1), N->depth + 1);
                	// cout << "TEMP STATE: " << temp->currentState << endl;
			// cout << "TEMP DEPTH: " << temp->depth << endl;
			// N->children->push_back(temp);
        	
			// ADDED
			childMod = temp->currentState;
			
			if(closedSet.find(childMod) == closedSet.end())
				Q.push(temp);
		}
        } 
	return 65535;
}

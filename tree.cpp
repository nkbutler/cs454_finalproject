// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// tree.cpp

#include "tree.hpp"

using namespace std;

Tree::Tree(unsigned long long incomingMultiple, vector<unsigned short>* incomingSymbols)
{
	this->multiple = incomingMultiple;
	this->symbols = incomingSymbols;
	this->root = new Node();
	this->relaxed = NULL;
	/*
	this->relaxed = new vector<unsigned short>;
        for(unsigned short i = 1; i < 10; i++)
        {
                relaxed->push_back(i);
        }
	*/
}

Tree::~Tree()
{
	free(symbols);
	free(root);
}

Node* Tree::solve()
{
	Node *N = NULL;

	stack<Node*>* S = new stack<Node*>;
	vector<size_t>* visited = new vector<size_t>;

	S->push(root);

	while(!S->empty())
	{
		N = S->top();
		S->pop();

		if(N != root)
			visited->push_back(hash<unsigned long long>{}(N->currentState));

		if(N->currentState == 0 && N != root)
		{
			Node * P = N;
			vector<unsigned short>* transitions = new vector<unsigned short>;

			while(P->parent != NULL)
			{
				transitions->push_back(P->prevInput);
				P = P->parent;
			}

			cout << endl << "Solution = ";

			string solution;
			for(int i = transitions->size() - 1; i >= 0; i--)
			{
				solution += to_string(transitions->at(i));
			}
			cout << solution << endl << endl;

			free(visited);
			free(transitions);
			
			return N;
		}

		setChildren(N);
		// sortChildren(N);

		// Push children of current node if child states not yet seen
		for(unsigned int i = 0; i < N->children->size(); i++)
		{
			if(find(visited->begin(), visited->end(), hash<unsigned long long>{}(N->children->at(i)->currentState)) == visited->end())
			{
				S->push(N->children->at(i));
			}
		}
	}

	free(visited);

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

void Tree::setChildrenRelaxed(Node* currentNode)
{
        currentNode->children = new vector<Node*>;
         
        for(unsigned short i = 0; i < this->relaxed->size(); i++)
        {
                currentNode->children-> 
                push_back(new Node(transition(currentNode->currentState, this->relaxed->at(i)), this->relaxed->at(i), currentNode));
        }
}

void Tree::sortChildren(Node* N)
{
	
}

unsigned long long Tree::transition(unsigned long long currentState, unsigned short nextInput)
{
        return (currentState * 10 + nextInput) % this->multiple;
}

unsigned short Tree::solveDFS()
{
        Node *N = NULL;
	unsigned short distance = 0;
                        
        queue<Node*>* Q = new queue<Node*>;
        vector<size_t>* visited = new vector<size_t>;
                       
        Q->push(root);   
                                
        while(!Q->empty())
        {
                N = Q->front();
                Q->pop();
                        
                if(N != root)
                        visited->push_back(hash<unsigned long long>{}(N->currentState));
                 
                if(N->currentState == 0 && N != root)
                {
                        Node * P = N;
                        vector<unsigned short>* transitions = new vector<unsigned short>;
                
                        while(P->parent != NULL)
                        {
                                transitions->push_back(P->prevInput);
                                P = P->parent;
				distance++;
                        }
                         
                        cout << endl << "Solution = ";
         
                        string solution;
                        for(int i = transitions->size() - 1; i >= 0; i--)
                        {
                                solution += to_string(transitions->at(i));
                        }
                        cout << solution << endl << endl;

                        free(visited);
                        free(transitions);
                
                        return distance;
                }

		setChildrenRelaxed(N);
 
                for(unsigned int i = 0; i < N->children->size(); i++)
                {
                        if(find(visited->begin(), visited->end(), hash<unsigned long long>{}(N->children->at(i)->currentState)) == visited->end())
                        {
                                Q->push(N->children->at(i));
                        }
                }
        }
 
        free(visited);

	return distance;
}		

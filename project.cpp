// Nick Butler, Jan Reinacher, Bryan Ward
// CS 454
// Semester Project
// project.cpp

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

#include "tree.hpp"
#include "node.hpp"

using namespace std;

unsigned long long getInput(vector<unsigned short>* incomingSymbols);

int transition(int currState, int k, int nextInput) {
	return (currState * 10 + nextInput) % k;
}
   
string MinString(int alphabet[], int alphaSize, int mult) {
  
  vector<int> visited;
  vector<int> parent;
  vector<int> path;
  for (int i = 0; i < mult; i++){
    parent.push_back(0);
    path.push_back(0);
    visited.push_back(0);
  }
  queue<int> bfs;
  int currentState, nextState;
  bfs.push(0);
  while(!bfs.empty()){
    currentState = bfs.front();
    bfs.pop();
    for(int i = 0; i < alphaSize; i++) {
      nextState = transition(currentState, mult, alphabet[i]);
      if(visited[nextState] == 0) {
        bfs.push(nextState);
        path[nextState] = alphabet[i];
        visited[nextState] = 1;
        parent[nextState] = currentState;
        if (nextState == 0)
          break;
      }  
    }
  }
  string output;
  currentState = 0;
  output = to_string(path[currentState]);
  currentState = parent[currentState];
  while(currentState != 0){
    output += to_string(path[currentState]);
    currentState = parent[currentState];
  }
  reverse(output.begin(), output.end());
  return output;
}

int main()
{
	/*
	int distance;
        int k;   
        int alphaSize;
        cout << "Input a positive integer for k: ";
        cin >> k;   
        cout << "What is the size of your alphabet S: ";
        cin >> alphaSize;
        int S[alphaSize];
        cout << "Enter alphabet character by character: " << endl;
        for(int i=0; i < alphaSize; i++) {   
                cin >> S[i];
        }
  	string minimumString = MinString(S, alphaSize, k);
  	cout << "Shortest string accepted by " << k << ": " << minimumString << endl;
  	cout << "Distance travelled: " << minimumString.length() << endl;      
  	cout << endl;
	*/

	// Tree Implementation

	vector<unsigned short>* symbols = new vector<unsigned short>;

	unsigned long long multiple = getInput(symbols);

	Tree * T = new Tree(multiple, symbols);

	Node * N = T->solve();

	N == NULL ?
                        cout << "No solution found...." << endl:
                        cout << "Solution found!" << endl;

	free(T);  	
	free(N);

	return 0;
}

unsigned long long getInput(vector<unsigned short>* incomingSymbols)
{
	unsigned long long multiple;
	unsigned short numSymbols;

	cout << "Please input a positive integer to use as our multiple (max size: 2^64 - 1): ";
        cin >> multiple;
        cout << endl;
        
        cout << "Please enter the number of symbols that we will use: ";
        cin >> numSymbols;
	cout << endl;
        
        cout << "Enter our symbols character by character: " << endl;
        for(unsigned short i = 0; i < numSymbols; i++)
        {
                unsigned short temp;
                cin >> temp;
                incomingSymbols->push_back(temp);
        }	

	return multiple;
}

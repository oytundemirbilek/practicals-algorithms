// Oytun Demirbilek
// 150150032

#ifndef AGENT_H
#define AGENT_H
#include "board.h"
#include <iostream>
#include <vector> 
#include <string> 
using namespace std;
class agent
{
private:
    int winner;
    board sudoku;
    int maximizer_nodes;
    int minimizer_nodes;

public:
    agent();
	agent(char* filename);
    int minimax(int depth, bool maxTurn, int maxDepth, int alpha, int beta);
    pair <int,int> get_node_counts();
	~agent();
};

#endif
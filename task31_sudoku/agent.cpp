// Oytun Demirbilek
// 150150032
#include "agent.h"
#include "board.h"
#include <iostream>
#include <vector> 

using namespace std;

int min(int a, int b) {
    return (a <= b) ? a : b;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}

agent::agent()
{
    this->winner = 0;
}

agent::agent(char* filename)
{
    this->winner = 0;
    board sudoku(filename);
    this->sudoku = sudoku;
    this->minimizer_nodes = 0;
    this->maximizer_nodes = 0;

}

int agent::minimax(int depth, bool maxTurn, int maxDepth, int alpha, int beta){

    vector<vector<int> > all_moves = this->sudoku.find_all_moves();
    int best_value = 0;
    int result = 0;
    if (depth == maxDepth)
        return 0;

    if (maxTurn){
        if (all_moves.size() == 0)
            return -1;
        best_value = -9999999;
        for (int i=0;i<all_moves.size();i++){
            this->maximizer_nodes++;
            this->sudoku.make_move(all_moves[i][0],all_moves[i][1],all_moves[i][2]);
            result = minimax(depth+1,false,maxDepth,alpha,beta);
            this->sudoku.undo_move(all_moves[i][0],all_moves[i][1]);
            best_value = max(best_value,result);
            alpha = max(alpha,best_value);
            if (beta <= alpha)
                break;
        }
        return best_value;
    }
    else{
        if (all_moves.size() == 0)
            return 1;
        best_value = 9999999;
        for (int i=0;i<all_moves.size();i++){
            this->minimizer_nodes++;
            this->sudoku.make_move(all_moves[i][0],all_moves[i][1],all_moves[i][2]);
            result = minimax(depth+1,true,maxDepth,alpha,beta);
            this->sudoku.undo_move(all_moves[i][0],all_moves[i][1]);
            best_value = min(best_value,result);
            beta = min(beta,best_value);
            if (beta <= alpha)
                break;
        }
        return best_value;
    }

}
pair <int,int> agent::get_node_counts()
{
    return make_pair(this->maximizer_nodes, this->minimizer_nodes);
}



agent::~agent()
{

}

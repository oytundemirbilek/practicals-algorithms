// Oytun Demirbilek
// 150150032

#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector> 
#include <string> 
using namespace std;
class board
{
private:
    vector<vector<int> > grid;
	char* filename;

public:
    board();
	board(char* filename);
    vector<vector<int> > get_grid();
    bool check_row(int row, int num);
    bool check_col(int col, int num);
    bool check_box(int row_start, int col_start, int num);
    vector<vector<int> > find_all_moves();
    void make_move(int row, int col, int val);
    void undo_move(int row, int col);
    void print_board();
	~board();
};

#endif
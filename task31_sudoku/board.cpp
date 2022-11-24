// Oytun Demirbilek
// 150150032
#include "board.h"
#include <iostream>
#include <vector> 
#include <cstdio>


using namespace std;


board::board()
{
    this->filename = NULL;
}

board::board(char* filename)
{
    this->filename = filename;
    int cell;
    vector<int> row;
    FILE * fp = fopen(filename,"r");
    for(int i = 0;i<9;i++){
        for (int j=0;j<9;j++){
            fscanf(fp,"%d ",&cell);
            row.push_back(cell);
        }
        this->grid.push_back(row);
        row.clear();
    }

}

vector<vector<int> > board::get_grid()
{
	return this->grid;
}

void board::print_board()
{
    for(int i = 0;i<9;i++){
        for (int j=0;j<9;j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}


bool board::check_col(int col, int num)
{ //check whether num is present in col or not
    for (int row = 0; row < 9; row++)
        if (this->grid[row][col] == num)
            return true;
    return false;
}
bool board::check_row(int row, int num)
{ //check whether num is present in row or not
    for (int col = 0; col < 9; col++)
        if (this->grid[row][col] == num)
            return true;
    return false;
}
bool board::check_box(int row_start, int col_start, int num)
{ //check whether num is present in 3x3 box or not
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (this->grid[row+row_start][col+col_start] == num)
                return true;
    return false;
}

vector<vector<int> > board::find_all_moves()
{
    vector<vector<int> > move_vector;
    vector<int> move;
    int cell;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cell = this->grid[i][j];
            if (cell == 0){
                for (int num = 1;num<10;num++){  

                    if ( check_col(j,num) + check_row(i,num) + check_box(i-(i%3),j-(j%3),num) == false){

                        move.push_back(i);
                        move.push_back(j);
                        move.push_back(num);
                        move_vector.push_back(move);

                        move.clear();
                    }
                }
            }
        }
    }
	return move_vector;
}

void board::make_move(int row, int col, int val)
{
    this->grid[row][col] = val;
}
void board::undo_move(int row, int col)
{
    this->grid[row][col] = 0;
}

board::~board()
{

}

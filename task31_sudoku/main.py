import numpy as np

INF = 9999999

class Move():
    def __init__(self,loc,values):
        self.loc = loc
        self.values = values

class SudokuBoard():
    def __init__(self):
        self.grid = np.loadtxt('input.txt')
        unique, counts = np.unique(self.grid, return_counts=True)
        self.solvable = (counts[0] >= 1) & (counts[0] <= 15)
        if self.solvable: self.state = "Playing"
        else: self.state = "Not Playable"
        self.value = 0
        self.rows, self.cols = self.grid.shape

    def find_all_moves(self):
        # Check if there is any possible moves left on the board.
        all_numbers = np.arange(1,10)
        move_list =[]
        for i in range(self.rows):
            for j in range(self.cols):
                if self.grid[i,j] == 0:
                    # Numbers placed in the row.
                    row_numbers = self.grid[i]
                    row_numbers = row_numbers[row_numbers != 0]

                    # Numbers placed in the column.
                    col_numbers = self.grid[:,j]
                    col_numbers = col_numbers[col_numbers != 0]

                    # Numbers placed in the box.
                    box_idx_x = i//3 * 3
                    box_idx_y = j//3 * 3
                    box_numbers = self.grid[box_idx_x:box_idx_x+3 , box_idx_y:box_idx_y+3].flatten()
                    box_numbers = box_numbers[box_numbers != 0]

                    # Union of all.
                    row_col = np.union1d(row_numbers,col_numbers)
                    not_allowed = np.union1d(row_col,box_numbers)
                    allowed = np.setdiff1d(all_numbers,not_allowed)

                    if len(allowed) != 0:
                        allowed = np.array([allowed])
                        allowed = np.insert(allowed, 0, i, axis=0)
                        allowed = np.insert(allowed, 0, j, axis=0)
                        move_list.append(allowed)

        # Each row represents a move as: [x_loc, y_loc, value]
        if len(move_list) != 0: return np.hstack(move_list).transpose()
        else: return np.array(move_list)

    def split(self):
        # Split the board into sub-matrices.
        return (self.grid.reshape(9//3, 3, -1, 3).swapaxes(1, 2).reshape(-1, 3, 3))

class MinimaxAgent():
    def __init__(self):
        self.board = SudokuBoard()
    
    def minimax(self, depth, maxTurn, max_depth, alpha, beta): 
        all_moves = self.board.find_all_moves()
        if depth == max_depth:
            return 0

        if maxTurn: 
            if len(all_moves) == 0:
                # If there are no more moves when its maximizer's turn, player will lose the game.
                return -10
            # Maximizer state, it also assigns maximizer turn as false for the next turn.
            bestVal = -INF 
            for move in all_moves:
                self.board.grid[move[0:2]] = move[2]
                value = self.minimax(depth+1, False,max_depth,alpha,beta)
                self.board.grid[move[0:2]] = 0
                bestVal = max(bestVal, value) 
                alpha = max(alpha, bestVal)
                if beta <= alpha:
                    break
            return bestVal
        
        else: 
            # Minimizer state, it also assigns maximizer turn as true for the next turn.
            if len(all_moves) == 0:
                # If there are no more moves when its minimizer's turn, opponent will lose the game.
                return 10
            bestVal = INF 
            for move in all_moves:
                self.board.grid[move[0:2]] = move[2]
                value = self.minimax(depth+1, True,max_depth,alpha,beta)
                self.board.grid[move[0:2]] = 0
                bestVal = min(bestVal, value) 
                beta = min(beta, bestVal)
                if beta <= alpha:
                    break
            return bestVal


ai = MinimaxAgent()
result = ai.minimax(0,True,3, -INF, INF)
print(result)
class Solution:
    def valid(self, board, idx, idy):
        """
        Check if the board is valid after placement at (idx, idy)
        """
        # check row
        s = set()
        for i in range(9):
            if board[idx][i] in s:
                # print('1')
                return False
            if board[idx][i] != '.':
                s.add(board[idx][i])
        
        # check col
        s = set()
        for i in range(9):
            if board[i][idy] in s:
                # print('2')
                return False
            if board[i][idy] != '.':
                s.add(board[i][idy])
    
        # check 3*3
        s = set()
        bx = idx // 3 # base x
        by = idy // 3 # base y
        for i in range(3):
            for j in range(3):
                x = bx * 3 + i
                y = by * 3 + j
                if board[x][y] in s:
                    # print('3', board[x][y], s)
                    return False
                if board[x][y] != '.':
                    s.add(board[x][y])
        
        return True
    
    def solveOne(self, board, where):
        """
        Place one number recursively
        """
        if where == 81:
            return True
        idx = where % 9
        idy = where // 9
        if board[idx][idy] != '.':
            return self.solveOne(board, where + 1)
        for i in range(1, 10):
            board[idx][idy] = str(i)
            # print(where, idx, idy, i, self.valid(board, idx, idy))
            # print(board)
            if self.valid(board, idx, idy) and self.solveOne(board, where + 1):
                return True
            else:
                board[idx][idy] = '.'
        return False
    
    def solveSudoku(self, board):
        """
        Do not return anything, modify board in-place instead.
        """
        self.solveOne(board, 0)

if __name__ == '__main__':
    # print(Solution().valid(list([['5', '3', '.', '.', '7', '.', '.', '.', '.'], ['6', '.', '.', '1', '9', '5', '.', '.', '.'], ['1', '9', '8', '.', '.', '.', '.', '6', '.'], ['8', '.', '.', '.', '6', '.', '.', '.', '3'], ['4', '.', '.', '8', '.', '3', '.', '.', '1'], ['7', '.', '.', '.', '2', '.', '.', '.', '6'], ['9', '6', '.', '.', '.', '.', '2', '8', '.'], ['.', '.', '.', '4', '1', '9', '.', '.', '5'], ['.', '.', '.', '.', '8', '.', '.', '7', '9']]), 6, 0))
    board = list([["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]])
    Solution().solveSudoku(board)
    print(board)
class Solution:
    def isValidSudoku(self, board):
        # check row
        for i in range(9):
            s = set()
            for j in range(9):
                if board[i][j] in s:
                    return False
                if board[i][j] != '.':
                    s.add(board[i][j])
        
        # check col
        for i in range(9):
            s = set()
            for j in range(9):
                if board[j][i] in s:
                    return False
                if board[j][i] != '.':
                    s.add(board[j][i])
        
        # check 3*3
        for i in range(3):
            for j in range(3):
                s = set()
                for k in range(9):
                    idx = i * 3 + k // 3
                    idy = j * 3 + k % 3
                    if board[idx][idy] in s:
                        return False
                    if board[idx][idy] != '.':
                        s.add(board[idx][idy])
        
        return True

if __name__ == '__main__':
    print(Solution().isValidSudoku(list([["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]])))
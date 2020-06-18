'''
Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
[[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
'''
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        length = len(matrix)
        for idx, l in enumerate(range(length, 1, -2)):

            for i in range(l - 1):
                a = (idx + l - 1 - i) % length
                b = (length - idx - 1) % length
                tmp = matrix[idx][idx + i]
                matrix[idx][idx + i] = matrix[a][idx]
                matrix[a][idx] = matrix[b][a]
                matrix[b][a] = matrix[idx + i][b]
                matrix[idx + i][b] = tmp
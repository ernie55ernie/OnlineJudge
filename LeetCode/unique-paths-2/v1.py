class Solution:
	def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
		table = []
		m = len(obstacleGrid)
		n = len(obstacleGrid[0])
		for i in range(m + 1):
			table.append([0] * (n + 1))
		table[0][1] = 1
		for i in range(1, m + 1):
			for j in range(1, n + 1):
				if obstacleGrid[i - 1][j - 1]:
					table[i][j] = 0
				else:
					table[i][j] = table[i - 1][j] + table[i][j - 1]
		return table[-1][-1]
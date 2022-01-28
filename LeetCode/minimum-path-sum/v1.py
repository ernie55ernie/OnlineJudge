class Solution:
	def minPathSum(self, grid: List[List[int]]) -> int:
		m = len(grid)
		n = len(grid[0])
		table = []
		for i in range(m + 1):
			table.append([0] * (n + 1))
		for i in range(1, m + 1):
			table[i][1] = table[i - 1][1] + grid[i - 1][0]
		for j in range(1, n + 1):
			table[1][j] = table[1][j - 1] + grid[0][j - 1]
		for i in range(2, m + 1):
			for j in range(2, n + 1):
				if table[i - 1][j] > table[i][j - 1]:
					table[i][j] = table[i][j - 1] + grid[i - 1][j - 1]
				else:
					table[i][j] = table[i - 1][j] + grid[i - 1][j - 1]

		return table[-1][-1]
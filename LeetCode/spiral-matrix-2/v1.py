#n = 1
#[[1]]
class Solution:
	def generateMatrix(self, n: int) -> List[List[int]]:
		result = []
		for i in range(n):
			result.append([0] * n)
		# 0 for right, 1 for down, 2 for left, and 3 for up
		idx, idy, direct, numbering, edge = -1, 0, 0, 0, 0
		while numbering < n * n:
			if direct == 0:
				if idx + 1 > n - 1 - edge:
					direct = 1
					continue
				else:
					idx += 1
					numbering += 1
					result[idy][idx] = numbering
			elif direct == 1:
				if idy + 1 > n - 1 - edge:
					direct = 2
					continue
				else:
					idy += 1
					numbering += 1
					result[idy][idx] = numbering
			elif direct == 2:
				if idx - 1 - edge < 0:
					direct = 3
					edge += 1
					continue
				else:
					idx -= 1
					numbering += 1
					result[idy][idx] = numbering
			elif direct == 3:
				if idy - 1 - edge < 0:
					direct = 0
					continue
				else:
					idy -= 1
					numbering += 1
					result[idy][idx] = numbering
			# print(idx, idy, numbering, direct, edge, result)
			
		return result
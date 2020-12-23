#[[1,3],[2,6],[8,10],[15,18]]
#[[1,6],[8,10],[15,18]]
#
#[[1,4],[4,5]]
#[[1,5]]
from collections import OrderedDict

class Solution:
	def merge(self, intervals: List[List[int]]) -> List[List[int]]:
		marks = OrderedDict()

		for interval in intervals:
			low, high = interval
			if low in marks:
				marks[low].append(1)
			else:
				marks[low] = [1]

			if high in marks:
				marks[high].append(-1)
			else:
				marks[high] = [-1]

		merged = []
		num_list = 0
		left = -1
		for key, value in marks.items():
			if num_list == 0 and left == -1:
				left = key
			num_list += sum(value)

			if num_list == 0:
				merged.append([left, key])
				left = -1

		return merged
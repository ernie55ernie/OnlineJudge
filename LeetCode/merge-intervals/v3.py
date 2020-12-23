#[[1,3],[2,6],[8,10],[15,18]]
#[[1,6],[8,10],[15,18]]
#
#[[1,4],[4,5]]
#[[1,5]]

class Solution:
	def merge(self, intervals: List[List[int]]) -> List[List[int]]:
		marks = dict()

		for interval in intervals:
			low, high = interval
			marks[low] = marks.get(low, 0) + 1

			marks[high] = marks.get(high, 0) - 1

		keys = sorted(marks.keys(), reverse=False)
		merged = []
		num_list = 0
		left = -1
		for key in keys:
			value = marks[key]
			if num_list == 0 and left == -1:
				left = key
			num_list += value
			print(key, num_list)

			if num_list == 0:
				merged.append([left, key])
				left = -1

		return merged
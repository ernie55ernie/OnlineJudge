#intervals = [[1,3],[6,9]], newInterval = [2,5]
#[[1,5],[6,9]]
#
#intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
#[[1,2],[3,10],[12,16]]
#
#intervals = [], newInterval = [5,7]
#[[5,7]]
#
#intervals = [[1,5]], newInterval = [2,3]
#[[1,5]]
#
#intervals = [[1,5]], newInterval = [2,7]
#[[1,7]]
#[[1,5]]
#[0,0]
#[[0,0],[1,4],[6,8],[9,11]]
#[0,9]
#[[0,2],[4,5],[6,9],[11,15],[18,19]]
#[2,2]
class Solution:
	def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
		counts = dict()
		intervals.append(newInterval)
		for interval in intervals:
			low, high = interval
			if low == high:
				count = counts.get(low, (0, False))
				count = (count[0], True)
				counts[low] = count
			else:
				count = counts.get(low, (0, False))
				count = (count[0] + 1, count[1])
				counts[low] = count
				count = counts.get(high, (0, False))
				count = (count[0] - 1, count[1])
				counts[high] = count

		# print(counts)
		keys = sorted(counts.keys())
		inserted = []
		left = -1
		value = 0
		for key in keys:
			count = counts[key]
			value += count[0]
			# print(key, count, value)
			if value > 0 and left == -1:
				left = key
			if value == 0 and left != -1:
				inserted.append([left, key])
				left = -1
				continue
			if count[1] and value == 0:
				inserted.append([key, key])
		return inserted
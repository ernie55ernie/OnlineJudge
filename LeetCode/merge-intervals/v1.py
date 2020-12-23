#[[1,3],[2,6],[8,10],[15,18]]
#[[1,6],[8,10],[15,18]]
#
#[[1,4],[4,5]]
#[[1,5]]
class Solution:
	def merge(self, intervals: List[List[int]]) -> List[List[int]]:
		low_bounds = dict()
		high_bounds = dict()
		for current_interval in intervals:
			low_bound, high_bound = current_interval
			if low_bound in low_bounds:
				already_in_low_bounds = low_bounds[low_bound]
				if already_in_low_bounds[1] < current_interval[1]:
					low_bounds[low_bound] = current_interval
			elif low_bound in high_bounds:


			if high_bound in high_bounds:
				already_in_high_bounds = high_bounds[high_bound]
				if already_in_high_bounds[0] > current_interval[0]:
					high_bounds[high_bound] = current_interval
			elif high_bound in low_bounds:


		for 
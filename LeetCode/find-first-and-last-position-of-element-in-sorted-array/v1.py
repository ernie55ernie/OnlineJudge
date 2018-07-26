class Solution:
	def searchRange(self, nums, target):
		"""
		:type nums: List[int]
		:type target: int
		:type: List[int]
		"""
		ans = []
		idx = len(nums) // 2
		rng = len(nums) // 4
		while True:
			if rng == 0:
				ans.append(-1)
				break
			if nums[idx] == target and (idx == 0 or nums[idx - 1] < target):
				ans.append(idx)
				break
			elif nums[idx] > target or nums[idx] == target:
				idx -= rng
				rng //= 2
			elif nums[idx] < target:
				idx += rng
				rng //= 2

		while True:
			if rng == 0:
				ans.append(-1)
				break
			if nums[idx] == target and (idx == len(nums) - 1 or nums[idx + 1] > target):
				ans.append(idx)
				break
			elif nums[idx] > target:
				idx -= rng
				rng //= 2
			elif nums[idx] < target or nums[idx] == target:
				idx += rng
				rng //= 2

		return ans
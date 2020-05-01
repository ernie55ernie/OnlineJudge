class Solution:
	def search(self, nums, target):
		"""
		:type nums: List[int]
		:type target: int
		:rtypeL int
		"""
		for i, n in enumerate(nums):
			if n == target:
				return i
		return -1
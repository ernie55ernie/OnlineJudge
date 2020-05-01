class Solution:
	def nextPermutation(self, nums):
		"""
		:type nums: List[int]
		:rtype: void Do not return anything, modify nums in-place instead.
		"""
		for i in reversed(range(1, len(nums))):
			found = False
			if nums[i] > nums[i - 1]:
				for j in reversed(range(i, len(nums))):
					if nums[j] > nums[i - 1]:
						swap_idx = [i - 1, j]
						found = True
						break
			if found:
				break

		try:
			swap_idx
			tmp = nums[swap_idx[0]]
			nums[swap_idx[0]] = nums[swap_idx[1]]
			nums[swap_idx[1]] = tmp
			self.rev(nums, swap_idx[0])
		except:
			self.rev(nums, -1)

	def rev(self, nums, start):
		tmp = []
		for i in range(start + 1, len(nums)):
			tmp.append(nums[i])
		for i in range(len(nums) - start - 1):
			nums[start + i + 1] = tmp[-i - 1]
# [1,2,3]
# [3,2,1]
# [1,1,5]
# [1,2,0,3,0,1,2,4]
# [1,3,2]
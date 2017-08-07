class Solution(object):
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        app = [0] * (n + 1)
        for i in range(n):
        	if nums[i] > 0 and nums[i] <= n:
        		app[nums[i] - 1] += 1
        for i in range(n + 1):
        	if app[i] == 0:
        		return i + 1
# [1,2,0]
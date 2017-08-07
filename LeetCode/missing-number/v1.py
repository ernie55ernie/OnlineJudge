class Solution(object):
    def missingNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        app = [0] * (n + 1)
        for i in range(n):
        	app[nums[i]] += 1
        for i in range(n + 1):
        	if app[i] == 0:
        		return i

#[1,0]
#[0,1]
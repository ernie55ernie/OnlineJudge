class Solution(object):
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        app = {}
        for i in range(n):
        	if nums[i] in app:
        		app[nums[i]] += 1
        	else:
        		app[nums[i]] = 1
        for key, value in app.iteritems():
        	if value == 1:
        		return key
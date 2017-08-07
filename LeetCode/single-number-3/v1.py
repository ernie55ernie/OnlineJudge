class Solution(object):
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        app = {}
        n = len(nums)
        for i in range(n):
        	if nums[i] in app:
        		app[nums[i]] += 1
        	else:
        		app[nums[i]] = 1
       	res = []
        for key, value in app.iteritems():
        	if value == 1:
        		res.append(key)
        return res
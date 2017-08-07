class Solution(object):
    def findDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        app = {}
        res = []
        for i in range(len(nums)):
        	if nums[i] in app and app[nums[i]] == 1:
        		res.append(nums[i])
        		app[nums[i]] += 1
        	else:
        		app[nums[i]] = 1
        return res
class Solution(object):
    def findDisappearedNumbers(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        record = [0] * len(nums)
        dis = []
        for i in range(len(nums)):
        	record[nums[i] - 1] += 1
        for i in range(len(nums)):
        	if record[i] == 0:
        		dis.append(i + 1)
        return dis

print Solution().findDisappearedNumbers([4,3,2,7,8,2,3,1])
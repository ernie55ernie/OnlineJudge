class Solution:
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums or len(nums) == 0:
        	return 0
        new_nums = 1
        j = nums[0]
        removing = []
        for i in range(1, len(nums)):
        	if nums[i] != j:
        		j = nums[i]
        		new_nums += 1
        	else:
        		removing.append(j)
        for num in removing:
        	nums.remove(num)
        return new_nums
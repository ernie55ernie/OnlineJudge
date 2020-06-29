class Solution:
    
    def jump(self, nums: List[int]) -> int:
        if len(nums) <= 1:
            return 0
        
        step = 0
        reachable = 0
        pos = 0
        for i in range(len(nums) - 1):
            if reachable < nums[i] + i:
                reachable = nums[i] + i
            if pos == i:
                pos = reachable
                step = step + 1
        return step
        
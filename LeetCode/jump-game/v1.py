# [2,0,0]
class Solution:
    def canJump(self, nums: List[int]) -> bool:
        farest = 0
        for current in range(len(nums)):
            current_farest = current + nums[current]
            if current_farest > farest:
                farest = current_farest
            if farest <= current:
                break
        if farest >= len(nums) - 1:
            return True
        return False
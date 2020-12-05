# [-2,1,-3,4,-1,2,1,-5,4]
# 6
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        max_sum = nums[0]
        cur_sum = nums[0]
        for ele in nums[1:]:
            if ele > ele + cur_sum:
                cur_sum = ele
            else:
                cur_sum = ele + cur_sum

            if cur_sum > max_sum:
                max_sum = cur_sum
            # print(cur_sum, max_sum)
        
        return max_sum
class Solution:
    
    def searchRange(self, nums, target):
        left = -1
        right = -1
        start = 0
        end = len(nums)
        if end == 0:
            return [-1, -1]
        center = end // 2
        
        while True:
            prev = center
            
            if nums[center] == target:
                if center == len(nums) - 1 or nums[center + 1] != target:
                    right = center
                    break
                else:
                    start = center
                    center = (start + end) // 2
                    
            if nums[center] < target:
                start = center
                center = (start + end) // 2
            if nums[center] > target:
                end = center
                center = (start + end) // 2
                
            if (center == 0 and nums[center] > target) or (center == len(nums) - 1 and nums[center] < target) or (prev == center):
                return [left, right]
        
        start = 0
        end = len(nums)
        center = len(nums) // 2

        while True:
            if nums[center] == target:
                if center == 0 or nums[center - 1] != target:
                    left = center
                    break
                else:
                    end = center
                    center = (start + end) // 2
                    
            if nums[center] < target:
                start = center
                center = (start + end) // 2
            if nums[center] > target:
                end = center
                center = (start + end) // 2
            
        
        return [left, right]

if __name__ == '__main__':
    print(Solution().searchRange([5,7,7,8,8,10], 6))
'''
	def searchRange(self, nums, target):
		"""
		:type nums: List[int]
		:type target: int
		:type: List[int]
		"""
		ans = []
		idx = len(nums) // 2
		rng = len(nums) // 4
		while True:
			if rng == 0:
				ans.append(-1)
				break
			if nums[idx] == target and (idx == 0 or nums[idx - 1] < target):
				ans.append(idx)
				break
			elif nums[idx] > target or nums[idx] == target:
				idx -= rng
				rng //= 2
			elif nums[idx] < target:
				idx += rng
				rng //= 2

		while True:
			if rng == 0:
				ans.append(-1)
				break
			if nums[idx] == target and (idx == len(nums) - 1 or nums[idx + 1] > target):
				ans.append(idx)
				break
			elif nums[idx] > target:
				idx -= rng
				rng //= 2
			elif nums[idx] < target or nums[idx] == target:
				idx += rng
				rng //= 2

		return ans
'''

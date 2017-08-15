class Solution(object):
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        left_idx = 0
        right_idx = len(height) - 1
        
        max_area = 0
        while left_idx < right_idx:
            left_height = height[left_idx]
            right_height = height[right_idx]
            
            larger_area = min(left_height, right_height) * (right_idx - left_idx)
            if larger_area > max_area:
                max_area = larger_area
            
            if right_height < left_height:
                right_idx -= 1
            else:
                left_idx += 1
        
        return  max_area
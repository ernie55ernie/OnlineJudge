# [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
# [3, 0, 2, 0, 4]
# [2, 0, 2]
# [5, 4, 1, 2]
class Solution:
    def trap(self, height: List[int]) -> int:
        left = 0 # left trap idx
        right = 0 # right trap idx
        span = 0
        length = len(height)
        table = [0] * (length + 1)
        
        for idx, h in enumerate(height):
            if h < height[left]:
                if h > height[right]:
                    right = idx
                if idx == length - 1 and height[right] < height[left]:
                    trapped = span * (height[right] - height[left])
                    # print(trapped, span, right, left)
                else:
                    trapped = height[left] - h # trapped based on left
                table[idx + 1] = table[idx] + trapped
                span = span + 1
            else:
                left = idx
                right = idx + 1
                table[idx + 1] = table[idx]
                span = 0
                
        return table[-1]
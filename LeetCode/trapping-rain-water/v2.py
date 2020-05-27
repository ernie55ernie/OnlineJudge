# [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
# [3, 0, 2, 0, 4]
# [2, 0, 2]
# [5, 4, 1, 2]
class Solution:
    def trap(self, height: List[int]) -> int:
        length = len(height)
        lleft = 0 # left trap idx
        lright = 0
        rright = length - 1 # right trap idx
        rleft = length - 1
        ltable = [0] * (length + 1)
        rtable = [0] * (length + 1)
        
        for idx, h in enumerate(height):
            if h < height[lleft]:
                if h > height[lright]:
                    lright = idx
                else:
                    trapped = height[lleft] - h # trapped based on left
                    ltable[idx + 1] = ltable[idx] + trapped
            else:
                lleft = idx
                lright = idx
                ltable[idx + 1] = ltable[idx]

            ridx = length - idx
            rh = height[ridx - 1]
            
            if rh < height[rright]:
                if rh > height[rleft]:
                    rleft = ridx
                else:
                    trapped = height[rright] - rh # trapped based on right
                    rtable[ridx - 1] = rtable[ridx] + trapped
            else:
                rleft = ridx - 1
                rright = ridx - 1
                rtable[ridx - 1] = rtable[ridx]
        # print(ltable, lleft)
        # print(rtable, rright)
        if lleft == rright:
            return ltable[lleft] + rtable[rright]
        return min(ltable[-1], rtable[0])
# Time Limit Exceeded [-14,-10,-1,8,-8,-7,-3,-2,14,10,3,3,-1,-15,6,9,-1,6,-2,-6,-8,-15,8,-3,-14,5,-1,-12,-10,-5,-9,-8,1,-3,-15,0,-3,-11,6,-11,7,-6,7,-9,-6,-10,7,1,11,-10,10,-12,-10,3,-7,-9,-7,7,-14,-9,10,14,-2,-4,-4,-10,3,1,-14,-6,5,8,-4,-11,14,-3,-6,-2,13,13,3,0,-14,8,10,-14,6,11,1,7,-13,-4,6,0,-1,10,-3,-13,-4,-2,-11,8,-8]
class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        s = sorted(nums)
        res = []
        
        for i in range(len(s) - 2):
            if i == 0 or (i > 0 and s[i] != s[i - 1]):
                two = - s[i]
                j = i + 1
                k = len(s) - 1
                while j < k:
                    if s[j] + s[k] == two:
                        res.append([s[i], s[j], s[k]])
                        while j < k and s[j] == s[j + 1]:
                            j += 1
                        while j < k and s[k] == s[k - 1]:
                            k -= 1
                        j += 1
                        k -= 1
                    elif s[j] + s[k] > two:
                        k -= 1
                    elif s[j] + s[k] < two:
                        j += 1

        return res
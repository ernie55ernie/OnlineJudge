class Solution(object):
    MOD = 1e9 + 7
    
    def findDerangement(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 0
        if n == 2:
            return 1
        return int((n - 1) * (self.findDerangement(n - 1) + self.findDerangement(n - 2)) % self.MOD)

print(Solution().findDerangement(13))
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
        
        first, second = 0, 1
        for i in range(2, n + 1):
            first, second = second, (first + second) * i % self.MOD
        return int(first)
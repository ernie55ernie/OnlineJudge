class Solution(object):
    def hammingWeight(self, n):
        """
        :type n: int
        :rtype: int
        """
        res = 0
        while n > 0:
        	if n % 2 <> 0:
        		res += 1
        		n -= 1
        	n /= 2
        return res
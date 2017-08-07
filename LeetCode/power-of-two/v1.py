class Solution(object):
    def isPowerOfTwo(self, n):
        """
        :type n: int
        :rtype: bool
        """
        if n == 1:
        	return True
        if n % 2 == 1 or n <= 0:
        	return False
        while n > 2:
        	n /= 2
        	if n % 2 <> 0:
        		return False
        return True
#0
#-16
#10
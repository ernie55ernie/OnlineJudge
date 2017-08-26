class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        if x < 0:
            sign = -1
            x = -x
        else:
            sign = 1
        
        new_x = 0
        while x > 0:
            last_num = x % 10
            new_x = new_x * 10 + last_num
            x /= 10
            
        if new_x > 2**31:
            return 0
        return new_x * sign

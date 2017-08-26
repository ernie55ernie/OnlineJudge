class Solution(object):
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        if x < 0:
            return False
        old_x = x
        
        new_x = 0
        while x > 0:
            last_num = x % 10
            new_x = new_x * 10 + last_num
            x /= 10
        
        if new_x == old_x:
            return True
        else:
            return False

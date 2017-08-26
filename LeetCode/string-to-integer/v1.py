class Solution(object):
    def myAtoi(self, str):
        """
        :type str: str
        :rtype: int
        """
        if len(str) == 0:
            return 0
        start_count = False
        sign = 1
        num = 0
        for i in range(len(str)):
            if not start_count and str[i] == ' ':
                continue
            elif not start_count and str[i] == '+':
                sign = 1
                start_count = True
            elif not start_count and str[i] == '-':
                sign = -1
                start_count = True
            elif not str[i].isdigit():
                break
            elif str[i].isdigit():
                start_count = True
                num *= 10
                num += int(str[i])
        result = num * sign
        if result > 2**31 - 1:
            return 2**31 - 1
        if result < -2**31:
            return -2**31
        return result

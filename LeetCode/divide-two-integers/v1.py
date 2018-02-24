class Solution:
    def divide(self, dividend, divisor):
        """
        :type dividend: int
        :type divisor: int
        :rtype: int
        """
        pos = (dividend >= 0) == (divisor >= 0)
        dividend, divisor = abs(dividend), abs(divisor)
        a, b = abs(dividend), abs(divisor)
        res = 0
        q = 1
        # a = q * b + r
        while a >= divisor:
        	a -= b
        	res += q

        	# b = 2b
        	q += q
        	b += b
        	if a < b:
        		b = divisor
        		q = 1

        if pos:
        	return min(2147483647, res)
        else:
        	return max(- 2147483648, - res)
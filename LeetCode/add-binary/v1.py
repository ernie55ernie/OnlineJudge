#'1'
#'111'
class Solution:
	def addBinary(self, a: str, b: str) -> str:
		m = len(a)
		n = len(b)
		if m < n:
			a, b = b, a
			m, n = n, m
		carry = 0
		result = ''
		for i in range(1, m + 1):
			d1 = int(a[-i])
			d2 = 0
			if i <= n:
				d2 = int(b[-i])
			d3 = d1 + d2 + carry
			carry = 0
			if d3 > 1:
				d3 = d3 - 2
				result = str(d3) + result
				carry = 1
			else:
				result = str(d3) + result

		if carry:
			result = '1' + result

		return result
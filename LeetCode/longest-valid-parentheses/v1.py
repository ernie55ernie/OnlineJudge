class Solution:
	def longestValidParentheses(self, s):
		"""
		:type s: str
		:rtype: int
		"""
		val = 0
		left = 0
		right = 0
		right_left = 0
		longest = 0
		for p in s:
			if p == '(':
				val += 1
			elif p == ')':
				val -= 1
				right_left += 1

			right += 1
			if val < 0:
				val = 0
				left = right
				right_left = 0
			elif val == 0:
				if right - left > longest:
					print(right, left)
					longest = right - left
				right_left = 0
		if val > 0 and right_left:
			longest = right_left * 2
			
		return longest

def test(s):
	print(Solution().longestValidParentheses(s))

if __name__ == '__main__':
	test('(()')
	test(')()())')
	test('((((()))))')
	test('(((()')
	test('()))))')
	test('(()()((())))')
	test('()(()')
	test('(()(((()')
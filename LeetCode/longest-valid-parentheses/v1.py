class Solution:
	def longestValidParentheses(self, s):
		"""
		:type s: str
		:rtype: int
		"""
		dp = [] # longest valid parentheses ends at #
		for p in s:
			dp.append(0)
		dp.append(0)

		for i in range(1, len(s)):
			if s[i - 1] == '('and s[i] == ')' :
				dp[i] = dp[i - 2] + 2
			elif s[i - 1] == ')' and s[i] == ')':
				if i > dp[i - 1] and s[i - dp[i - 1] - 1] == '(':
					dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] + 2

		return max(dp)

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
	test('()(())')
	test('(()))())(')
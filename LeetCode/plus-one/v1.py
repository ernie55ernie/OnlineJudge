#[1,2,3]
#[1,2,4]
#[9]
#[1,0]
class Solution:
	def plusOne(self, digits: List[int]) -> List[int]:
		carry = 0
		for i in range(1, len(digits) + 1):
			digits[-i] += 1
			if digits[-i] > 9:
				digits[-i] = 0
				carry = 1
			else:
				carry = 0
				break
		if carry:
			digits = [1] + digits
		return digits
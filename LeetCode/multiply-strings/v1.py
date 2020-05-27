# "2"
# "3"
class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        if num1 == '0' or num2 == '0':
            return '0'
        dictionary = {
            '0' : 0,
            '1' : 1,
            '2' : 2,
            '3' : 3,
            '4' : 4,
            '5' : 5,
            '6' : 6,
            '7' : 7,
            '8' : 8,
            '9' : 9
        }
        if len(num1) < len(num2):
            num1, num2 = num2, num1
        n2 = 0
        for idx, d in enumerate(num2[::-1]):
            n2 += dictionary[d] * 10 ** idx
        result = 0
        for idx, d in enumerate(num1[::-1]):
            result += n2 * dictionary[d] * 10 ** idx
        
        return str(result)
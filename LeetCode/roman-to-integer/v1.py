# "MCMXCVI"
class Solution(object):
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        num = 0
        if 'M' in s:
            thousands = s.count('M')
            num += thousands * 1000
            if 'C' in s[:s.rfind('M') + 1]:
                num -= 100
            s = s[s.rfind('M') + 1:]
        
        if 'D' in s:
            num += 500
            if 'C' in s[:s.rfind('D') + 1]:
                num -= 100
            s = s[s.rfind('D') + 1:]
        
        if 'C' in s:
            hundreds = s.count('C')
            num += hundreds * 100
            if 'X' in s[:s.rfind('C') + 1]:
                num -= 10
            s = s[s.rfind('C') + 1:]
        
        if 'L' in s:
            num += 50
            if 'X' in s[:s.rfind('L') + 1]:
                num -= 10
            s = s[s.rfind('L') + 1:]
        
        if 'X' in s:
            tens = s.count('X')
            num += tens * 10
            if 'I' in s[:s.rfind('X') + 1]:
                num -= 1
            s = s[s.rfind('X') + 1:]
        
        if 'V' in s:
            num += 5
            if 'I' in s[:s.rfind('V') + 1]:
                num -= 1
            s = s[s.rfind('V') + 1:]
        
        if 'I' in s:
            ones = s.count('I')
            num += ones * 1
        
        return num

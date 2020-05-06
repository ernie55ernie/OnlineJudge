class Solution:
    
    def countAndSay(self, n: int) -> str:
        if n == 1:
            return '1'
        s = self.countAndSay(n - 1)
        if len(s) == 1:
            return '1' + s
        current_char = s[0]
        count = 1
        result = ''
        for c in s[1:]:
            if c == current_char:
                count += 1
            else:
                result = result + str(count) + current_char
                count = 1
                current_char = c
        result = result + str(count) + current_char
        return result
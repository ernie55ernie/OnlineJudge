class Solution:
    def maximum69Number (self, num: int) -> int:
        s = str(num)
        c = 0
        for idx in range(len(s)):
            if s[idx] == '9':
                continue
            else:
                c = idx
                break
        return int(s[:c] + '9' + s[c + 1:])
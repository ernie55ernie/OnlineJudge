class Solution:
    def lengthOfLastWord(self, s: str) -> int:
        s = s.strip()
        appear_word = False
        for i in range(len(s)):
            if s[len(s) - 1 - i] == ' ':
                return i
            elif s[len(s) - 1 - i] != ' ':
                appear_word = True
        if appear_word:
            return len(s)
        return 0
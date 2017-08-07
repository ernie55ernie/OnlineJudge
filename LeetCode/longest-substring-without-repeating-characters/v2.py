class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_length = 0
        app = dict()
        lower_idx = 0

        for i in range(len(s)):
            if s[i] in app and app[s[i]] + 1 > lower_idx:
                    lower_idx = app[s[i]] + 1
            if i - lower_idx + 1 > max_length:
                max_length = i - lower_idx + 1
            app[s[i]] = i
        
        return max_length

print Solution().lengthOfLongestSubstring('abcabcbb')
#abcabcbb
#bbbbb
#pwwkew
#dvdf
#abba
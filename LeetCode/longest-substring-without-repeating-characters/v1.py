class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        longest = list([0])
        appearance = list([set()])
        
        for i in range(len(s)):
            longest.append(1)
            appearance.append(set(s[i]))
            for j in range(i):
                idx = j + 1
                if s[i] not in appearance[idx] and len(appearance[idx]) <> 0:
                    longest[idx] = longest[idx] + 1
                    appearance[idx].add(s[i])
                else:
                    appearance[idx].clear()
        
        return max(longest)

print Solution().lengthOfLongestSubstring('abcabcbb')
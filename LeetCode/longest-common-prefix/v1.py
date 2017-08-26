# ["geeksforgeeks", "geeks", "geek", "geezer"]
class Solution(object):
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        if len(strs) == 0:
            return ""
        
        first_str = strs[0]
        lcp = ""
        flag = False
        for i in range(len(first_str)):
            for j in range(1, len(strs)):
                if len(strs[j]) <= i or strs[j][i] != first_str[i]:
                    flag = True
                    break
            if flag:
                break
            lcp += first_str[i]
        return lcp
# "aabcc"
# "dbbca"
# "aadbbcbcac"
# 
# "aabc"
# "abad"
# "aabadabc"
class Solution(object):
    def isInterleave(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        if len(s3) != len(s1) + len(s2):
            return False
        if s3 == s1 + s2 or s3 == s2 + s1:
            return True
        if len(s1) == 0:
            return s2 == s3
        if len(s2) == 0:
            return s1 == s3
        table = []
        for i in range(len(s1) + 2):
            table.append([False] * (len(s2) + 2))
        table[0][0] = True
        for i in range(len(s1) + 1):
            for j in range(len(s2) + 1):
                if i < len(s1):
                    c1 = s1[i]
                else:
                    c1 = ''
                if j < len(s2):
                    c2 = s2[j]
                else:
                    c2 = ''
                if i + j < len(s3):
                    c3 = s3[i + j]
                else:
                    break
                if table[i][j]:
                    if c1 == c3 and c2 == c3:
                        table[i + 1][j] = True
                        table[i][j + 1] = True
                    elif c1 == c3:
                        table[i + 1][j] = True
                    elif c2 == c3:
                        table[i][j + 1] = True
        return table[-2][-2]
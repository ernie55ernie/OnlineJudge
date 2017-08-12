class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        str_idx = 0
        pat_idx = 0
        dp_table = []
        for i in range(len(s) + 1):
            dp_table.append([])
            for j in range(len(p) + 1):
                dp_table[i].append(False)
        dp_table[0][0] = True
        
        for i in range(len(p)):
            if p[i] == '*' and dp_table[0][i - 1]:
                dp_table[0][i + 1] = True
        
        for i in range(len(s)):
            for j in range(len(p)):
                if s[i] == p[j] or p[j] == '.':
                    dp_table[i + 1][j + 1] = dp_table[i][j]
                elif p[j] == '*':
                    if s[i] != p[j - 1] and p[j - 1] != '.':
                        dp_table[i + 1][j + 1] = dp_table[i + 1][j - 1]
                    else:
                        dp_table[i + 1][j + 1] = dp_table[i][j + 1] | dp_table[i + 1][j] | dp_table[i + 1][j - 1]
            
        return dp_table[-1][-1]

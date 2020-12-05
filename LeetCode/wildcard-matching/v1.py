class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        table = [[False] * (len(p) + 1)]
        table[0][0] = True # s and p are empty
        for idx, c in enumerate(p):
            table[0][idx + 1] = table[0][idx] & (c == '*')
            
        for idx, c in enumerate(s):
            table.append([False] * (len(p) + 1))
            for p_idx, p_c in enumerate(p):
                if c == p[p_idx] or p[p_idx] == '?':
                    table[idx + 1][p_idx + 1] = table[idx][p_idx]
                
                if p[p_idx] == '*':
                    table[idx + 1][p_idx + 1] = table[idx][p_idx + 1] | table[idx + 1][p_idx]
        
        return table[-1][-1]
        
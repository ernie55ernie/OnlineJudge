# "aabcc"
# "dbbca"
# "aadbbcbcac"
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
        table = []
        for i in range(len(s1) + 1):
        	table.append([''] * (len(s2) + 1))
        for i in range(len(s1) + 1):
            table[i][0] = ' '
        for i in range(len(s2) + 1):
            table[0][i] = ' '
        for i in range(len(s1)):
        	for j in range(len(s2)):
        		c1 = s1[i]
        		c2 = s2[j]
        		c3 = s3[i + j]
                if not self.no_match(table, i, j + 1) or not self.no_match(table, i + 1, j):
                    if c1 == c3 and c2 == c3:
                        table[i + 1][j + 1] = 'ij'
                    elif c1 == c3:
                        print 'i'
                        table[i + 1][j + 1] = 'i'
                    elif c2 == c3:
                        table[i + 1][j + 1] = 'j'
        print table
        if table[-1][-1] == '':
            return False
        else:
            return True

    def no_match(self, table, i, j):
        if table[i][j] == '':
            return True
        return False
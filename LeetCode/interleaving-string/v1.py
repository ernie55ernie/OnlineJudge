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
        	table.append([False] * (len(s2) + 1))
        for i in range(len(s1)):
        	if s1[i] == s3[i]:
        		table[i + 1][0] = True
        	else:
        		break
        for i in range(len(s2)):
        	if s2[i] == s3[i]:
        		table[0][i + 1] = True
        	else:
        		break
        for i in range(len(s1)):
        	for j in range(len(s2)):
        		c1 = s1[i]
        		c2 = s2[j]
        		c3 = s3[i + j]
        		if c1 == c3 and c2 == c3:
        			table[i + 1][j + 1] = table[i][j + 1] | table[i + 1][j]
        		elif c1 == c3:
        			table[i + 1][j + 1] = table[i + 1][j]
        		elif c2 == c3:
        			table[i + 1][j + 1] = table[i][j + 1]
        		else:
        			table[i + 1][j + 1] = False
        print table
        return table[-1][-1]
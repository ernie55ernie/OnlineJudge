class Solution(object):
    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """
        if numRows == 1:
            return s
        if numRows == 2:
            return ''.join([s[0::2], s[1::2]])
        
        new_str_list = []
        idx = 0
        row_idx = 0
        new_str_list.append(s[0::(numRows * 2 - 2)])
        for i in range(numRows - 2):
            out_idx = 1 + i
            mid_idx = numRows * 2 - 3 - i
            mid = False
            while (mid and mid_idx < len(s)) or (out_idx < len(s)):
                if mid:
                    new_str_list.append(s[mid_idx])
                    mid_idx += numRows * 2 - 2
                    mid = False
                else:
                    new_str_list.append(s[out_idx])
                    out_idx += numRows * 2 - 2
                    mid = True
        new_str_list.append(s[(numRows - 1)::(numRows * 2 - 2)])
        
        return ''.join(new_str_list)
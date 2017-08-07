class Solution(object):
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        _max_length = 0
        _max_string = ''
        _left_idx = 0
        _mid_idx = 0
        _right_idx = 0
        if len(s) == 1:
            return s
        
        for i in range(len(s)):
            # length is odd
            _left_idx = i
            _right_idx = i
            while _left_idx > 0 and _right_idx < len(s) - 1 and s[_left_idx - 1] == s[_right_idx + 1]:
                _left_idx -= 1
                _right_idx += 1
            if _right_idx - _left_idx + 1 > _max_length:
                _max_length = _right_idx - _left_idx + 1
                _max_string = s[_left_idx : _right_idx + 1]
        
        for i in range(len(s) - 1):
            # length is even
            if s[i] == s[i + 1]:
                _left_idx = i
                _right_idx = i + 1
                while _left_idx > 0 and _right_idx < len(s) - 1 and s[_left_idx - 1] == s[_right_idx + 1]:
                    _left_idx -= 1
                    _right_idx += 1
                if _right_idx - _left_idx + 1 > _max_length:
                    _max_length = _right_idx - _left_idx + 1
                    _max_string = s[_left_idx : _right_idx + 1]
        
        return _max_string
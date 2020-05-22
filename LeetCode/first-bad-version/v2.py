# The isBadVersion API is already defined for you.
# @param version, an integer
# @return a bool
# def isBadVersion(version):
from math import ceil

class Solution:
    def firstBadVersion(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 1
        top = n
        bottom = 0
        idx = n // 2
        while True:
            if isBadVersion(idx):
                if not isBadVersion(idx - 1):
                    return idx
                top = idx
                idx = idx // 2
            else:
                bottom = idx
                idx = ceil((top + idx) / 2)
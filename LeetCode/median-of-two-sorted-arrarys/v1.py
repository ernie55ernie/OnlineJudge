class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        m = len(nums1)
        n = len(nums2)
        l = m + n
        nums3 = []
        idx1 = 0
        idx2 = 0
        for i in range(l):
            if idx2 >= n or (idx1 < m and nums1[idx1] < nums2[idx2]):
                nums3.append(nums1[idx1])
                idx1 += 1
            else:
                nums3.append(nums2[idx2])
                idx2 += 1
        
        if l % 2 == 0:
            return (nums3[l / 2 - 1] + nums3[l / 2]) / 2.0
        else:
            return nums3[(l - 1) / 2]
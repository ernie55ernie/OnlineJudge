class Solution(object):
    arr = []

    def derangement(self, n):
        arr = self.arr
        
        if n == 0:
            return 1
        
        count = 0
        
        for i in range(1, len(arr)):
            if arr[i] == 0 and i != n:
                arr[i] = n
                count = count + self.derangement(n - 1)
                arr[i] = 0
        
        return count
    
    def findDerangement(self, n):
        """
        :type n: int
        :rtype: int
        """
        self.arr = [0] * (n + 1)
        return self.derangement(n)
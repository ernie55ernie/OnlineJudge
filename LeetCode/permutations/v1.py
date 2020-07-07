# [1,2,3]
# [
#   [1,2,3],
#   [1,3,2],
#   [2,1,3],
#   [2,3,1],
#   [3,1,2],
#   [3,2,1]
# ]
# [5,4,6,2]
class Solution:
    def recursive(self, nums: List[int], length: int):
        if length <= 2:
            for ele in self.nset:
                nums.append(ele)
            self.results.append(nums)
            new = nums.copy()
            new[-1], new[-2] = new[-2], new[-1]
            self.results.append(new)
        else:
            fset = self.nset.copy()
            for i in range(length):
                new = nums.copy()
                ele = fset.pop()
                new.append(ele)
                self.nset.remove(ele)
                self.recursive(new, length - 1)
                self.nset.add(ele)


    def permute(self, nums: List[int]) -> List[List[int]]:
        self.length = len(nums)
        if self.length < 2:
            return [nums]
        self.results = []
        self.nset = set(nums)
        self.recursive([], self.length)
        return self.results
        
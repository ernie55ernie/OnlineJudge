# [2,2,1,1]
# [[1,1,2,2],[1,2,1,2],[1,2,2,1],[2,1,1,2],[2,1,2,1],[2,2,1,1]]
class Solution:
    def recursive(self, nums: List[int], length: int):
        if length <= 2:
            if len(self.nset) == 1:
                for ele in self.nset:
                    nums.append(ele)
                    nums.append(ele)
                self.results.append(nums)
            else:
                for ele in self.nset:
                    nums.append(ele)
                self.results.append(nums)
                new = nums.copy()
                new[-1], new[-2] = new[-2], new[-1]
                self.results.append(new)
        else:
            fset = self.nset.copy()
            for _ in range(len(fset)):
                new = nums.copy()
                ele = fset.pop()
                new.append(ele)
                if self.app[ele] == 1:
                    self.nset.remove(ele)
                self.app[ele] = self.app[ele] - 1
                self.recursive(new, length - 1)
                if self.app[ele] == 0:
                    self.nset.add(ele)
                self.app[ele] = self.app[ele] + 1


    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        self.length = len(nums)
        if self.length < 2:
            return [nums]
        self.results = []
        self.nset = set(nums)
        self.app = {}
        for ele in self.nset:
            self.app[ele] = nums.count(ele)
        print(self.app)
        self.recursive([], self.length)
        return self.results
# [14,6,25,9,30,20,33,34,28,30,16,12,31,9,9,12,34,16,25,32,8,7,30,12,33,20,21,29,24,17,27,34,11,17,30,6,32,21,27,17,16,8,24,12,12,28,11,33,10,32,22,13,34,18,12]
# 27

class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        sols = []
        sol = []
        self.sets = set()
        remain = target
        
        self.bt(candidates, sols, 0, remain, sol)
        
        return sols
    
    def bt(self, candidates: List[int], sols: List[List[int]], idx: int, remain: int, sol: List[int]) -> bool:
        if idx == 0:
            sol = []
        if idx >= len(candidates):
            return
        
        for i in range(2):
            nextRemain = remain - i * candidates[idx]
            nextSol = sol.copy()
            nextSol.extend([candidates[idx]] * i)
            
            if nextRemain == 0:
                nextSol.sort()
                check = str(nextSol)
                if check not in self.sets:
                    sols.append(nextSol)
                    self.sets.add(check)
                    return
            
            self.bt(candidates, sols, idx + 1, nextRemain, nextSol)
        
        return
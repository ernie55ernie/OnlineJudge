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
            
            if nextRemain < 0:
                return
            
            if nextRemain == 0:
                nextSol.sort()
                check = str(nextSol)
                if check not in self.sets:
                    sols.append(nextSol)
                    self.sets.add(check)
                    return
            
            self.bt(candidates, sols, idx + 1, nextRemain, nextSol)
        
        return
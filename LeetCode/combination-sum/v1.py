class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        sols = []
        sol = []
        remain = target
        
        self.bt(candidates, sols, 0, remain, sol)
        
        return sols
    
    def bt(self, candidates: List[int], sols: List[List[int]], idx: int, remain: int, sol: List[int]) -> bool:
        if idx == 0:
            sol = []
        if idx >= len(candidates):
            return
        
        maxTime = remain // candidates[idx]
        for i in range(maxTime + 1):
            nextRemain = remain - i * candidates[idx]
            nextSol = sol.copy()
            nextSol.extend([candidates[idx]] * i)
            
            if nextRemain == 0:
                sols.append(nextSol)
                return
            
            self.bt(candidates, sols, idx + 1, nextRemain, nextSol)
        
        return
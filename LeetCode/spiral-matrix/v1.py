#[[1,2,3,4],[5,6,7,8],[9,10,11,12]]
#[1,2,3,4,8,12,11,10,9,5,6,7]
#[[1,2],[3,4]]
#[1,2,4,3]
class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        # m*n
        n = len(matrix)
        m = len(matrix[0])
        
        idx = 0
        idy = 0
        # direction: 
        # 0 right, 1 down, 2 left, and 3 up
        direct = 0
        # distance to edge
        dist = 0
        result = []
        while True:
            if idx > m - 1 or idx < 0 or idy > n - 1 or idy < 0:
                break
            result.append(matrix[idy][idx])

            if direct == 0:
                if idx == m - 1 - dist:
                    if idy  == n - 1 - dist:
                        break
                    direct = 1
                    idy = idy + 1
                else:
                    idx = idx + 1
            elif direct == 1:
                if idy == n - 1 - dist:
                    if idx  == dist:
                        break
                    direct = 2
                    idx = idx - 1
                else:
                    idy = idy + 1
            elif direct == 2:
                if idx == dist:
                    dist = dist + 1
                    if idy  == dist:
                        break
                    direct = 3
                    idy = idy - 1
                else:
                    idx = idx - 1
            elif direct == 3:
                if idy == dist:
                    if idx  == m - 1 - dist:
                        break
                    direct = 0
                    idx = idx + 1
                else:
                    idy = idy - 1

        return result
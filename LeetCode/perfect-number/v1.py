class Solution:
    def checkPerfectNumber(self, num: int) -> bool:
        if num == 1:
            return False
        remain = num - 1
        for i in range(2, num):
            if i * i > num:
                break
            elif i * i == num:
                remain = remain - i
                break
            else:
                if num % i == 0:
                    remain = remain - i - num / i
                    
        if remain == 0:
            return True
        return False
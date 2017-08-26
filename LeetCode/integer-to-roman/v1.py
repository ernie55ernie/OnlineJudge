class Solution(object):
    def intToRoman(self, num):
        """
        :type num: int
        :rtype: str
        """
        s = ''
        ones = num % 10
        tens = (num / 10) % 10
        hundreds = (num / 100) % 10
        thousands = (num / 1000) % 10
        
        if 0 < ones and ones < 4:
            for i in range(ones):
                s = s + 'I'
        elif ones == 4:
            s = 'IV'
        elif 4 < ones and ones < 9 :
            s = 'V'
            for i in range(ones - 5):
                s = s + 'I'
        elif ones == 9:
            s = 'IX'
        
        tmp_s = ''
        if 0 < tens and tens < 4:
            for i in range(tens):
                tmp_s = tmp_s + 'X'
        elif tens == 4:
            tmp_s = 'XL'
        elif 4 < tens and tens < 9 :
            tmp_s = 'L'
            for i in range(tens - 5):
                tmp_s = tmp_s + 'X'
        elif tens == 9:
            tmp_s = 'XC'
        s = tmp_s + s
        
        tmp_s = ''
        if 0 < hundreds and hundreds < 4:
            for i in range(hundreds):
                tmp_s = tmp_s + 'C'
        elif hundreds == 4:
            tmp_s = 'CD'
        elif 4 < hundreds and hundreds < 9 :
            tmp_s = 'D'
            for i in range(hundreds - 5):
                tmp_s = tmp_s + 'C'
        elif hundreds == 9:
            tmp_s = 'CM'
        s = tmp_s + s
        
        tmp_s = ''
        if 0 < thousands and thousands < 4:
            for i in range(thousands):
                tmp_s = tmp_s + 'M'
        s = tmp_s + s
        
        return s

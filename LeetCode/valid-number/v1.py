class Solution:
	def isNumber(self, s: str) -> bool:
		num_list = [str(i) for i in range(10)]
		if 'e' in s:
			parts = s.split('e')
			if len(parts) > 2: #"95a54e53"
				return False
			if '.' in parts[1]: #" 99e2.5 "
				return False
		else:
			parts = [s]

		if len(parts) > 1:
			if (len(parts[0]) > 1 and parts[0][-1] == ' ') or (len(parts[1]) > 1 and parts[1][0] == ' '): #"96 e5"
				return False

		for part in parts:
			wth_sign = part.strip()
			if len(wth_sign) == 0: #"e"
				return False
			if wth_sign[0] in ['-', '+']:
				wth_sign = wth_sign[1:]
			if '.' in wth_sign:
				if wth_sign.count('.') > 1:
					return False
				wth_sign = wth_sign.replace('.', '')
			for c in wth_sign:
				if c not in num_list:
					return False
			if len(wth_sign) == 0: #" 1e", "."
				return False
		return True
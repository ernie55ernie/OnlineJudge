class Solution(object):
	def findSubstring(self, s, words):
		"""
		:type s: str
		:type words: List[str]
		:rtype: List[int]
		"""
		if len(s) == 0 or len(words) == 0:
			return []

		# word dictionary
		wd = dict()
		# word length
		wl = len(words[0])
		for w in words:
			wd[w] = wd.get(w, 0) + 1

		ans = []

		# index
		for idx in range(len(s) - wl * len(words) + 1):
			# word dictionary for each index
			idxd = dict()
			# index for the number of words
			for widx in range(len(words)):
				# temporary index after matched words
				tidx = idx + widx * wl
				tw = s[tidx : tidx + wl]
				if tw in wd:
					idxd[tw] = idxd.get(tw, 0) + 1
				else:
					break
				if idxd[tw] > wd[tw]:
					break
				if widx == len(words) - 1:
					ans.append(idx)

		return ans

# "barfoothefoobarman"
# ["foo","bar"]
# "barfoofoobarthefoobarman"
# ["bar","foo","the"]
# "wordgoodgoodgoodbestword"
# ["word","good","best","good"]
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        if not head:
        	return head
        ptr = head
        group = [(ptr, ptr.val)]
        while ptr.next:
        	ptr = ptr.next
        	group.append((ptr, ptr.val))
        	if len(group) % k == 0:
        		for i in range(k):
        			group[i][0].val = group[k - i - 1][1]
        		group = []
        return head
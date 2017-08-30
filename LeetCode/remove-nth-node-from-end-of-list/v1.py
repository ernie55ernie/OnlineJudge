# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None
#         
# [1, 2, 3, 4, 5]
# 2

class Solution(object):
    def removeNthFromEnd(self, head, n):
        """
        :type head: ListNode
        :type n: int
        :rtype: ListNode
        """
        if head == None:
        	return None
        l = []
        l.append(head)
        current = head
        while current.next != None:
        	l.append(current.next)
        	current = current.next
        length = len(l)
        if n > length:
        	return None
        elif n == length and length > 1:
        	return l[1]
        elif n == length and length == 1:
        	return None
        prev = l[-n - 1]
        removed = l[-n]
        prev.next = removed.next
        return l[0]
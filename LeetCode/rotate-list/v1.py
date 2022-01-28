# Definition for singly-linked list.
# class ListNode:
#	 def __init__(self, val=0, next=None):
#		 self.val = val
#		 self.next = next
class Solution:
	def rotateRight(self, head: ListNode, k: int) -> ListNode:
		if head == None:
			return None
		newHead = head
		newTail = head
		nextNode = head
		idx = 0
		while nextNode.next:
			idx += 1
			nextNode = nextNode.next
		l = idx + 1
		k = k % l
		idx = 0
		nextNode = head
		# print(k, l, nextNode.val, nextNode.next)
		while True:
			if idx == l - k - 1:
				newTail = nextNode
			if idx == l - k:
				newHead = nextNode
				# print(l, k, newHead.val)
			if not nextNode.next:
				break
			idx += 1
			nextNode = nextNode.next

		if newHead != head:
			nextNode.next = head
			newTail.next = None

		return newHead
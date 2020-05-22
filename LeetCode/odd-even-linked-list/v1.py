# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def oddEvenList(self, head: ListNode) -> ListNode:
        if head is None or head.next is None or head.next.next is None:
            return head
        currentNode = head.next.next
        odd = True
        oddHead = head
        oddIdx = oddHead
        oddTail = None
        evenHead = head.next
        evenIdx = evenHead
        while True:
            if currentNode is None:
                break
            
            if odd:
                oddIdx.next = currentNode
                oddIdx = oddIdx.next
                oddTail = oddIdx
                odd = False
            else:
                evenIdx.next = currentNode
                evenIdx = evenIdx.next
                odd = True
            
            currentNode = currentNode.next
            evenIdx.next = None
        
        oddTail.next = evenHead
        
        return oddHead
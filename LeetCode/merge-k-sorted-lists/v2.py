# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        if len(lists) == 0:
            return None
        head = None
        current = None
        flag = True
        while flag:
            smallest = None
            smallestid = []
            for idx, ln in enumerate(lists):
                if ln is None:
                    continue
                if smallest is None:
                    smallest = ln.val
                    smallestid.append(idx)
                elif ln.val < smallest:
                    smallest = ln.val
                    smallestid = [idx]
                elif ln.val == smallest:
                    smallestid.append(idx)
                
            if head is None:
                head = lists[smallestid[0]]
                current = head
            else:
                current.next = lists[smallestid[0]]
                current = current.next
                    
            lists[smallestid[0]] = lists[smallestid[0]].next
            
            for sidx in smallestid[1:]:
                current.next = lists[sidx]
                lists[sidx] = lists[sidx].next
                current = current.next
            
            flag = False
            for ln in lists:
                if ln is not None:
                    flag = True
        return head
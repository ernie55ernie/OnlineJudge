/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    	ListNode node = new ListNode(
        		(l1 == null ? 0 : l1.val) +
        		(l2 == null ? 0 : l2.val));
    	ListNode current = node;
    	l1 = (l1 == null ? null : l1.next);
    	l2 = (l2 == null ? null : l2.next);
    	int increment = 0;
        while(l1 != null || l2 != null || increment != 0){
        	int val = (l1 == null ? 0 : l1.val) +
        		(l2 == null ? 0 : l2.val);
        	val += increment;
        	if(val >= 10){
        		increment = 1;
        		val -= 10;
        	}else{
        	    increment = 0;
        	}
        	current.next = new ListNode(val);
        	current = current.next;
	    	l1 = (l1 == null ? null : l1.next);
	    	l2 = (l2 == null ? null : l2.next);
        }
        return node;
    }
}
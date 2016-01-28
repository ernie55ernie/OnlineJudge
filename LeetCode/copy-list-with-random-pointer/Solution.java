/**
 * Definition for singly-linked list with a random pointer.
 * class RandomListNode {
 *     int label;
 *     RandomListNode next, random;
 *     RandomListNode(int x) { this.label = x; }
 * };
 */
import java.util.HashMap;
import java.util.Map;

public class Solution {
    public RandomListNode copyRandomList(RandomListNode head) {
    	if(head == null) return null;
        RandomListNode newHead = new RandomListNode(head.label);
        RandomListNode newNext = newHead;
        RandomListNode next = head.next; 

        Map<RandomListNode, RandomListNode> map = 
        	new HashMap<RandomListNode, RandomListNode>();

        while(next != null){
        	newNext.next = new RandomListNode(next.label);
        	newNext = newNext.next;
        	map.put(next, newNext);

        	next = next.next;
        }

        newNext = newHead;
        next = head.random;

        while(next != null && newNext != null){
        	newNext.random = map.get(next);
        	newNext = newNext.random;

        	next = next.random;
        }

        return newHead;
    }
}
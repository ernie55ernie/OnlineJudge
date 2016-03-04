/**
 *	Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 */
public class Solution {
    public int[] twoSum(int[] nums, int target) {
        for(int i = 0; i < nums.length - 1; i++){
        	for(int j = i + 1; j < nums.length; j++){
        		if(target == nums[i] + nums[j])
        			return new int[]{i, j};
        	}
        }
        return null;
    }
}
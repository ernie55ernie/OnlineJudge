//1
//1 1//2
//1 1 1//1 2//2 1
//1 1 1 1//1 1 2//1 2 1//2 1 1//2 2
//1 1 1 1 1//1 1 1 2//1 1 2 1//1 2 1 1//2 1 1 1//1 2 2//2 1 2//2 2 1
//1 1 1 1 1 1//1 1 1 1 2//1 1 1 2 1//1 1 2 1 1//1 2 1 1 1//2 1 1 1 1//1 1 2 2//1 2 1 2//1 2 2 1//2 1 2 1//2 2 1 1//2 1 1 2//2 2 2
class Solution {
public:
	int climbStairs(int n) {
		int before = 1;
		int ways = 1;
		for(int i = 0; i < n - 1;i++){
			int tmp = ways;
			ways = ways + before;
			before = tmp;
		}
		return ways;
	}
};
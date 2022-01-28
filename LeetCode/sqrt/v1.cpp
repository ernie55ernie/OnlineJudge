class Solution {
public:
	int mySqrt(int x) {
		if(x == 0){
			return 0;
		}
		if(x < 4){
			return 1;
		}
		if(x < 9){
			return 2;
		}
		for(long i = 3; i <= x / 2; i++){
			if(i * i == x){
				return i;
			}
			if(i * i > x){
				return i - 1;
			}
		}
		return 0;
	}
};
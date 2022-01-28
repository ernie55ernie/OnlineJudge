class Solution {
public:
	int maxScore(string s) {
		int len = s.length();
		int left[len + 1];
		int right[len + 1];
		int max = 0;
		left[0] = 0;
		right[len] = 0;
		for (int i = 0; i < len - 1; i++){
			if( s[i] == '0'){
				left[i + 1] = left[i] + 1;
			}else{
				left[i + 1] = left[i];
			}
			if( s[len - i - 1] == '1'){
				right[len - i - 1] = right[len - i] + 1;
			}else{
				right[len - i - 1] = right[len - i];
			}
		}
		int maxValue = 0, value = 0;
		for (int i = 1; i < len ; i++){
			cout << left[i] << ' ' << right[i] << '\n';
			value = left[i] + right[i];
			if( value > maxValue){
				maxValue = value;
			}
		}
		return maxValue;
	}
};
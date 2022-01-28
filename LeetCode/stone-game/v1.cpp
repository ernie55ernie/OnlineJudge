//[3,2,10,4]
class Solution {
public:
	bool stoneGame(vector<int>& piles) {
		int size = piles.size();
		vector<int> alex_table;
		vector<int> lee_table;
		int left = 0;
		int right = size - 1;
		for(int i = 0; i < size / 2; i++){
			//alex
			if(piles[left] > piles[right]){
				alex_table.push_back(piles[left]);
				left++;
			}else{
				alex_table.push_back(piles[right]);
				right--;
			}
			//lee
			if(piles[left] > piles[right]){
				lee_table.push_back(piles[left]);
				left++;
			}else{
				lee_table.push_back(piles[right]);
				right--;
			}
		}
		int alex_sum = 0;
		int lee_sum = 0;
		for(int i = 0; i < size / 2; i++){
			alex_sum += alex_table[i];
			lee_sum += lee_table[i];
		}
		// cout << alex_sum << lee_sum;
		if(alex_sum > lee_sum)
			return true;
		return false;
	}
};
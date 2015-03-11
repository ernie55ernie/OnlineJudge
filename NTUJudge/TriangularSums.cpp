#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int main(int argc, char** argv){
	int num = 0 , temp = 0 , sum = 0;
	vector<pair<int , int > >* pa = new vector<pair<int , int > >();

	cin >> num;

	for(int i = 0; i < num ; i++){
		sum = 0;

		cin >> temp;

		for(int j = 1; j <= temp ; j++){
			sum += j * (1 + j + 1) * (j + 1) / 2;
		}

		pa->push_back(make_pair(temp , sum));
	}

	for(unsigned int i = 0; i < pa->size(); i++){
		cout << i + 1 <<" " << pa->at(i).first << " " << pa->at(i).second << "\n";
	}

	return 0;
}
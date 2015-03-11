#include <iostream>
#include <cstdlib>
using namespace std;
/*
N = a + (a + 1) + ... + (a + b)
N = a * (b + 1) + b * (b + 1) / 2
*/
int main(int argc , char** argv){
	
	int num = 1 , time = 0 , temp = 0 , sum = 0;
	
	cin >> num ; 

	for (int i = 0 ; i < num ; i++){
		cin >> time >> temp;
		time = 0;
		for(int j = 1 ; j * (j + 1) / 2 < temp ; j++){
			sum = temp - j * (j + 1) / 2;
			if (sum % (j + 1) == 0)time++;			
		}
		
		cout << i + 1 << " " << time << "\n";
	}

	return 0;
}


#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc , char** argv){
	
	float i = -1 , sum = 0.0;

	while(true){
		cin >> i;
		if(i == 0.00)break;
		int j;
		for(j = 1 ; sum < i ; j++)
			sum += 1.00 / (j + 1);
		sum = 0.0;
		cout << j - 1 << " card(s)\n";
		
	}

	return 0;
}
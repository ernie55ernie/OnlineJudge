#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc , char** argv){
	int num = 0 , mon = 0 ;

	cin >> num;
	for (int i = 1 ; i <= num ; i++){
		int q = 0 , d = 0 , n = 0 , p = 0;
		cin >> mon;
		while (mon >= 25){
			mon -= 25;
			q ++;
		}
		while (mon >= 10){
			mon -= 10;
			d++;
		}
		if (mon >= 5){
			mon -=5;
			n++;
		}
		while (mon >= 1){
			mon -= 1;
			p++;
		}
		cout << i << " " << q << " QUARTER(S), " << d << " DIME(S), "
			 << n << " NICKEL(S), " << p << " PENNY(S)\n"; 
	}

	return 0;
}
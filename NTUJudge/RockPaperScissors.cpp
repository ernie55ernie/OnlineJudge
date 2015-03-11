#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc , char** argv){
	
	int n = 0 , m = 0;

	cin >> n ; 
	while(n-- > 0){
		int p1 = 0 , p2 = 0;
		char c1 , c2;
		cin >> m;
		while(true){
			cin >> c1 >> c2;
			if(c1 == c2);
			else if((c1 == 'S' && c2 == 'P') ||
					(c1 == 'P' && c2 == 'R') ||
					(c1 == 'R' && c2 == 'S'))p1++;
			else p2++;
			if(--m == 0){
				cout << (p1 > p2 ? "Player 1\n" : (p1 == p2 ? "TIE\n" : "Player 2\n" )); 
				break;
			}
		}
	}

	return 0;
}
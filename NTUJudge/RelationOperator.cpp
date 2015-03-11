#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

bool strToOpe(int a , int b , string ope){
	if(ope.compare(">") == 0) return a > b;
	else if(ope.compare(">=") == 0) return a >= b;
	else if(ope.compare("<") == 0) return a < b;
	else if(ope.compare("<=") == 0) return a <= b;
	else if(ope.compare("==") == 0) return a == b;
	else return a != b;
}

int main(int argc , char** argv){
	int n = 0 , a = 0 , b = 0;
	string ope;

	while(true){
		cin >> a >> ope >> b;
		if(ope.compare("E") == 0)break;
		else if(strToOpe(a , b , ope))cout << "Case " << ++n << ": true\n";
		else cout << "Case " << ++n << ": false\n";
	}
	return 0;
}
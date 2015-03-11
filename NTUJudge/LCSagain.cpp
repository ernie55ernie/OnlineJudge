#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int lcs(string str1 , string str2){
	int m = str1.length() , n = str2.length() , o = 0;
	int** c = new int*[m + 1];
	for(int i = 0 ; i < m + 1 ; i++)
		c[i] = new int[n + 1];

	for(int i = 0 ; i < m + 1 ; i++)
		c[i][0] = 0;

	for(int i = 0 ; i < n + 1 ; i++)
		c[0][i] = 0;

	for(int i = 1 ; i < m + 1 ; i++){
		for(int j = 1 ; j < n + 1 ; j++){
			if(str1.at(i - 1) == str2.at(j - 1))
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = c[i - 1][j] > c[i][j - 1] ? c[i - 1][j] : c[i][j - 1] ;
		}
	}

	o = c[m][n];

	for(int i = 0 ; i < m ; i++)
		delete [] c[i];
	delete [] c;
	
	return o;
}

int main(int argc , char** argv){
	int i = 0 , l = 0;
	string str1 , str2;

	cin >> i;

	while(i-- > 0){
		cin >> str1 >> str2;
		cout << lcs(str1 , str2) << "\n";
	}

	return 0;
}
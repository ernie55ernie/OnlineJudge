#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
	string currentLine;
	vector<string> listOfString;
	vector<string> sortString;
	while(cin >> currentLine){
		listOfString.push_back(currentLine);
		sortString.push_back(currentLine);
	}
	string resultString[listOfString.size()];
	sort(sortString.begin(), sortString.end());
	int i, j, currentStrike = 0;
	string prefix;
	for(i = 0; i < sortString.size(); i++){
		string currentString = sortString.at(i);
		string nextString;
		if(i + 1 < sortString.size())nextString = sortString.at(i + 1);
		for(j = 0; j < currentString.size(); j++){
			if((j >= nextString.size() || currentString[j] != nextString[j] ) || j == currentString.size() - 1){
				prefix = currentString.substr(0, j + 1);
				if(i == sortString.size() - 1 || j < currentStrike)prefix = currentString.substr(0, currentStrike + 1);
				currentStrike = j;
				break;
			}
		}
		for(j = 0; j < listOfString.size(); j++){
			if(listOfString.at(j).compare(sortString.at(i)) == 0){
				resultString[j] = prefix;
				break;
			}
		}
	}
	for(i = 0; i < listOfString.size(); i++){
		cout << listOfString.at(i) <<" "<< resultString[i] << endl;
	}
	return EXIT_SUCCESS;
}
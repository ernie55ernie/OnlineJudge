/*
 * ShortestPrefixes.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: user
 */
/*#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {

	queue<string>* q = new queue<string>();
	string str;
	fstream f("input.txt");
	int temp;
	while (getline(cin, str)) {
		if (stringstream(str) >> temp)
			break;
		q->push(str);
	}
	while(!getline(cin,str).eof()){
		q->push(str);
	}
	f.getline(str,100);
	q->push(str);
	cout << q->size();

	return 0;
}*/


/*
 * GoldCoins.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: user
 */
/*#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

int main(int argc,char** argv){

	int i = -1, sum = 0;
	queue<int>* q = new queue<int>();
	while(true){
		cin >> i;
		if( i == 0 )break;
		q->push(i);
	}

	while(!q->empty()){
		int j = i = q->front();
		q->pop();
		sum = 0;
		for(int k = 1 ; i > 0 ; k++){
			sum += k*k;
			i = i - k;
			if(i < 0)sum += i * k;
		}
		cout << j <<' '<<sum<<'\n';
	}

	return 0;
}*/




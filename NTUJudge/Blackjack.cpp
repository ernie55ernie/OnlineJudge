/*
 * Blackjack.cpp
 *
 *  Created on: Aug 4, 2014
 *      Author: user
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
using namespace std;

int convert(char w) {
	switch (w) {
	case 'A':
		return 11;
	case 'T':
		return 10;
	case 'J':
		return 10;
	case 'K':
		return 10;
	case 'Q':
		return 10;
	default:
		return w - '0';
	}
}

int main(int argc, char** argv) {

	char card[3];
	int num[3];
	int deck = 0, exc = 0, alr = 0;
	double win = 0.0;

	vector<double>* pro = new vector<double>();

	while (true) {
		cin >> deck;
		if (deck == 0)
			break;
		cin >> card[0] >> card[1] >> card[2];
		num[0] = convert(card[0]);
		num[1] = convert(card[1]);
		num[2] = convert(card[2]);
		exc = num[2] + num[1] - num[0];
		win = alr = 0;
		if (exc > 0) {
			if (exc > 10)
				win += 4 + exc - 3;
			else
				win += exc - 2;
			win *= 4 * deck;
			//cout << win << endl;
			if (num[2] < exc)
				alr++;
			if (num[1] < exc)
				alr++;
			if (num[0] < exc)
				alr++;
			//cout << alr << endl;
			win -= alr;
			//cout << win << endl;
			pro->push_back(win / (deck * 52 - 3) * 100);
		} else {
			pro->push_back(0);
		}
	}

	for (unsigned int i = 0; i < pro->size(); i++) {
		cout << fixed << setprecision(3) << pro->at(i) << "%\n\n";
	}
}


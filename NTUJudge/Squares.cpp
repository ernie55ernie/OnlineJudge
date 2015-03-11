/*
 * Squares.cpp
 *
 *  Created on: Jul 22, 2014
 *      Author: user
 */
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <utility>
#include <vector>
#include <math.h>

using namespace std;

int main(int args, char** argv) {

	int k, l, num = 0, len1, len2;
	int len[6];
	vector<pair<int, int> >* v = new vector<pair<int, int> >();
	vector<int>* r = new vector<int>();

	while (true) {
		int i;
		cin >> i;
		if (i == 0)
			break;
		for (int j = 0; j < i; j++) {
			cin >> k >> l;
			v->push_back(make_pair(k, l));
		}
		for (unsigned int m = 0; m < v->size() - 3; m++) {
			for (unsigned int n = m + 1; n < v->size() - 2; n++) {
				for (unsigned int o = n + 1; o < v->size() - 1; o++) {
					for (unsigned int p = o + 1; p < v->size(); p++) {
						pair<int, int> a = v->at(m);
						pair<int, int> b = v->at(n);
						pair<int, int> c = v->at(o);
						pair<int, int> d = v->at(p);
						len[0] = pow((a.first - b.first), 2)
								+ pow((a.second - b.second), 2);
						len[1] = pow((a.first - c.first), 2)
								+ pow((a.second - c.second), 2);
						len[2] = pow((a.first - d.first), 2)
								+ pow((a.second - d.second), 2);
						len[3] = pow((b.first - c.first), 2)
								+ pow((b.second - c.second), 2);
						len[4] = pow((b.first - d.first), 2)
								+ pow((b.second - d.second), 2);
						len[5] = pow((c.first - d.first), 2)
								+ pow((c.second - d.second), 2);
						len1 = len[0];
						len2 = len1 != len[1] ?
								len[1] :
								(len1 != len[2] ?
										len[2] : (len1 != len[3] ? len[3] : 0));
						if (len2 == 0)
							continue;
						int temp1 = 0, temp2 = 0;
						for (int q = 0; q < 6; q++) {
							if (len[q] == len1)
								temp1++;
							else if (len[q] == len2)
								temp2++;
						}
						if ((temp1 == 2 && temp2 == 4)
								|| (temp2 == 2 && temp1 == 4))
							num++;
					}
				}
			}
		}
		r->push_back(num);
		num = 0;
		v->clear();
	}
	for (unsigned int i = 0; i < r->size(); i++) {
		cout << r->at(i) << "\n";
	}

	return EXIT_SUCCESS;
}


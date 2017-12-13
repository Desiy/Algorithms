#include "stdafx.h"
#include <vector>
#include <iostream>

using std::vector;

void COUNTING_SORT(vector<int> a, vector<int> b, int k) {

	vector<int> c;
	for (int i = 0; i <= k; ++i)
		c.push_back(0);
	for (int i = 0; i < a.size(); ++i) {
		c[a[i]] = c[a[i]] + 1;
	}
	for (int i = 1; i < c.size(); ++i)
		c[i] += c[i - 1];
	for (int i = a.size() - 1; i >= 0; --i) {
		b[c[a[i]]-1] = a[i];
		c[a[i]] -= 1;
	}
}
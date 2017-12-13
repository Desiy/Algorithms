#include <vector>
#include<iostream>
using std::vector;

int FINDMAX(vector<int> vec) {
	int max = vec[0];
	for (int i = 0; i < vec.size();++i) {
		if (vec[i] > max)
			max = vec[i];
	}
	return max;
}
void RADIX_SORT(vector<int> &vec,int exp) {
	vector<int> output, temp = { 0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < vec.size(); ++i)
		output.push_back(0);
	for (int i = 0; i < vec.size(); ++i) 
		temp[(vec[i] / exp) % 10] += 1 ;
	
	for (int i = 1; i < temp.size(); ++i)
		temp[i] += temp[i - 1];
	for (int i = vec.size() - 1; i >= 0; --i) {
		output[temp[(vec[i] / exp) % 10]-1] = vec[i];
		temp[(vec[i] / exp) % 10] -= 1;
	}
	for (int i = 0; i < vec.size(); ++i)
		vec[i] = output[i];
}
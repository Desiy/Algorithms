#include<vector>
#include<iostream>
using std::vector;
void SWAP(int& a,int& b) {
	int temp = a;
	a = b;
	b = temp;
}
int PARTITION(vector<int>& A,int p,int r) {
	int pivot = A[r];
	int i = p;
	for (int j = p; j < r; ++j) {
		if (A[j] < pivot) {
			SWAP(A[i], A[j]);
			++i;
		}
	}
	SWAP(A[i], A[r]);
	return i;
}
int RANDOM_PARTITION(vector<int>& A,int p,int r){
	int i = p + rand() % (r - p);
	SWAP(A[i], A[r]);
	return PARTITION(A, p, r);
}
int RANDOM_SELECT(vector<int>& A,int p,int r,int i) {
	if (p == r) return A[p];
	int q = RANDOM_PARTITION(A, p, r);
	int k = q - p + 1;
	if (k == i) return A[q];
	else if(i<k)
		return RANDOM_SELECT(A, p, q - 1, i);
	else return RANDOM_SELECT(A, q + 1, r, i-k);
	
}
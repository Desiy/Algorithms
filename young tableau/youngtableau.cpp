#include "stdafx.h"
#include <limits>
#include <iostream>

typedef struct {
	int row;
	int col;
}cell;

void EXCHANGE(int*a,int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void YOUNG_MATRIXIFY(int** a,int m,int n,int i,int j) {
	

	int min_i=i, min_j=j;

		if (i < m-1 && a[i+1][j]<a[i][j] ) {
			min_i = i + 1;
			min_j = j;
		}
		if (j < n-1  && a[i][j + 1] < a[min_i][min_j]) {
			min_i = i;
			min_j = j + 1;
		}
		if (i != min_i || j != min_j) {
			EXCHANGE(&a[min_i][min_j], &a[i][j]);	
			YOUNG_MATRIXIFY(a, m, n, min_i, min_j);
		}
	
}
int EXTRACT_MIN(int** a,int m,int n) {
	int min = a[0][0];
	a[0][0] = a[m - 1][n - 1];
	a[m - 1][n - 1] = INT_MAX;
	YOUNG_MATRIXIFY(a,m,n,0,0);		
	return min;
}
void INCREASE_KEY(int** a,int m,int n) {
	int i = m - 1, j = n - 1;
	int swap_i = m - 1, swap_j = n - 1;
	if (i>0 && a[i - 1][j] > a[i][j]) {
		swap_i = i - 1;
		swap_j = j;
	}
	if (j>0 && a[i][j - 1] > a[swap_i][swap_j]) {
		swap_i = i;
		swap_j = j - 1;
	}
	if (swap_i != m - 1 || swap_j != n - 1) {
		EXCHANGE(&a[i][j], &a[swap_i][swap_j]);
		INCREASE_KEY(a, swap_i+1, swap_j+1);
	}

}
void INSERT(int** a,int m,int n,int key) {

	if (a[m - 1][n - 1] != INT_MAX)
		return;
	a[m - 1][n - 1] = key;

	INCREASE_KEY(a, m , n );
}
cell FIND(int** a,int i,int j,int m,int n,int number) {
	if (number<a[0][0] || number>a[m - 1][n - 1]) {

		std::cout << "can not find the number in the tableau." << std::endl;
		return{INT_MAX,INT_MAX};
	}
	cell location;
	
	if (number == a[i][j]) {
		location = { i,j };
		return location; 

	}
	else if (j>0 && a[i][j] > number) {
		FIND(a, i, j - 1, m, n,number);
	}
	else if(i<m-1 && a[i][j]<number)
		FIND(a, i + 1, j, m, n,number);
	
}
#include <iostream>



int LEFT(int i) {
	
	return 2 * i+1;

}

int RIGHT(int i) {
	
	return 2 * i + 2;

}


void exchange(int*a, int*b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void MAX_HEAPIFY(int*a,int i,int length) {
	int heapsize = length;

	int l = LEFT(i);
	int r = RIGHT(i);
	int largest = i;
	if (l<heapsize&&a[l]>a[i])
		largest = l;
	if (r<heapsize&&a[r]>a[largest])
		largest=r;
	if (largest != i) {
		exchange(&a[i], &a[largest]);
		MAX_HEAPIFY(a, largest, heapsize);
	}
	

}
void BIULD_MAX_HEAP(int* a,int length) {

	for (int i = (length-1) / 2; i >=0; i--)
		MAX_HEAPIFY(a, i,length);
	for (int i = 0; i < 10; i++) {
		std::cout << a[i] << " ";
	}
	std::cout <<"initial"<< std::endl;
}
void HEAPSORT(int* a,int length) {
	int heapsize = length;
	BIULD_MAX_HEAP(a,length);

	for (int i = heapsize-1; i >=1; --i) {
		exchange(&a[0], &a[i]);
		heapsize -= 1;
		MAX_HEAPIFY(a, 0,heapsize);
	}
}


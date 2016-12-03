#include <stdio.h>
#include <iostream>
using namespace std;

#define SIZE 1024
//a, b ,c pointent sur des tableaux
void VectorAdd(int*a, int *b, int *c,int n) {
	for (int i; i < n; ++i) {
		c[i] = a[i] + b[i];
	}
}
int main() {
	int *a, *b, *c;
	a = (int *)malloc(SIZE * sizeof(int));
	b = (int *)malloc(SIZE * sizeof(int));
	c = (int *)malloc(SIZE * sizeof(int));
	for (int i = 0; i < 10; ++i) {
		cout << "c[" << i << "] = " << c[i] << endl;
	}

	free(a);
	free(b);
	free(c);
	
	return 0;
}

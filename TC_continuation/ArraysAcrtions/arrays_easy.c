#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRLEN 1000

void main() {
	srand(time(0));
	
	int n = 0;
	printf("Arr len (1-1000): ");
	while (n > 3000 || n < 1) {
		scanf_s(" %d", &n);
	}
	int arr[ARRLEN];
	for (int i = 0; i < n; i++) {
		arr[i] = -10 + (rand() % 21);
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ARRLEN 1000

void main() {
	srand(time(0));
	
	int n = 0, modnum = 0, power = 0;
	printf("Arr len (1-1000): ");
	while (n > 3000 || n < 1) {
		scanf_s(" %d", &n);
	}
	int arr[ARRLEN];
	for (int i = 0; i < n; i++) {
		arr[i] = -10 + (rand() % 21);
	}

	printf("Mod numb (arr[i)%modnumb == 0): ");
	scanf_s(" %d", &modnum);
	printf("Power (2-5) (arr[i)%modnumb == 0)^power: ");
	while (power < 2 || power > 5) {
		scanf_s(" %d", &power);
	}
	for (int i = n-1; i > -1; i--) {
		if (arr[i] % modnum == 0) {
			arr[i] = pow(arr[i], power);
		}
		printf("%d ", arr[i]);
	}

}
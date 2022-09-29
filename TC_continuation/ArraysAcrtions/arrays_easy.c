#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ARRLEN 1000

void main() {
	srand(time(0));
	
	int n = 0, modnum = 0, power = 0,temp = 0;

	while (n > ARRLEN || n < 1) {
		system("cls");
		printf("Arr len (1-%d): ", ARRLEN);
		scanf_s(" %d", &n);
	}

	int arr[ARRLEN];

	for (int i = 0; i < n; i++) {
		arr[i] = -10 + (rand() % 21);
	}

	printf("Mod numb (arr[i)%modnumb == 0): ");
	scanf_s(" %d", &modnum);

	while (power < 2 || power > 5) {
		system("cls");
		printf("Power (2-5) (arr[i)%modnumb == 0)^power: ");
		scanf_s(" %d", &power);
	}

	for (int i = 0; i < n; i++) {
		if (arr[i] % modnum == 0) {
			arr[i] = pow(arr[i], power);
		}
		
	}

	printf("\n");
	printf("Delete all numb less than: ");
	scanf_s(" %d", &temp);

	for (int i = 0; i < n; i++) {
		if (arr[i] < temp) {
			for (int k = 0; k < n; k++) {
				arr[i + k] = arr[i + k + 1];
			}
			n--;
			i--;
		}
	}

	for (int i = 0; i < n*0.5; i++) {
		temp = arr[n-1 - i];
		arr[n-1-i] = arr[i];
		arr[i] = temp;
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}
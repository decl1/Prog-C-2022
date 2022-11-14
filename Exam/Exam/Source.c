#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

void uravnenie(int a, int b, int c) {
	float d;
	float root1, root2;
	d = sqrt((b * b) - (4 * a * c));
	if (d < 0) {
		printf("Решений нет\n");
	} else if (d == 0){
		root1 = ((-b - d) / 2);
		printf("Один корень: %.2f\n", root1);
	}
	else if (d > 0) {
		root1 = ((-b - d) / 2);
		root2 = ((-b + d) / 2);
		printf("Два корня: %.2f %.2f\n", root1, root2);
	}
}

void main() {
	setlocale(LC_ALL, "rus");
	int menu1, menu2;
	char exit_flag = 0;
	while (exit_flag == 0) {
		menu1 = 0;
		menu2 = 0;
		system("cls");
		printf("Выберите задачу:\n 1.1) Задача 1,\n 1.2) Задача 2.\nВаш выбор: ");
		scanf_s("%d.%d", &menu1, &menu2);
		printf("%d\n", menu2);
		if (menu2 == 1 || menu2 == 2 || menu2 == 3) {
			switch (menu2) {
			case 1:
				system("cls");
				int a, b, c;
				printf("Введите коэфициенты уравнения(a b c): ");
				scanf_s("%d %d %d", &a, &b, &c);
				uravnenie(a, b, c);
				system("pause");
				break;
			case 2:
				system("cls");
				int n;
				printf("Введите количество уравнений: ");
				scanf("%d", &n);
				int** koef = (int**)malloc(sizeof(int*) * n);
				for (int i = 0; i < n; i++) {
					int* koef[i] = (int*)malloc(sizeof(int) * 3);
				}
				
				system("pause");
				break;
			}
		}
	}
}
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <math.h>

void getstr(char* str, int* size) {
	*size = 0;
	printf("Введите строку <= 100 символов: ");
	gets(str);
	while (str[(*size)] != '\0') {
		(* size)++;
	}
}

void printMenu() {
	printf("Выберете действия над строкой:\n");
	printf("1) заменить строку\n");
	printf("2) обрезать строку\n");
	printf("3) развернуть строку\n");
	printf("4) сменить регистр\n");
	printf("- в верхний регистр\n");
	printf("- в нижний регистр\n");
	printf("- в противоположный регистр\n");
	printf("0) выход\n\n");
	printf("Ваш выбор: ");
}

void obrezka(char* str, int* size) {
	int index = (*size) + 1;
	while (index > *size || index < 0) {
		printf("Введите значение: ");
		scanf_s(" %d", &index);
	}
	for (int i = 0; i < index; i++) {
		printf("%c", str[i]);
	}
	*size = index;
	printf("\n");
}

void reversestr(char* str, int size) {
	char temp;
	for (int i = 0; i < size / 2; i++) {
		temp = str[i];
		str[i] = str[size - 1 - i];
		str[size - 1 - i] = temp;
	}
}

void changetitle(char* str, int size) {
	// ToApper
	for (int i = 0; i < size; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			printf("%c", str[i] - 32);
		}
		else if (str[i] >= 'а' && str[i] <= 'я') {
			printf("%c", str[i] - 32);
		}
		else {
			printf("%c", str[i]);
		}
	}
	printf("\n");
	//ToDown
	for (int i = 0; i < size; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			printf("%c", str[i] + 32);
		}
		else if (str[i] >= 'А' && str[i] <= 'Я') {
			printf("%c", str[i] + 32);
		}
		else {
			printf("%c", str[i]);
		}
	}
	printf("\n");
	//ToReverse
	for (int i = 0; i < size; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			printf("%c", str[i] + 32);
		}
		else if (str[i] >= 'a' && str[i] <= 'z') {
			printf("%c", str[i] - 32);
		}
		else if (str[i] >= 'А' && str[i] <= 'Я') {
			printf("%c", str[i] + 32);
		}
		else if (str[i] >= 'а' && str[i] <= 'я') {
			printf("%c", str[i] - 32);
		}
		else {
			printf("%c", str[i]);
		}
	}
	printf("\n");
}

void getresult(char* str, int size) {
	printf("Результат: ");
	for (int i = 0; i < size; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

int gotoquastion() {
	int flag = -1;
	while (flag < 0 || flag > 1) {
		printf("Хотите выполнить что-то еще? 1/0\nВаш выбор: ");
		scanf_s(" %d", &flag);
	}
	return flag;
}

//void main() {
//	setlocale(LC_ALL, "rus");
//	char str[] = "аБвГд aBcDeF";
//	changetitle(str, 12);
//}

int main() {
	setlocale(LC_ALL, "rus");
	char* str = (char*)malloc(sizeof(char) * 100);
	int* size;
	int menu = -1;
	getstr(str, &size);
start:
	printMenu();
	scanf_s(" %d", &menu);

	switch (menu) {
	case 1:
		system("cls");
		scanf_s("%c");
		getstr(str, &size);
		goto start;
		break;
	case 2:
		obrezka(str, &size);
		getresult(str,size);
		if (gotoquastion()==1) {
			system("cls");
			goto start;
		}
		else {
			break;
		}
	case 3:
		reversestr(str, size);
		getresult(str, size);
		if (gotoquastion() == 1) {
			system("cls");
			goto start;
		}
		else {
			break;
		}
	case 4:
		changetitle(str, size);
		if (gotoquastion() == 1) {
			system("cls");
			goto start;
		}
		else {
			break;
		}
	case 0:
		printf("До свидания!");
		return 0;
		break;
	default:
		system("cls");
		goto start;
	}
}

#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <math.h>

void getstr(char* str, int* size) {
	*size = 0;
	printf("������� ������ <= 100 ��������: ");
	gets(str);
	while (str[(*size)] != '\0') {
		(* size)++;
	}
}

void printMenu() {
	printf("�������� �������� ��� �������:\n");
	printf("1) �������� ������\n");
	printf("2) �������� ������\n");
	printf("3) ���������� ������\n");
	printf("4) ������� �������\n");
	printf("- � ������� �������\n");
	printf("- � ������ �������\n");
	printf("- � ��������������� �������\n");
	printf("0) �����\n\n");
	printf("��� �����: ");
}

void obrezka(char* str, int* size) {
	int index = (*size) + 1;
	while (index > *size || index < 0) {
		printf("������� ��������: ");
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
		else if (str[i] >= '�' && str[i] <= '�') {
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
		else if (str[i] >= '�' && str[i] <= '�') {
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
		else if (str[i] >= '�' && str[i] <= '�') {
			printf("%c", str[i] + 32);
		}
		else if (str[i] >= '�' && str[i] <= '�') {
			printf("%c", str[i] - 32);
		}
		else {
			printf("%c", str[i]);
		}
	}
	printf("\n");
}

void getresult(char* str, int size) {
	printf("���������: ");
	for (int i = 0; i < size; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
}

int gotoquastion() {
	int flag = -1;
	while (flag < 0 || flag > 1) {
		printf("������ ��������� ���-�� ���? 1/0\n��� �����: ");
		scanf_s(" %d", &flag);
	}
	return flag;
}

//void main() {
//	setlocale(LC_ALL, "rus");
//	char str[] = "����� aBcDeF";
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
		printf("�� ��������!");
		return 0;
		break;
	default:
		system("cls");
		goto start;
	}
}

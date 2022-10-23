#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

#define MENU_SIZE 3

void choosepos(int* choose_pos, char** menu, COORD* cursorPos, HANDLE hStdOut, int menu_size) {
    int iKey = 67;
    *cursorPos = (COORD){ 0, 0 };
    *choose_pos = 0;
    SetConsoleCursorPosition(hStdOut, *cursorPos);
    while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
        switch (iKey) {
        case KEY_ARROW_UP:
            (*choose_pos)--;
            break;
        case KEY_ARROW_DOWN:
            (*choose_pos)++;
            break;
        }

        system("cls");

        if (*choose_pos < 0) { *choose_pos = menu_size - 1; }
        if (*choose_pos > menu_size - 1) { *choose_pos = 0; }

        for (int i = 0; i < menu_size; i++) {
            *cursorPos = (COORD){ 3, i };
            SetConsoleCursorPosition(hStdOut, *cursorPos);
            printf("%s \n", menu[i]);
        }

        *cursorPos = (COORD){ 0, *choose_pos };
        SetConsoleCursorPosition(hStdOut, *cursorPos);
        printf("<<");
        *cursorPos = (COORD){ strlen(menu[*choose_pos]) + 3 + 1, *choose_pos };
        SetConsoleCursorPosition(hStdOut, *cursorPos);
        printf(">>");

        iKey = _getch();
    }
}

void initarray(int** array, int* size) {
    system("cls");
    printf("Введите кол-во элементов: ");
    scanf_s(" %d", size);
    *array = (int*)malloc(sizeof(int) * (*size));
}
void fillmass(int* array, int size) {
    printf("Введите элементы массива: ");
    for (int i = 0; i < size; i++) {
        scanf_s(" %d", &array[i]);
    }
}
void printarray(int* array, int size) {
    system("cls");
    if (size == -1) {
        printf("Массив не определен\n");
    } else {
        printf("Ваш массив: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}

int main() {
    system("title Application");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    SetConsoleTextAttribute(hStdOut, 10);
    system("cls");

    int choose_pos;
    int exit_flag;
    int incase_flag;
    COORD cursorPos;

    char* menu[MENU_SIZE] = { "Алгоритмы", "Настройки", "Выход" };

    char* algorithms[MENU_SIZE] = { "Поиск", "Сортировки", "Назад"};
    char* search[MENU_SIZE] = { "Наивный поиск","Бинарный поиск", "Назад"};
    char* sorts[2] = { "Пузырьковая сортировка", "Назад" };

    char* settings[MENU_SIZE] = { "Задать массив", "Посмотреть текущий массив", "Назад"};
    
    int* array = NULL;
    int arrsize = -1;


    exit_flag = 0;
    incase_flag = 1;

    while (!exit_flag) {
        system("cls");
        choosepos(&choose_pos, menu, &cursorPos, hStdOut, MENU_SIZE);
        switch (choose_pos) {
        case 0: // Alg
            incase_flag = 1;
            while (incase_flag >= 1) {
                system("cls");
                choosepos(&choose_pos, algorithms, &cursorPos, hStdOut, MENU_SIZE);
                switch (choose_pos) {
                case 0: // Search
                    incase_flag = 2;
                    while (incase_flag >= 2) {
                        choosepos(&choose_pos, search, &cursorPos, hStdOut, MENU_SIZE);
                        switch (choose_pos) {
                        case 0: // Simple search
                            system("cls");
                            system("pause");
                            break;
                        case 1: // Bin search
                            system("cls");
                            system("pause");
                            break;
                        case 2: //Back
                            incase_flag = 1;
                            break;
                        }
                    }
                    break;
                case 1: // Sort
                    incase_flag = 2;
                    while (incase_flag >= 2) {
                        choosepos(&choose_pos, sorts, &cursorPos, hStdOut, 2);
                        switch (choose_pos) {
                        case 0: // Bubble sort
                            system("cls");
                            system("pause");
                            break;
                        case 1: //Back
                            incase_flag = 1;
                            break;
                        }
                    }
                    break;
                case 2: // Back
                    system("cls");
                    incase_flag = 0;
                    break;
                }
            }
            break;
        case 1: // Settings
            incase_flag = 1;
            while (incase_flag == 1) {
                system("cls");
                choosepos(&choose_pos, settings, &cursorPos, hStdOut, MENU_SIZE);
                switch (choose_pos) {
                case 0:
                    initarray(&array, &arrsize);
                    fillmass(array, arrsize);
                    printarray(array, arrsize);
                    system("pause");
                    break;
                case 1:
                    printarray(array, arrsize);
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    incase_flag = 0;
                    break;
                }
            }
            break;
        case 2: // Exit
            exit_flag = 1;
            break;
        }
    }

    system("cls");
    printf("Goodbay!\n");
    free(array);
    system("pause");
    return 0;
}
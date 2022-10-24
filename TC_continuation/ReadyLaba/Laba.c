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
#define SORTMENU_SIZE 2
#define NONE_TITLE ""


void choosepos(int* choose_pos, char** menu, COORD* cursorPos, HANDLE hStdOut, int menu_size, char* text) {
    int iKey = 67;
    int line = (text == NONE_TITLE) ? 0 : 1;
    *cursorPos = (COORD){ 0, line };
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
        printf("%s", ((line == 1) ? text : ""));

        if (*choose_pos < 0) { *choose_pos = menu_size - 1; }
        if (*choose_pos > menu_size - 1) { *choose_pos = 0; }

        for (int i = 0; i < menu_size; i++) {
            *cursorPos = (COORD){ 3, line + i };
            SetConsoleCursorPosition(hStdOut, *cursorPos);
            printf("%s \n", menu[i]);
        }

        *cursorPos = (COORD){ 0, line + *choose_pos };
        SetConsoleCursorPosition(hStdOut, *cursorPos);
        printf("<<");
        *cursorPos = (COORD){ strlen(menu[*choose_pos]) + 3 + 1, line + *choose_pos };
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
        printf("Массив не определен");
    } else {
        printf("Ваш массив: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}
void bubble_sort(int* array, int size) {
    int temp = 0;
    if (size != -1) {
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (array[i] > array[j]) {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
}
void stupidsearch(int* array, int size) {
    system("cls");
    if (size != -1) {
        int number, cnt = 0;
        printf("Введите искомое число: ");
        scanf_s(" %d", &number);
        printf("Индексы найденных элементов: ");
        for (int i = 0; i < size; i++) {
            if (array[i] == number) {
                printf("%d ", i);
                cnt++;
            }
        }
        if (cnt == 0) {
            printf("элементы не найдены");
        }
    }
    else {
        printf("Массив не определен");
    }
    printf("\n");
}
int ifsorted(int* array, int size) {
    int ctrl = 1;
    for (int i = 0; i < size-1; i++) {
        if (array[i] > array[i + 1]) {
            ctrl--;
            break;
        }
    }
    return ctrl;
}
void binsearch(int* array, int size) {
    if (size != -1) {
        int x;
        printf("Введите искомое число X: ");
        scanf_s(" %d", &x);
        system("cls");
        int l = 0, r = size - 1;
        int flag = 0;
        while (l <= r) {
            int c = (l + r) / 2;
            if (array[c] == x) {
                printf("Элемент X = %d найден с индексом %d\n",x,c);
                flag = 1;
                break;
            }
            if (array[c] > x)
                r = c - 1;
            else
                l = c + 1;
        }
        printf("%s", (flag == 1 ? "" : "Элемент не найден\n"));
    }
    else {
        printf("Массив не определен\n");
    }
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
    char* sorts[SORTMENU_SIZE] = { "Пузырьковая сортировка", "Назад" };
    char* settings[MENU_SIZE] = { "Задать массив", "Посмотреть текущий массив", "Назад"};
    
    int* array = NULL;
    int arrsize = -1;


    exit_flag = 0;
    incase_flag = 1;

    while (!exit_flag) {
        system("cls");
        choosepos(&choose_pos, menu, &cursorPos, hStdOut, MENU_SIZE, NONE_TITLE);
        switch (choose_pos) {
        case 0: // Alg
            incase_flag = 1;
            while (incase_flag >= 1) {
                system("cls");
                choosepos(&choose_pos, algorithms, &cursorPos, hStdOut, MENU_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0: // Search
                    incase_flag = 2;
                    while (incase_flag >= 2) {
                        choosepos(&choose_pos, search, &cursorPos, hStdOut, MENU_SIZE, NONE_TITLE);
                        switch (choose_pos) {
                        case 0: // Simple search
                            stupidsearch(array, arrsize);
                            system("pause");
                            break;
                        case 1: // Bin search
                            system("cls");
                            char* yesno[2] = {"Yes", "No"};
                            if (ifsorted(array, arrsize) == 1) { 
                                binsearch(array, arrsize);
                                system("pause");
                            } else {
                                choosepos(&choose_pos, yesno, &cursorPos, hStdOut, 2, "Массив не отсортирован. Отсортировать?");
                                switch (choose_pos) {
                                case 0:
                                    system("cls");
                                    bubble_sort(array, arrsize);
                                    printarray(array, arrsize);
                                    system("pause");
                                    break;
                                case 1:
                                    system("cls");
                                    break;
                                }
                            }
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
                        choosepos(&choose_pos, sorts, &cursorPos, hStdOut, SORTMENU_SIZE, NONE_TITLE);
                        switch (choose_pos) {
                        case 0: // Bubble sort
                            bubble_sort(array, arrsize);
                            printarray(array, arrsize); 
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
                choosepos(&choose_pos, settings, &cursorPos, hStdOut, MENU_SIZE, NONE_TITLE);
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
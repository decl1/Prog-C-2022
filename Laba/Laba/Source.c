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

#define MENU_SIZE 4
#define ALGMENU_SIZE 3
#define SEARCHMENU_SIZE 3
#define SORTMENU_SIZE 2
#define SETSMENU_SIZE 4
#define NONE_TITLE ""

#define LANG_CNT 2
#define RUS 0
#define ENG 1

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
void initarray(int** array, int* size, int lang) {
    system("cls");
    printf( lang  == 0 ? "Введите кол-во элементов: ": "Enter number of elements: ");
    scanf_s(" %d", size);
    *array = (int*)malloc(sizeof(int) * (*size));
}
void fillmass(int* array, int size, int lang) {
    printf(lang == 0 ? "Введите элементы массива: ": "Enter elements of array: ");
    for (int i = 0; i < size; i++) {
        scanf_s(" %d", &array[i]);
    }
}
void printarray(int* array, int size, int lang) {
    system("cls");
    if (size == -1) {
        printf(lang == 0?"Массив не определен":"Array not defined");
    }
    else {
        printf(lang == 0?"Ваш массив: ":"Your array: ");
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
void stupidsearch(int* array, int size, int lang) {
    system("cls");
    if (size != -1) {
        int number, cnt = 0;
        printf(lang == 0 ? "Введите искомое число: ": "Enter desired number: ");
        scanf_s(" %d", &number);
        printf(lang == 0? "Индексы найденных элементов: ": "Indexes of found elements: ");
        for (int i = 0; i < size; i++) {
            if (array[i] == number) {
                printf("%d ", i);
                cnt++;
            }
        }
        if (cnt == 0) {
            printf(lang == 0?"элементы не найдены":"elements not found");
        }
    }
    else {
        printf(lang == 0 ? "Массив не определен": "Array not defined");
    }
    printf("\n");
}
int ifsorted(int* array, int size) {
    int ctrl = 1;
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            ctrl--;
            break;
        }
    }
    return ctrl;
}
void binsearch(int* array, int size, int lang) {
    if (size != -1) {
        int x;
        printf(lang == 0 ? "Введите искомое число X: ": "Enter desired number X: ");
        scanf_s(" %d", &x);
        system("cls");
        int l = 0, r = size - 1;
        int flag = 0;
        while (l <= r) {
            int c = (l + r) / 2;
            if (array[c] == x) {
                printf(lang == 0? "Элемент X = %d найден с индексом %d\n": "Element X = %d found with index %d\n", x, c);
                flag = 1;
                break;
            }
            if (array[c] > x)
                r = c - 1;
            else
                l = c + 1;
        }
        printf("%s", (flag == 1 ? "" : lang == 0 ? "Элемент не найден\n": "Element not found\n"));
    }
    else {
        printf(lang == 0 ? "Массив не определен" : "Array not defined");
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

    char* menu[LANG_CNT][MENU_SIZE] = { { "Режим эксперимента","Алгоритмы", "Settings/Настройки", "Выход"},{"Exp mode","Algs","Settings/Настройки","Exit"}};
    char* algorithms[LANG_CNT][ALGMENU_SIZE] = { { "Поиск", "Сортировки", "Назад" }, { "Search","Sorts","Back" } };
    char* search[LANG_CNT][SEARCHMENU_SIZE] = { { "Наивный поиск","Бинарный поиск", "Назад" }, { "Stupid search","Bin search","Back" } };
    char* sorts[LANG_CNT][SORTMENU_SIZE] = { { "Пузырьковая сортировка", "Назад" }, { "Bubble sort","Back"} };
    char* settings[LANG_CNT][SETSMENU_SIZE] = { {"Language/Язык", "Задать массив", "Посмотреть текущий массив", "Назад"}, {"Language/Язык","Set array","Check our array","Back"}};

    char* lngs[LANG_CNT] = { "Русский","English" };

    int* array = NULL;
    int arrsize = -1;

    int language = RUS;

    exit_flag = 0;
    incase_flag = 1;

    while (!exit_flag) {
        system("cls");
        choosepos(&choose_pos, menu[language], &cursorPos, hStdOut, MENU_SIZE, NONE_TITLE);
        switch (choose_pos) {
        case 0: // Exp
            system("cls");
            system("pause");
            break;
        case 1: // Alg
            incase_flag = 1;
            while (incase_flag >= 1) {
                system("cls");
                choosepos(&choose_pos, algorithms[language], &cursorPos, hStdOut, ALGMENU_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0: // Search
                    incase_flag = 2;
                    while (incase_flag >= 2) {
                        choosepos(&choose_pos, search[language], &cursorPos, hStdOut, SEARCHMENU_SIZE, NONE_TITLE);
                        switch (choose_pos) {
                        case 0: // Simple search
                            stupidsearch(array, arrsize, language);
                            system("pause");
                            break;
                        case 1: // Bin search
                            system("cls");
                            if (arrsize != -1) {
                                char* yesno[LANG_CNT][2] = { {"Да","Нет"}, { "Yes", "No" } };
                                if (ifsorted(array, arrsize) == 1) {
                                    binsearch(array, arrsize, language);
                                    system("pause");
                                }
                                else {
                                    choosepos(&choose_pos, yesno[language], &cursorPos, hStdOut, 2, language == 0 ? "Массив не отсортирован. Отсортировать?" : "Array not sorted. Sort it?");
                                    switch (choose_pos) {
                                    case 0:
                                        system("cls");
                                        bubble_sort(array, arrsize);
                                        printarray(array, arrsize, language);
                                        system("pause");
                                        break;
                                    case 1:
                                        system("cls");
                                        break;
                                    }
                                }
                            }
                            else {
                                printf(language == 0 ? "Массив не определен\n" : "Array not defined\n");
                                system("pause");
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
                        choosepos(&choose_pos, sorts[language], &cursorPos, hStdOut, SORTMENU_SIZE, NONE_TITLE);
                        switch (choose_pos) {
                        case 0: // Bubble sort
                            bubble_sort(array, arrsize);
                            printarray(array, arrsize, language);
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
        case 2: // Settings
            incase_flag = 1;
            while (incase_flag == 1) {
                system("cls");
                choosepos(&choose_pos, settings[language], &cursorPos, hStdOut, SETSMENU_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0:
                    system("cls");
                    choosepos(&choose_pos, lngs, &cursorPos, hStdOut, 2, "Выберете язык / Select a language");
                    language = choose_pos;
                    break;
                case 1:
                    initarray(&array, &arrsize, language);
                    fillmass(array, arrsize, language);
                    printarray(array, arrsize, language);
                    system("pause");
                    break;
                case 2:
                    printarray(array, arrsize, language);
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    incase_flag = 0;
                    break;
                }
            }
            break;
        case 3: // Exit
            exit_flag = 1;
            break;
        }
    }

    system("cls");
    printf(language == 0? "Досвидания!\n" : "Goodbay!\n");
    free(array);
    system("pause");
    return 0;
}
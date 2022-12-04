#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "sys/stat.h"

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
#define SORTMENU_SIZE 5
#define SETSMENU_SIZE 5
#define SETARR_SIZE 4
#define EXPMMENU_SIZE 4

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
    while (iKey != KEY_ENTER) {
        switch (iKey) {
        case KEY_EXIT:
            (*choose_pos) = menu_size - 1;
            return 0;
            break;
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
void randarray(int* array, int size, int lang) {
    printf(lang == 0 ? "Введите минимальный и максимальный элемент (a b): " : "Enter min and max element (a b): ");
    int min, max;
    scanf_s("%d %d", &min, &max); 
    for (int i = 0; i < size; i++) {
        array[i] = min + rand() % (abs(min-max)+1);
    }
}
void viborsort(int* array, int size) {
    int tempmin,tminindex,temp;
    for (int i = 0; i < size; i++) {
        tempmin = array[i];
        tminindex = i;
        for (int k = i; k < size; k++) {
            if (tempmin > array[k]) {
                tempmin = array[k];
                tminindex = k;
            }
        }
        temp = array[i];
        array[i] = tempmin;
        array[tminindex] = temp;
    }
}

int quicksort(int* a, int len) {
    quicksort_r(a, 0, len - 1);
    return 0;
}
int quicksort_r(int* a, int start, int end) {
    if (start >= end) {
        return 0;
    }
    int pivot = a[end];
    int swp;
    //set a pointer to divide array into two parts
    //one part is smaller than pivot and another larger
    int pointer = start;
    int i;
    for (i = start; i < end; i++) {
        if (a[i] < pivot) {
            if (pointer != i) {
                //swap a[i] with a[pointer]
                //a[pointer] behind larger than pivot
                swp = a[i];
                a[i] = a[pointer];
                a[pointer] = swp;
            }
            pointer++;
        }
    }
    //swap back pivot to proper position
    swp = a[end];
    a[end] = a[pointer];
    a[pointer] = swp;
    quicksort_r(a, start, pointer - 1);
    quicksort_r(a, pointer + 1, end);
    return 0;
}
int my_mergesort(int* a, int len) {
    int step = 1;
    int* m1 = (int*)malloc(len * sizeof(int));
    if (!m1) return -1;
    int* m2 = (int*)malloc(len * sizeof(int));
    if (!m2) return -1;
    while (step < len) {
        int i, s1, e1, s2, e2;
        for (i = 0; (i + step - 1) < (len - 1); i += 2 * step) {
            s1 = i;
            e1 = i + step - 1;
            s2 = e1 + 1;
            (i + 2 * step - 1) < (len - 1) ? (e2 = i + 2 * step - 1) : (e2 = len - 1);
            merge_two(a, s1, e1, s2, e2, m1, m2);
        }
        step = step << 1;
    }
    return 0;
}
int merge_two(int* a, int s1, int e1, int s2, int e2, int* m1, int* m2) {
    int len1 = e1 - s1 + 1;
    int len2 = e2 - s2 + 1;
    int p1 = 0;
    int p2 = 0;
    int p = s1;
    memcpy(m1, a + s1, sizeof(int) * len1);
    memcpy(m2, a + s2, sizeof(int) * len2);
    while (p1 < len1 && p2 < len2) {
        if (m1[p1] < m2[p2]) {
            a[p++] = m1[p1++];
        }
        else {
            a[p++] = m2[p2++];
        }
    }
    while (p1 < len1) {
        a[p++] = m1[p1++];
    }
    while (p2 < len2) {
        a[p++] = m2[p2++];
    }
    return 0;
}

int intlen(int a) {
    int i = 1;
    while (a >= 10) {
        i++;
        a /= 10;
    }
    return i;
}

void draw_efficiency_table(void (*sorts[4])(int*, int), int language) {
    int sort_vibor;
    int tests;
    char* titles[LANG_CNT][3] = {
        {"Кол-во элементов","Время","Увеличение"},
        {"Number of elements","Time","Compare"},
    };
    printf("bubble_sort - 1, viborsort - 2, quicksort - 3, mergesort - 4\n");
    printf(language == 0 ? "Выберете сортировку: " : "Enter sort: ");
    scanf_s("%d", &sort_vibor);
    printf(language == 0 ? "Введите количество проверок: " : "Enter number of tests: ");
    scanf_s("%d", &tests);
    int* numberofelement = (int*)malloc(sizeof(int) * tests);
    int* times = (int*)malloc(sizeof(int) * tests);
    int* timeratio = (int*)malloc(sizeof(int) * tests);
    printf(language == 0 ? "Введите размеры данных: " : "Enter numbers of elements: ");
    for (int i = 0; i < tests; i++) {
        scanf_s(" %d", &numberofelement[i]);
    }
    int time;
    for (int i = 0; i < tests; i++) {
        time = clock();
        int* array = (int*)malloc(sizeof(int) * numberofelement[i]);
        for (int k = 0; k < numberofelement[i]; k++) {
            array[k] = -100 + rand() % (abs(-100 - 100) + 1);
        }
        sorts[sort_vibor - 1](array, numberofelement[i]);
        time = clock() - time;
        times[i] = time;
        free(array);
    }
    int mintime = times[0];
    for (int i = 0; i < tests; i++) {
        if (times[i] < mintime)
            mintime = times[i];
    }
    if (mintime == 0)
        mintime = 1;
    for (int i = 0; i < tests; i++) {
        timeratio[i] = times[i] / mintime;
    }

    int column_len[3] = { strlen(titles[language][0]), strlen(titles[language][1]), strlen(titles[language][2]) };

    for (int i = 0; i < tests; i++) {
        if (intlen(numberofelement[i]) > column_len[0])
            column_len[0] = intlen(numberofelement[i]);
        if (intlen(times[i]) > column_len[1])
            column_len[1] = intlen(times[i]);
        if (intlen(timeratio[i]) > column_len[2])
            column_len[2] = intlen(timeratio[i]);
    }

    for (int k = 0; k < 3; k++) {
        printf("|%s", titles[language][k]);
        for (int i = 0; i < column_len[k] - strlen(titles[language][k]); i++) {
            printf(" ");
        }
    }
    printf("|\n");
    for (int l = 0; l < tests; l++) {
        printf("|%d", numberofelement[l]);
        for (int i = 0; i < column_len[0] - intlen(numberofelement[l]); i++) {
            printf(" ");
        }
        printf("|%d", times[l]);
        for (int i = 0; i < column_len[1] - intlen(times[l]); i++) {
            printf(" ");
        }
        printf("|%d", timeratio[l]);
        for (int i = 0; i < column_len[2] - intlen(timeratio[l]); i++) {
            printf(" ");
        }
        printf("|\n");
    }

}

//void draw_table() {
//    int I = 0, J = 0, maxlen;
//    char c;
//    printf("Введите число столбцов таблицы: ");
//    scanf_s("%d", &I);
//    char** title = (char**)malloc(I * sizeof(char*));
//    for (int i = 0; i < I; i++) {
//        title[i] = (char*)malloc(100 * sizeof(char));
//    }
//    for (int i = 0; i < I; i++) {
//        for (int j = 0; j < 100; j++) {
//            title[i][j] = '\0';
//        }
//    }
//    printf("Введите заголовки таблицы:\n");
//    getchar();
//    for (int i = 0; i < I; i++) {
//        int j = 0;
//        while ((c = getchar()) != '\n' && j < 100) {
//            title[i][j] = c;
//            j++;
//        }
//    }
//    printf("\n");
//    printf("Введите количество строк таблицы: ");
//    scanf_s("%d", &J);
//    int** line = (int**)malloc(I * sizeof(int*));
//    for (int i = 0; i < I; i++) {
//        line[i] = (int*)malloc(J * sizeof(int));
//    }
//    for (int i = 0; i < I; i++) {
//        printf("Введите данные для заполнения столбца %s: ", title[i]);
//        for (int j = 0; j < J; j++) {
//            scanf_s(" %d", &line[i][j]);
//        }
//    }
//    printf("\n");
//    int* columnlen = (int*)malloc(I * sizeof(int));
//    for (int i = 0; i < I; i++) {
//        maxlen = 0;
//        if (maxlen < strlen(title[i])) {
//            maxlen = strlen(title[i]);
//        }
//        for (int k = 0; k < I; k++) {
//            if (maxlen < intlen(line[i][k])) {
//                maxlen = intlen(line[i][k]);
//            }
//        }
//        columnlen[i] = maxlen;
//    }
//    printf("Ваша таблица:\n");
//    for (int i = 0; i < I; i++) {
//        printf("|");
//        printf("%s", title[i]);
//        for (int k = 0; k < (columnlen[i] - strlen(title[i])); k++) {
//            printf(" ");
//        }
//    }
//    printf("|");
//    for (int j = 0; j < J; j++) {
//        printf("\n");
//        printf("|");
//        for (int i = 0; i < I; i++) {
//            printf("%d", line[i][j]);
//            for (int k = 0; k < (columnlen[i] - intlen(line[i][j])); k++) {
//                printf(" ");
//            }
//            printf("|");
//        }
//    }
//    printf("\n");
//    // ачищееение
//    for (int i = 0; i < I; i++) {
//        free(title[i]);
//    }
//    free(title);
//    for (int i = 0; i < I; i++) {
//        free(line[i]);
//    }
//    free(line);
//    free(columnlen);
//}

int main() {
    system("title Laba Anikin M");

    srand(time(0));
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
    int sort_flag;
    COORD cursorPos;

    char* menu[LANG_CNT][MENU_SIZE] = {
        { "Режим эксперимента","Алгоритмы", "Settings/Настройки", "Выход"},
        {"Exp mode","Algs","Settings/Настройки","Exit"}
    };
    char* algorithms[LANG_CNT][ALGMENU_SIZE] = {
        { "Поиск", "Сортировки", "Назад" },
        { "Search","Sorts","Back" }
    };
    char* search[LANG_CNT][SEARCHMENU_SIZE] = {
        { "Наивный поиск","Бинарный поиск", "Назад" },
        { "Stupid search","Bin search","Back" }
    };
    char* sorts[LANG_CNT][SORTMENU_SIZE] = {
        { "Пузырьковая сортировка", "Сортировка выбором","Быстрая сортировка Хоара","Сортировка слиянием","Назад"},
        {"Bubble sort","Choose sort","Quick sort", "Merge sort","Back"}
    };
    char* settings[LANG_CNT][SETSMENU_SIZE] = {
        {"Language/Язык", "Задать массив", "Посмотреть текущий массив","Изменить дирректории файлов", "Назад"},
        {"Language/Язык","Set array","Check our array","Change files directory","Back"}
    };
    char* setarrayact[LANG_CNT][SETARR_SIZE] = {
        {"Ручной ввод","Рандомный ввод","Прочитать из файла", "Назад"},
        {"Manual enter","Random array","Read from file", "Back"}
    };
    char* exp_mode_menu[LANG_CNT][EXPMMENU_SIZE] = {
        {"Сравнение сортировок","Эффективонсть","debug","Назад"},
        {"Compare sorts","Efficiency","debug","Back"},
    };


    char* lngs[LANG_CNT] = { "Русский","English" };
    char* filesmenu[LANG_CNT][3] = { 
        {"Файл ввода", "Файл вывода", "Назад"},
        { "input file", "output file", "Back" } 
    };
    int* array = NULL;
    int arrsize = -1;

    char inp_filepath[300] = "C:\\decll\\programs\\Prog-C-2022\\Laba\\files\\input.txt";
    char out_filepath[300] = "C:\\decll\\programs\\Prog-C-2022\\Laba\\files\\output.txt";

    int language = RUS;

    FILE* file = NULL;
    errno_t error;

    exit_flag = 0;
    incase_flag = 1;
    sort_flag = 0;

    void (*p_sorts[4])(int*, int) = { bubble_sort , viborsort , quicksort , my_mergesort };

    while (!exit_flag) {
        system("cls");
        choosepos(&choose_pos, menu[language], &cursorPos, hStdOut, MENU_SIZE, NONE_TITLE);
        switch (choose_pos) {
        case 0: // Exp
            system("cls");
            incase_flag = 1;
            while (incase_flag >= 1) {
                choosepos(&choose_pos, exp_mode_menu[language], &cursorPos, hStdOut, EXPMMENU_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0:
                    system("cls");

                    system("pause");
                    break;
                case 1:
                    system("cls");
                    draw_efficiency_table(p_sorts, language);
                    system("pause");
                    break;
                case 2:
                    system("cls");

                    printf("\n");

                    system("pause");
                    break;
                case EXPMMENU_SIZE - 1:
                    incase_flag = 0;
                    break;
                }
            }
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
                        case (SEARCHMENU_SIZE - 1): //Back
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
                            sort_flag = arrsize == -1 ? 0 : 1;
                            break;
                        case 1: // vibor sort
                            system("cls");
                            viborsort(array, arrsize);
                            printarray(array, arrsize, language);
                            sort_flag = arrsize == -1 ? 0 : 1;
                            break;
                        case 2: // qsort
                            system("cls");
                            quicksort(array, arrsize);
                            printarray(array, arrsize, language);
                            sort_flag = arrsize == -1 ? 0 : 1;
                            break;
                        case 3: // merge sort
                            system("cls");
                            my_mergesort(array, arrsize);
                            printarray(array, arrsize, language);
                            sort_flag = arrsize == -1 ? 0 : 1;
                            break;
                        case (SORTMENU_SIZE - 1): //Back
                            sort_flag = 0;
                            incase_flag = 1;
                            break;
                        }
                        if (sort_flag == 1) {
                        file = NULL;
                        error = fopen_s(&file, out_filepath, "w");

                        if (file == NULL) {
                            printf("Error in input file. Error %d\n", error);
                        }
                        else {
                            if (fprintf(file, "%d\n", arrsize) < 0) {
                                printf("Error\n");
                                return 0;
                            }
                        }
                        for (int i = 0; i < arrsize; i++) {
                            if (fprintf(file, "%d ", array[i]) < 0) {
                                printf("Error\n");
                                return 0;
                            }
                        }
                        printf(language == 0 ? "Массив записан\n" : "Data was write\n");
                        fclose(file);
                        system("pause");
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
            while (incase_flag >= 1) {
                system("cls");
                choosepos(&choose_pos, settings[language], &cursorPos, hStdOut, SETSMENU_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0: // lang
                    system("cls");
                    choosepos(&choose_pos, lngs, &cursorPos, hStdOut, 2, "Выберете язык / Select a language");
                    language = choose_pos;
                    break;
                case 1: // set array
                    incase_flag = 2;
                    while (incase_flag >= 2) {

                        system("cls");
                        choosepos(&choose_pos, setarrayact[language], &cursorPos, hStdOut, SETARR_SIZE, language == 0 ? "Как вы собираетесь задать массив?" : "How you want enter the array?");   

                        switch (choose_pos) {
                        case 0: // manual enter
                            system("cls");
                            free(array);
                            initarray(&array, &arrsize, language);
                            fillmass(array, arrsize, language);
                            printarray(array, arrsize, language);
                            incase_flag = 1;
                            system("pause");
                            break;
                        case 1: // rand enter
                            system("cls");
                            free(array);
                            initarray(&array, &arrsize, language);
                            randarray(array, arrsize, language);
                            printarray(array, arrsize, language);
                            incase_flag = 1;
                            system("pause");
                            break;
                        case 2: // read from file
                            system("cls");
                            
                            free(array);
                            file = NULL;
                            error = fopen_s(&file, inp_filepath, "r");

                            if (file == NULL) {
                                    printf("Error in input file. Error %d\n", error);
                            }
                            else {
                                if (fscanf_s(file, "%d", &arrsize) != 1) {
                                    printf("Error\n");
                                    return 0;
                                }
                            }
                            array = (int*)malloc(sizeof(int) * arrsize);

                            for (int i = 0; i < arrsize; i++) {
                                if (fscanf_s(file, "%d", &array[i]) != 1) {
                                    printf("Error\n");
                                    return 0;
                                }
                            }

                            printf(language == 0 ? "Массив получен\n" : "Data was read\n");
                            fclose(file);
                            printarray(array, arrsize, language);
                            system("pause");
                            incase_flag = 1;
                            break;
                        case 3: // back
                            system("cls");
                            incase_flag = 1;
                            break;
                        }
                    }
                    break;
                case 2: // check array
                    printarray(array, arrsize, language);
                    system("pause");
                    break;
                case 3: // dir change
                    system("cls");

                    choosepos(&choose_pos, filesmenu[language],
                        &cursorPos, hStdOut, 3, language == 0 ? "Файл:" : "File:");
                    switch(choose_pos) { 
                    case 0:
                        system("cls");
                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = TRUE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);

                        printf(language == 0 ? "Введите расположение файла или \"default\": " : "Input filepath or \"default\": ");
                        scanf_s(" ");
                        gets(inp_filepath);

                        if (!strcmp(inp_filepath, "default"))
                            strcpy_s(inp_filepath, sizeof(inp_filepath),"C:\\decll\\programs\\Prog-C-2022\\Laba\\files\\input.txt");
                        system("cls");

                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        break;
                    case 1:
                        system("cls");
                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = TRUE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);

                        printf(language == 0 ? "Введите расположение файла или \"default\": " : "Input filepath or \"default\": ");
                        scanf_s(" ");
                        gets(out_filepath);

                        if (!strcmp(out_filepath, "default"))
                            strcpy_s(out_filepath, sizeof(out_filepath), "C:\\decll\\programs\\Prog-C-2022\\Laba\\files\\output.txt");

                        system("cls");

                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        break;
                    case 2:
                        break;
                    }
                    printf("input file: %s\noutput file: %s\n", inp_filepath, out_filepath);
                    system("pause");
                    break;
                case (SETSMENU_SIZE - 1): // back
                    system("cls");
                    incase_flag = 0;
                    break;
                }
            }
            break;
        case (MENU_SIZE - 1): // Exit
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

#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <conio.h>

#define MENU_SIZE 3

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80


void fillmass(int* mass, int size) {
    printf("Введите элементы массива: ");
    for (int i = 0; i < size; i++) {
        scanf_s(" %d", &mass[i]);
    }
}
void checkmass(int* mass, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", mass[i]);
    }
}
void bubblesort(int* mass, int size) {
    int temp;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (mass[i] > mass[j]) {
                temp = mass[i];
                mass[i] = mass[j];
                mass[j] = temp;
            }
        }
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

    SetConsoleTextAttribute(hStdOut, 5);

    system("cls");

   
    int choose_pos;
    int iKey;
    int exit_flag;
    int massive_flag;
    COORD cursorPos;
    char* menu[MENU_SIZE] = { "Алгоритмы", "Настройки", "Выход" };
    char* settings[MENU_SIZE] = { "Задать массив", "Посмотреть текущий массив", "Назад"};
    char* algorithms[MENU_SIZE] = { "Сортировки", "Поиск", "Назад"};
    
    int n = 1;
    int* mass = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        mass[i] = 0;
    }

    exit_flag = 0;
    choose_pos = 0;
    massive_flag = 0;
    iKey = 0;
    cursorPos = (COORD){0,0};

    while (!exit_flag) {
        
        system("cls");
        iKey = 67;
        cursorPos = (COORD){ 0, 0 };
        SetConsoleCursorPosition(hStdOut, cursorPos);

        while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
            switch (iKey) {
            case KEY_ARROW_UP:
                choose_pos--;
                break;
            case KEY_ARROW_DOWN:
                choose_pos++;
                break;
            }

            system("cls");

         
            if (choose_pos < 0) { choose_pos = MENU_SIZE - 1; }
            if (choose_pos > MENU_SIZE - 1) { choose_pos = 0; }

            for (int i = 0; i < MENU_SIZE; i++) {
                cursorPos = (COORD){ 3, i };
                SetConsoleCursorPosition(hStdOut, cursorPos);
                printf("%s \n", menu[i]);
            }


            cursorPos = (COORD){ 0, choose_pos };
            SetConsoleCursorPosition(hStdOut, cursorPos);
            printf("<<", iKey);
            cursorPos = (COORD){ strlen(menu[choose_pos]) + 3 + 1, choose_pos };
            SetConsoleCursorPosition(hStdOut, cursorPos);
            printf(">>");

            iKey = _getch();
        }
        switch (choose_pos) {
        case 0:
            // Алгоритмы
            system("cls");
            iKey = 67;
            while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
                switch (iKey) {
                case KEY_ARROW_UP:
                    choose_pos--;
                    break;
                case KEY_ARROW_DOWN:
                    choose_pos++;
                    break;
                }
                system("cls");
                if (choose_pos < 0) { choose_pos = MENU_SIZE - 1; }
                if (choose_pos > MENU_SIZE - 1) { choose_pos = 0; }
                for (int i = 0; i < MENU_SIZE; i++) {
                    cursorPos = (COORD){ 3, i };
                    SetConsoleCursorPosition(hStdOut, cursorPos);
                    printf("%s \n", algorithms[i]);
                }

                cursorPos = (COORD){ 0, choose_pos };
                SetConsoleCursorPosition(hStdOut, cursorPos);
                printf("<<", iKey);
                cursorPos = (COORD){ strlen(algorithms[choose_pos]) + 3 + 1, choose_pos };
                SetConsoleCursorPosition(hStdOut, cursorPos);
                printf(">>");

                iKey = _getch();
            }
            switch (choose_pos) {
            case 0:
                // Сортировочка
                system("cls");
                bubblesort(mass, n);
                checkmass(mass, n);
                printf("\n");
                break;
            case 1:
                // Поиск
                system("cls");
                printf("Пииск");
                printf("\n");
                break;
            }
            system("pause");
            break;
        case 1:
            // Настройки
            system("cls");
            iKey = 67;
            while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
                switch (iKey) {
                case KEY_ARROW_UP:
                    choose_pos--;
                    break;
                case KEY_ARROW_DOWN:
                    choose_pos++;
                    break;
                }
                system("cls");
                if (choose_pos < 0) { choose_pos = SETTINGS_SIZE - 1; }
                if (choose_pos > SETTINGS_SIZE - 1) { choose_pos = 0; }
                for (int i = 0; i < SETTINGS_SIZE; i++) {
                    cursorPos = (COORD){ 3, i };
                    SetConsoleCursorPosition(hStdOut, cursorPos);
                    printf("%s \n", settings[i]);
                }


                cursorPos = (COORD){ 0, choose_pos };
                SetConsoleCursorPosition(hStdOut, cursorPos);
                printf("<<", iKey);
                cursorPos = (COORD){ strlen(settings[choose_pos]) + 3 + 1, choose_pos };
                SetConsoleCursorPosition(hStdOut, cursorPos);
                printf(">>");

                iKey = _getch();
            }
            switch (choose_pos) {
            case 0:
                // Задать массив
                system("cls");
                free(mass);
                printf("Введите кол-во элементов: ");
                scanf_s(" %d", &n);
                mass = (int*)malloc(n * sizeof(int));
                fillmass(mass, n);
                massive_flag = 1;
                checkmass(mass, n);
                printf("\n");
                break;
            case 1:
                // Посмотреть массив
                system("cls");
                checkmass(mass, n);
                printf("\n");
                break;
            }
            system("pause");
            break;
        case 2:
            // Выход
            exit_flag = 1;
            break;
        }
    }

    system("cls");
    printf("Goodbay!\n");

    system("pause");
    return 0;
}
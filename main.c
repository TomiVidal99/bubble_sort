/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Importo librerias ~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#include <time.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defino colores ~~~~~*/
#define Black          0
#define Blue           1
#define Green          2
#define Cyan           3
#define Red            4
#define Magenta        5
#define Brown          6
#define LightGray     7
#define DarkGray      8
#define LightBlue     9
#define LightGreen    10
#define LightCyan     11
#define LightRed      12
#define LightMagenta  13
#define Yellow         14
#define White          15

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CAMBIAR DEPENDIENDO DEL SISTEMA OPERATIVO ~~~~~*/
/*WINDOWS*/
#define clc() system("cls")
/*LINUx*/
/*#define clc() system("clear")*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Definicion de constantes ~~~~~*/
#define MAX_LENGTH_DATA 9

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defino funciones ~~~~~*/
void set_color(int);
void load_data(int [], int);
void sort_data(int [], int);
void delay(int);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Loop principal ~~~~~*/
int main() {

    /*int data[MAX_LENGTH_DATA], index;*/
    int data[MAX_LENGTH_DATA] = { 1, 4, 5, 8, 23, 11, 15, 2, 3};

    /*set_color(RED);*/
    /*load_data(data, MAX_LENGTH_DATA);*/
    sort_data(data, MAX_LENGTH_DATA);

    fflush(stdin);
    getchar();
    
    return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Creo las funciones ~~~~~*/
void set_color(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

void load_data(int data[], int length) {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Funcion que carga los datos en un arreglo de tamaño length ~~~~~*/
    int index;
    for (index = 0; index < length; index++) {
        clc();
        printf("Ingrese el dato del arreglo [%d]: ", index);
        scanf("%d", &data[index]);
    }
    return;
}

void sort_data(int data[], int length) {
/* Funcion que organiza de mayor a menor los datos con el metodo de burbuja ~~~~~*/
    int index, j;
    for (j = 1; j < length; j++) {
        
        for (index = 1; index < length; index++) {
            int current_val = data[index];
            int prev_val = data[index-1];
            if (index == (j+1)) {
                set_color(Green);
            } else if (index == j) {
                set_color(Blue);
            } else {
                set_color(Red);
            }
            printf("%d \t", prev_val);
            set_color(Red);
            printf("|");
            if (prev_val > current_val) {
                data[index] = prev_val;
                data[index-1] = current_val;
            } else {
                data[index] = current_val;
                data[index-1] = prev_val;
            }
        }

        delay(5000);
        clc();

    }
    return;
}

void delay(int milliseconds) {
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

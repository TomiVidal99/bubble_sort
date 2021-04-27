/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SOLO COMPILABLE PARA WINDOWS ~~~~~*/
/*NO SE PUEDE COMPILAR PARA LINUX PORQUE SE IMPORTAN LIBRERIAS SOLO DISPONIBLES EN WINDOWS*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Importo librerias ~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <dos.h>
#include <dir.h>
#include <time.h>
#include <stdbool.h>

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Definicion de constantes ~~~~~*/
#define MAX_LENGTH_DATA 30
#define DEFAULT_ANIMATION_DELAY 200
#define MAX_ANIMATION_DELAY 3000
#define MAX_RANGE 100
#define clc() system("cls")

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defino funciones ~~~~~*/
void set_color(int);
void load_data(int [], int);
void sort_data(int [], int, int);
void delay(int);
void get_random_data(int [], int, int);
void get_data_length(int *);
void should_get_user_data(int [], int, int);
void define_max_range(int *, int, int);
void define_animation_delay(int *, int, int);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Loop principal ~~~~~*/
int main() {

    int data[MAX_LENGTH_DATA], max_range = 100, max_length = MAX_LENGTH_DATA, animation_delay = DEFAULT_ANIMATION_DELAY;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Preguntar cual es el tamaño del arreglo ~~~~~*/
    get_data_length(&max_length);


    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Obetener el tiempo entre animacion ~~~~~*/
    define_animation_delay(&animation_delay, 200, MAX_ANIMATION_DELAY);


    /*~~~~~~~~~~~~~ PREGUNTO SI SE QUIERE INGRESAR NUMERO O TOMAR ALEATORIOS ~~~~~*/
    should_get_user_data(data, max_length, max_range);

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CARGO LA ANIMACION Y ORDENO EL ARREGLO ~~~~~*/
    clc();
    sort_data(data, max_length, animation_delay);

    printf("\n\nAnimacion finalizada! ");

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

void sort_data(int data[], int length, int milliseconds_between_animations) {
/* Funcion que organiza de mayor a menor los datos con el metodo de burbuja ~~~~~*/
    int index, limit, current_val, next_val, current_index, next_index, animation_iterator;
    bool should_swap;

    /* Itero todos los valores exepto el ultimo, para marcas el limit del ordenamiento ~~~~~*/
    for (limit = 0; limit < length; limit++) {

        /* Recorro los valores hasta el limit y voy llevando el mayor valor al final del arreglo ~~~~~*/
        for (index = 0; index < (length-1-limit); index++) {

            should_swap = false;

            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defino el valor actual y el siguiente ~~~~~*/
            current_index = index;
            next_index = index+1;
            current_val = data[current_index];
            next_val = data[next_index];

            /*~~~~~~ Cambio los valores si es mayor el valor actual que el siguiente ~~~~~*/
            if (current_val > next_val) {
                data[current_index] = next_val;
                data[next_index] = current_val;
                should_swap = true;
            } 

            /*~~~~~~~~~~~~~~~~~~~~ Muestro todos los valores para hacer la animacion ~~~~~*/
            for (animation_iterator = 0; animation_iterator < length; animation_iterator++) {
                if (limit != (length-2)) {

                    if (animation_iterator == next_index) {
                        if (should_swap) {
                            set_color(Yellow);
                            printf("\t\t  %d ---> CAMBIAR\n", data[animation_iterator]);
                        } else {
                            set_color(Blue);
                            printf("\t  %d\n", data[animation_iterator]);
                        }
                    } else if (animation_iterator == current_index) {
                        if (should_swap) {
                            set_color(Yellow);
                            printf("\t\t  %d ---> CAMBIAR\n", data[animation_iterator]);
                        } else {
                            set_color(Blue);
                            printf("\t  %d\n", data[animation_iterator]);
                        }
                    } else if (animation_iterator == limit) {
                        set_color(Green);
                        printf("\t %d <--- \n", data[animation_iterator]);
                    } else {
                        set_color(Red);
                        printf("\t %d \n", data[animation_iterator]);
                    }
                } else {
                    set_color(White);
                    printf("\t %d \n", data[animation_iterator]);
                }
            }

            delay(milliseconds_between_animations);
            if (limit != (length-2) || animation_iterator < (length-1)) {
                clc();
            }

        }

    }
    return;
}

void delay(int milliseconds) {
    /*~ Funcion que espera x milisegundos que se especifican en el argumento, se requiere la inclusion de la libreria <time.h> ~~~~~*/

    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();

}

void get_random_data(int data[], int length, int range) {
/* Funcion que genera 'length' numeros aleatorios desde 0 a range, y los almacena en data ~~~~~*/
    int random_number, index;
    for (index = 0; index < length; index++) {
        random_number = rand() % range;
        data[index] = random_number;
    }
}

void should_get_user_data(int data[], int length, int max_range) {
/* Esta funcion es para preguntar al usuario si quiere ingresar sus propios numeros o ingresar aleatorios ~~~~~*/
    char answer;
    do {
        clc();
        printf("Ingresar numeros? se usaran aleatorios si no (s/n) ");
        fflush(stdin);
        scanf(" %c", &answer);
        if (answer == 's' || answer == 'S') {
            load_data(data, length);
        } else if (answer == 'n' || answer == 'N') {
            /*~~~~~~~~~~~~~~~~~~~~ Obtener el maximo rango de los numeros aleatorios ~~~~~*/
            define_max_range(&max_range, 10, MAX_LENGTH_DATA);
            get_random_data(data, length, max_range);
        }
    } while (answer != 'n' && answer != 'N' && answer != 'S' && answer != 's');
}

void get_data_length(int *length) {
/* Funcion que pregunta al usuario el tamaño del arreglo 'data' y asigna el valor a length ~~~~~*/
    do {
        clc(); 
        printf("¿Cuantos numeros se quieren ordenar? (1-%d) ", MAX_LENGTH_DATA);
        fflush(stdin);
        scanf("%d", length);
    } while (*length < 1 && *length > MAX_LENGTH_DATA);

}

void define_animation_delay(int *delay, int min_val, int max_val) {
/*~~~~~~~~~~~~~~~~~~~~~~~~ Funcion para obtener el maximo valor de delay ~~~~~*/
    do {
        clc();
        printf("¿Cual es el tiempo en milisegundos entre animaciones? (%d-%d) ", min_val, max_val);
        fflush(stdin);
        scanf("%d", delay);
    } while ( *delay < min_val || *delay > max_val);
}

void define_max_range(int *range, int min_val, int max_val) {
/*~~~~~~~~~~~~~~~~~~~~~~~~ Funcion para obtener el maximo valor de delay ~~~~~*/
    char answer;
    do {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Preguntar si se quiere modificar el valor ~~~~~*/
        clc();
        printf("¿Modificar el maximo valor de los numeros aleatorios? (s/n) ");
        fflush(stdin);
        scanf(" %c", &answer);

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Cambiar el valor si el usuario quiere ~~~~~*/
        if (answer == 's' || answer == 'S') {
            do {
                clc();
                printf("¿Cual es el rango de los numeros aleatorios? (%d-%d) ", min_val, max_val);
                fflush(stdin);
                scanf("%d", range);
            } while ( *range < min_val || *range > max_val);
        }
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  ~~~~~*/

        } while (answer != 'n' && answer != 'N' && answer != 'S' && answer != 's');
}

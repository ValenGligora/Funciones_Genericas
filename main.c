#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"

typedef struct
{
    int d;
    int m;
    int a;
}
Fecha;
//*(((Fecha*)miVec.vec)+1) Esto cuando queremos debuggear y ver los elementos en el watch
int cmpFechas(const void* a, const void* b);
void imprimirFecha(const void* a);
// memcpy(dirDest, dirOrig, cantBytes); 
//copia en la dirc de destino lo que se encuentra en la dir de origen

// memmove(dirDest, dirOrig, cantBytes);
// desplazamiento en bloque a la direccion destino

int main()
{
    // Set the code page to support Spanish characters
    system("chcp 65001 > nul");

    Vector miVec;

    vectorCrear(&miVec, sizeof(Fecha));

    srand(time(NULL));

    Fecha f;


    for(int i = 1; i <= 100000; i++)
    {
        f.d = 1 + rand() %28;
        f.m = 1 + rand() %12;
        f.a = 1900 + rand() %130;

        vectorInsertarAlFinal(&miVec, &f);
    }
//    puts("Antes:");
//    vectorMostrar(&miVec, imprimirFecha);

    time_t tIni = time(NULL);
    vectorOrdenar(&miVec, QSORT, cmpFechas);
    time_t tFin = time(NULL);

    time_t tiempoEjecucion = tFin - tIni;

    printf("Tiempo de ejecución: %Iu\n", tiempoEjecucion);

//    puts("\nDespues:");

//    vectorMostrar(&miVec, imprimirFecha);

    vectorDestruir(&miVec);

    return 0;
}

int cmpFechas(const void* a, const void* b){
    const Fecha* f1 = a;
    const Fecha* f2 = b;
    return (f1->a * 10000 + f1->m * 100+ f1->d) - (f2->a * 10000 + f2->m * 100+ f2->d);

}

void imprimirFecha(const void* a){

    const Fecha* f = a;
    printf("%02d/%02d/%04d\n", f->d, f->m, f->a);
}


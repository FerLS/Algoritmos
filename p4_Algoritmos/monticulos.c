#include <stdio.h>
#include <stdlib.h>
#include "monticulos.h"

void crear_monticulo(const int v[], int n, monticulo *M) {
    int i;
    for (i = 0; i < n; ++i) {
        M->vector[i] = v[i];
    }

    M->ultimo = n-1;

    for (i = n; i >= 0; --i) {
        hundir(M, i);
    }

}

int eliminar_mayor(monticulo *M) {
    int x;
    if(M->ultimo ==-1){
        printf("Montículo lleno.\n");
    }
    x = M->vector[0];
    M->vector[0] = M->vector[M->ultimo];
    M->ultimo--;
    if(M->ultimo > 0){
        hundir(M,0);
    }
    return x;
}

void intercambiar(int *a, int *b) {

    int aux;
    aux=*a;
    *a=*b;
    *b=aux;

}
void hundir(monticulo *M,int i){

    int  j,izq,der;
    do {
        der = 2 * i+1;
        izq = 2 * i+2;
        j = i;

        if((der <= M->ultimo) && (M->vector[der] > M->vector[i])){
            i = der;
        }
        if((izq <= M->ultimo) && (M->vector[izq] > M->vector[i])){
            i= izq;
        }
        intercambiar(&M->vector[j],&M->vector[i]);

    } while (j != i);

}

void ord_monticulo(int v[], int n){
    int i;
    monticulo M;
    crear_monticulo(v,n,&M);

    for (i = n-1; i >= 0 ; --i) {
        M.vector[i]= eliminar_mayor(&M);
        v[i]=M.vector[i];
    }
}

void visualizar(monticulo M){

    printf("\n");
    for (int i = 0; i <= M.ultimo; ++i) {
        printf("%d ",M.vector[i]);
    }
    printf("\n");
}

void flotar(monticulo *M, int i) {

    while (i > 1 && M->vector[i / 2] < M->vector[i]) {

        intercambiar(&M->vector[i/2], &M->vector[i]);
        i = i / 2;
    }
}


#ifndef ARBOLES_ARBOLES_H
#define ARBOLES_ARBOLES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int data;

struct nodo {
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

struct nodo *crearnodo(int e);


arbol creararbol();
arbol hijoDerecho(arbol T);
arbol hijoizquierdo(arbol T);

posicion buscar(data e, arbol T);
arbol eliminararbol(arbol T);
arbol insertar(data e, arbol a);

int esarbolvacio(arbol T);


int elemento(posicion p);
int numerorepeticiones(posicion p );
int altura(arbol T);
void visualizar(arbol T);

void test();
#endif //ARBOLES_ARBOLES_H

#ifndef ALGORITMOS4_MONTICULOS_H
#define ALGORITMOS4_MONTICULOS_H

#define TAM 512000
typedef struct {
    int vector[TAM];
    int ultimo;
} monticulo;

void crear_monticulo(const int v[], int i,monticulo *M);
void ord_monticulo(int v[], int n);
int eliminar_mayor(monticulo *M);
void hundir(monticulo *M,int i);
void intercambiar(int *a, int *b);
void flotar(monticulo *M, int i);
void visualizar(monticulo M);
#endif //ALGORITMOS4_MONTICULOS_H


#include "arboles.h"

struct nodo *crearnodo(int e) {

    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL) {
        printf("Memoria agotada.\n");
        exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

arbol creararbol() {

    return NULL;
}

int esarbolvacio(arbol T) {

    return T == NULL ? 1 : 0;
}

arbol eliminararbol(arbol T) {

    if (T != NULL) {
        T->izq = eliminararbol((hijoizquierdo(T)));
        T->der = eliminararbol(hijoDerecho(T));
        free(T);
    }
    return NULL;
}

arbol hijoizquierdo(arbol T) {

    return T->izq;

}

arbol hijoDerecho(arbol T) {

    return T->der;
}

arbol insertar(int i, arbol T) {
    if (T == NULL) {
        return crearnodo(i);

    } else if (i < T->elem) {
        T->izq = insertar(i, T->izq);

    } else if (i > T->elem) {
        T->der = insertar(i, T->der);

    } else {
        T->num_repeticiones++;

    }


    return T;
}


posicion buscar(int i, arbol T) {

    if (T == NULL) {
        return NULL;
    } else if (i < (T->elem)) {

        return buscar(i, T->izq);

    } else if (i > (T->elem)) {

        return buscar(i, T->der);
    } else {

        return T;
    }

}

int elemento(posicion p) {

    return p->elem;
}

int numerorepeticiones(posicion p) {

    return p->num_repeticiones;

}

int altura(arbol T) {

    int der;
    int izq;

    if (esarbolvacio(T)) {

        return -1;
    }

    if (T->der != NULL && T->izq != NULL) {

        der = altura(T->der);
        izq = altura(T->izq);
        return 1 + (izq > der ? izq : der);

    }

    if (T->der != NULL) {

        return 1 + altura(T->der);


    }
    if (T->izq != NULL) {

        return 1 + altura(T->izq);

    }

    return 0;
}

void visualizar(arbol T) {

    if (esarbolvacio(T)) {
        printf("()");
        return;
    }

    printf("(");

    if (T->izq != NULL) {


        visualizar(T->izq);
    }

    printf("%d", T->elem);


    if (T->der != NULL) {

        visualizar(T->der);
    }
    printf(")");
}

void test() {
    int i;
    posicion p;
    arbol a = creararbol();

    printf("Arbol vacio: ");
    visualizar(a);
    printf(".\n");
    printf("Altura del arbol: %i\n", altura(a));
    printf("Inserto un 3\n");
    a = insertar(3, a);
    printf("Inserto un 1\n");
    a = insertar(1, a);
    printf("Inserto un 2\n");
    a = insertar(2, a);
    printf("Inserto un 5\n");
    a = insertar(5, a);
    printf("Inserto un 4\n");
    a = insertar(4, a);
    printf("Inserto un 5\n");
    a = insertar(5, a);
    printf("Arbol: ");
    visualizar(a);
    printf(".\n");
    printf("Altura del arbol: %i\n", altura(a));
    for (i = 1; i <= 6; i++) {
        p = buscar(i, a);
        if (p != NULL) {
            printf("Busco %d y encuentro %d repetido: %d veces\n", i,
                   elemento(p), numerorepeticiones(p));
        } else {
            printf("Busco %d y no encuentro nada\n", i);
        }
    }
    printf("Borro todos los nodos liberando la memoria:\n");
    a = eliminararbol(a);
    printf("Arbol vacio: ");
    visualizar(a);
    printf(".\n");
    printf("Altura del arbol: %i\n", altura(a));
}
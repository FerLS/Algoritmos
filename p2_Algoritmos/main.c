#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#define UMBRAL 1
#define K 1000

enum tCota {
    SUB, AJU, SOBR
};
typedef struct Cota {

    double value;
    char *string;

} cota;

cota cAscendeteIns(int n, enum tCota t) {

    cota c;
    switch (t) {
        case SUB:
            c.value = (pow(n, 0.8));
            c.string = "__[t(n)/n^0.8]____";
            break;
        case AJU:
            c.value = n;
            c.string = "[t(n)/n]______";
            break;
        case SOBR:
            c.value = (pow(n, 1.2));
            c.string = "[t(n)/n^1.2]___";
            break;
        default:
            c.value = 0;
            break;
    }
    return c;
}

cota cDescendeteIns(int n, enum tCota t) {

    cota c;
    switch (t) {
        case SUB:

            c.value = (pow(n, 1.8));
            c.string = "__[t(n)/n^1.8]___";
            break;

        case AJU:
            c.value = (n * n);
            c.string = "[t(n)/n^2]______";
            break;

        case SOBR:
            c.value = (pow(n, 2.2));
            c.string = "[t(n)/n^2.2]___";
            break;

        default:
            c.value = 0;
            break;

    }
    return c;

}

cota cAleatorioIns(int n, enum tCota t) {

    cota c;
    switch (t) {
        case SUB:

            c.value = (pow(n, 1.8));
            c.string = "__[t(n)/n^1.8]___";
            break;

        case AJU:
            c.value = (n * n);
            c.string = "[t(n)/n^2]______";
            break;

        case SOBR:
            c.value = (pow(n, 2.2));
            c.string = "[t(n)/n^2.2]___";
            break;

        default:
            c.value = 0;
            break;
    }

    return c;

}

cota cAscendeteRap(int n, enum tCota t) {

    cota c;

    switch (t) {
        case SUB:
            c.string =  UMBRAL == 1 ? "__[t(n)/n^0.8]___" : "__[t(n)/n^2.2]___";
            c.value = pow(n, 0.8);
            break;
        case AJU:
            c.string = UMBRAL == 1 ? "[t(n)/n^0.95 * log2 n]_" : UMBRAL == 10 ? "[t(n)/n^0.99 * log2 n]_" : "[t(n)/n^1.06 * log2 n]_";
            c.value = UMBRAL == 1 ? pow(n, 0.95) * log2(n) : UMBRAL == 10 ? pow(n, 0.99) * log2(n) : pow(n, 1.06) * log2(n);
            break;
        case SOBR:
            c.string =  UMBRAL == 1 ? "[t(n)/n^1.2]" : UMBRAL == 10 ? "[t(n)/n^1.2]" : "[t(n)/n^1.3]";
            c.value = UMBRAL == 1 ? pow(n, 1.2) : UMBRAL == 10 ? pow(n, 1.2) : pow(n, 1.3);
            break;
        default:
            c.value = 0;
            break;
    }
    return c;

}

cota cDescendeteRap(int n, enum tCota t) {

    cota c;

    switch (t) {
        case SUB:
            c.string = "__[t(n)/n]______";
            c.value = n;
            break;
        case AJU:
            c.string =  UMBRAL == 1 ? "[t(n)/n^1.06]______" : "[t(n)/n^1.1]______";
            c.value = UMBRAL == 1 ? pow(n, 1.06) : pow(n, 1.1);
            break;
        case SOBR:
            c.string = "[t(n)/n^1.3]";
            c.value = pow(n, 1.3);
            break;
        default:
            c.value = 0;
            break;
    }
    return c;
}

cota cAleatorioRap(int n, enum tCota t) {

    cota c;

    switch (t) {
        case SUB:
            c.string = "__[t(n)/n]___";
            c.value = n;
            break;
        case AJU:
            c.string =  UMBRAL == 1 ? "[t(n)/n^1.01]______" : UMBRAL == 10 ? "[t(n)/n^1.14]______" : "[t(n)/n^1.1]______1";
            c.value = UMBRAL == 1 ? pow(n, 1.1) : UMBRAL == 10 ? pow(n, 1.14) : pow(n, 1.1);
            break;
        case SOBR:
            c.string = "[t(n)/n^1.4]___";
            c.value = pow(n, 1.4);
            break;
        default:
            c.value = 0;
            break;
    }
    return c;

}

void ord_ins(int v[], int n) {
    int i, x, j;

    for (i = 0; i < n; i++) {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

void intercambiar(int v[], int x, int y) {

    int aux;
    aux = v[x];
    v[x] = v[y];
    v[y] = aux;
}

void ordenarAux(int v[], int izq, int der) {

    int x, i, j, pivote;
    if (izq + UMBRAL <= der) {
        x = (rand() % (der - izq + 1)) + izq;

        pivote = v[x];
        intercambiar(v, izq, x);
        i = izq + 1;
        j = der;

        while (i <= j) {
            while (i <= der && v[i] < pivote) {
                i = i + 1;
            }
            while (v[j] > pivote) {
                j = j - 1;
            }
            if (i <= j) {
                intercambiar(v, i, j);
                i = i + 1;
                j = j - 1;

            }
        }
        intercambiar(v, izq, j);
        ordenarAux(v, izq, j - 1);
        ordenarAux(v, j + 1, der);
    }
}

void ord_rapida(int v[], int n) {
    ordenarAux(v, 0, n - 1);
    if (UMBRAL > 1) {
        ord_ins(v, n);
    }
}

void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v[], int n) { /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n) {

    int i;
    for (i = 0; i < n; i++) {
        v[i] = i;
    }
}

void descendente(int v[], int n) {

    int i;
    for (i = n; i > 0; --i) {
        v[n - i] = i - 1;
    }
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void print_vector(int v[], int n) {
    int i;
    printf("  [");
    for (i = 0; i < n; i++) {
        printf("%3d", v[i]);
        if (i != n - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

void OrdenaryDesordenar(void (*ini)(int v[], int n), void(*algo)(int v[], int n)) {

    int n = 10;
    int v[n];

    ini(v, n);
    printf("\n- Desordenado :\t");
    print_vector(v, n);
    algo(v, n);
    printf("\n- Ordenado :\t");
    print_vector(v, n);

}

void TestOrdenacion() {

    printf("\nOrd Ins Ascendete\n");
    OrdenaryDesordenar(ascendente, ord_ins);
    printf("\nOrd Ins Descendete\n");
    OrdenaryDesordenar(descendente, ord_ins);
    printf("\nOrd Ins Aleatoria\n");
    OrdenaryDesordenar(aleatorio, ord_ins);
    printf("\nOrd Rap Ascendete\n");
    OrdenaryDesordenar(ascendente, ord_rapida);
    printf("\nOrd Rap Descendete\n");
    OrdenaryDesordenar(descendente, ord_rapida);
    printf("\nOrd Rap Aleatoria\n");
    OrdenaryDesordenar(aleatorio, ord_rapida);
}


double tiempos(void (*alg)(int v[], int tamanho), void (*vector)(int v[], int tamanho), int tamanho) {

    double t1, t2, t, prima;
    int i;
    int *v;

    v = malloc(tamanho * sizeof(int));
    vector(v, tamanho);

    t1 = microsegundos();
    alg(v, tamanho);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500) {
        t1 = microsegundos();
        for (i = 0; i < K; i++) {
            vector(v, tamanho);
            alg(v, tamanho);
        }
        t2 = microsegundos();
        prima = t2 - t1;
        t1 = microsegundos();
        for (i = 0; i < K; i++) {
            vector(v, tamanho);
        }
        t2 = microsegundos();
        t = t2 - t1;
        t = (prima - t) / K;
    }
    free(v);
    return t;
}

void CalComplejidad(void (*ini)(int v[], int n), void(*algo)(int v[], int n), cota (*cta)(int n, enum tCota t)) {


    printf(" ______[N]___________[Tiempo]____%s%s%s____[t<500]_ \n\n", cta(1, SUB).string, cta(1, AJU).string,
           cta(1, SOBR).string);

    double tiempo;
    for (int n = 500; n <= 32000; n *= 2) {

        tiempo = tiempos(algo, ini, n);
        printf("%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |", n,
               tiempo, tiempo / cta(n, SUB).value, tiempo / cta(n, AJU).value,
               tiempo / cta(n, SOBR).value);
        if (tiempo < 500) {
            printf("  (*)");
        }
        printf("\n    \t\t|               |               |               |                   |\n");
    }


}

void TestComplejidad() {
    printf("\n****************** Ordenación por INSERCION con inicialización ASCENDENTE ******************\n\n");
    CalComplejidad(ascendente, ord_ins, cAscendeteIns);
    printf("\n****************** Ordenación por INSERCION con inicialización DESCENDENTE ******************\n\n");
    CalComplejidad(descendente, ord_ins, cDescendeteIns);
    printf("\n\n\n****************** Ordenación por INSERCION con inicialización ALEATORIA ******************\n\n");
    CalComplejidad(aleatorio, ord_ins, cAleatorioIns);


    printf("\n****************** Ordenación RAPIDA con inicialización ASCENDENTE ******************\n\n");
    CalComplejidad(ascendente, ord_rapida, cAscendeteRap);
    printf("\n****************** Ordenación RAPIDA con inicialización DESCENDENTE ******************\n\n");
    CalComplejidad(descendente, ord_rapida, cDescendeteRap);
    printf("\n\n\n****************** Ordenación RAPIDA con inicialización ALEATORIA ******************\n\n");
    CalComplejidad(aleatorio, ord_rapida, cAleatorioRap);
}

int main() {

    inicializar_semilla();

    TestOrdenacion();
    TestComplejidad();


    return 0;
}
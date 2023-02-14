#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

#define K 1000

void inicializar_semilla() {
    srand(time(NULL));
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) {
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v[], int n) { /** se generan números pseudoaleatorio entre -n y +n */
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


void intercalar(int v[], int izq, int der, int centro) {

    int i = izq, j = centro + 1, k = 1;
    int aux[(der - izq) + 1];
    while (i <= centro && j <= der) {
        if (v[i] <= v[j]) {
            aux[k] = v[i];
            i = i+1;
        } else {
            aux[k] = v[j];
            j = j+1;
        }
        k = k+1;
    }
    while (i <= centro) {
        aux[k] = v[i];
        i = i+1;
        k = k+1;
    }
    while (j <= der) {
        aux[k] = v[j];
        j = j+1;
        k= k+1;
    }
    k = 1;
    for (i = izq; i <= der; i++) {
        v[i] = aux[k];
        k = k+1;;
    }

}

void ordenarAux(int v[], int izq, int der) {

    int centro;
    if ((der-izq) > 0) {
        centro = (izq + der) / 2;
        ordenarAux(v, izq, centro);
        ordenarAux(v, centro + 1, der);
        intercalar(v, izq, der, centro);

    }

}

void ordernar(int v[], int n) {

    ordenarAux(v, 0, n - 1);

}

double tiempos(void (*ini)(int v[], int n), int n) {
    double t1, t2, ta, tb, t;
    int i;
    int *v;
    v = malloc(n * sizeof(int));
    ini(v, n);
    ta = microsegundos();
    ordernar(v, n);
    tb = microsegundos();
    t = tb - ta;
    if (t < 500) {
        ta = microsegundos();
        for (i = 0; i < K; i++) {
            ini(v, n);
            ordernar(v, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < K; i++) {
            ini(v, n);
        }
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / K;
    }
    free(v);
    return t;
}

void ComplejidadDescendte() {
    double tiempo = 0.0;
    int n, max = 512000;
    printf("\nVector descendente\n");
    printf("\t - Cota subestimada f(n): n^(0.9)*log(n)\n");
    printf("\t - Cota ajustada g(n): n^(0.945)*log(n)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.1)*log(n)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]___"
           "____[t(n)/g(n)]_____[t(n)/h(n)]______[t<500]_ ");
    for (n = 500; n <= max; n = n * 2) {
        tiempo = tiempos(descendente, n);
        printf("\n%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |",
               n, tiempo, tiempo / (pow(n, 0.9) * log(n)), tiempo / (pow(n, 0.945)
               * log(n)),
               tiempo / (pow(n, 1.1) * log(n)));
        if (tiempo < 500) {
            printf("  (*)");
        }
    }
}

void ComplejidadAscendente() {
    double tiempo = 0.0;
    int n, max = 512000;
    printf("\nVector Ascendente\n");
    printf("\t - Cota subestimada f(n): n^(0.9)*log(n)\n");
    printf("\t - Cota ajustada g(n): n^(1)*log(n)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.1)*log(n)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]____"
           "___[t(n)/g(n)]_____[t(n)/h(n)]______[t<500]_ ");
    for (n = 500; n <= max; n = n * 2) {
        tiempo = tiempos(ascendente, n);
        printf("\n%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |",
               n, tiempo, tiempo / pow(n, 0.9) * log(n), (tiempo / pow(n, 1.2)
               * log(n)),
               tiempo / (pow(n, 1.1) * log(n)));
        if (tiempo < 500) {
            printf("  (*)");
        }
    }

}

void ComplejidadAleatoria() {
    double tiempo = 0.0;
    int n, max = 512000;
    printf("\nVector aleatorio\n");
    printf("\t - Cota subestimada f(n): n^(0.9)*log(n)\n");
    printf("\t - Cota ajustada g(n): n^(1.21)*log(n)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.1)*log(n)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]_______"
           "[t(n)/g(n)]_____[t(n)/h(n)]______[t<500]_ ");
    for (n = 500; n <= max; n = n * 2) {
        tiempo = tiempos(aleatorio, n);
        printf("\n%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |",
               n, tiempo, tiempo / (pow(n, 0.9) * log(n)), tiempo / (pow(n, 0.985)
               * log(n)),
               tiempo / (pow(n, 1.1) * log(n)));
        if (tiempo < 500) {
            printf("  (*)");
        }
    }
    printf("\n");
}

void TestOrdenacion() {

    int i, n = 10;
    int v[n];

    aleatorio(v, n);

    printf("Vector desordenado : \n");

    for (i = 0; i < n; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n\nVector ordenado : \n");

    ordernar(v, n);
    for (i = 0; i < n; ++i) {
        printf("%d ", v[i]);
    }
}

void TestComplejidad() {

    ComplejidadAscendente();
    ComplejidadDescendte();
    ComplejidadAleatoria();

}


int main() {

    inicializar_semilla();
    printf("********* Test Ordenacion *********\n\n");
    TestOrdenacion();
    printf("\n\n********* Test Ordenacion *********\n\n");
    TestComplejidad();


}
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include "monticulos.h"
#include <math.h>
#define K 1000

void inicializar_semilla(){
    srand(time(NULL));
}

double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v[], int n){ /** se generan números pseudoaleatorio entre -n y +n */
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

void crearMonticulo(int v[], int n){
    monticulo M;
    crear_monticulo(v,n,&M);
}

double tiempos(void (*ini)(int v[],int n),void (*alg)(int v[],int n),int n) {
    double t1, t2, ta, tb,t;
    int i;
    int *v;

    v = malloc(n * sizeof(int));
    ini(v,n);

    ta = microsegundos();
    alg(v,n);
    tb = microsegundos();
    t = tb - ta;
    if (t < 500) {
        ta = microsegundos();
        for (i = 0; i < K; i++) {
            ini(v,n);
            alg(v,n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < K; i++) {
            ini(v,n);
        }
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / K;
    }
    free(v);
    return t;
}

void TiempoCrear(){
    int n;
    double tiempo;

    printf("\n Creacion de Monticulos\n");
    printf(" ______[N]____________[t(n)]_________[O(n)]_____ \n");
    for (n = 500; n <= 128000; n = n * 2) {
        tiempo = tiempos(ascendente,crearMonticulo,n);
        printf("%10d    \t|%14.3f\t|%14.8f\n",
               n, tiempo, tiempo/n);
    }
}

void TestOrdenacion(){
    //int arr[] = {-9,7,-4,2,5,0,8,-1,-3,9};
    //int n = sizeof(arr) / sizeof(arr[0]);
    int n=10;
    int arr[n];
    aleatorio(arr,n);
    //Vector desordenado
    printf("Desordenado : \n");
    for (int i = 0; i < n; ++i) {
        printf("%d ",arr[i]);
    }
    //Vector con formato montículo
    printf("\nMontículo : \n");
    monticulo M;
    crear_monticulo(arr,n,&M);
    for (int i = 0; i <= M.ultimo; i++) {
        printf("%d ",M.vector[i]);
    }
    //Vector ordenado
    ord_monticulo(arr,n);
    printf("\nOrdenado :  \n");
    for (int i = 0; i < n; ++i) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void tiempos_mont() {
    double tiempo = 0.0, tmax = 1500000.0;
    int n, max = 128000;

    printf("\nMonticulo Ascendente\n");
    printf("\t - Cota subestimada f(n): n^(1.1)*log(n)\n");
    printf("\t - Cota ajustada g(n): n^(1.19)*log(n)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.32)*log(n)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]_______[t(n)/g(n)]_____[t(n)/h(n)]______[t<500]_ ");
    for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
        tiempo = tiempos(ascendente,ord_monticulo,n);
        printf("\n%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |",
               n, tiempo, tiempo/pow(n,1.1)*log(n), tiempo/pow(n,1.19)*log(n),
               tiempo/pow(n,1.32)*log(n));
        if(tiempo<500){
            printf("  (*)");
        }
    }
    printf("\nMonticulo descendente\n");
    printf("\t - Cota subestimada f(n): n^(1.1)*log(n)\n");
    printf("\t - Cota ajustada g(n): n^(1.24)*log(n)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.4)*log(n)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]_______[t(n)/g(n)]_____[t(n)/h(n)]______[t<500]_ ");
    for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
        tiempo = tiempos(descendente,ord_monticulo,n);
        printf("\n%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |",
               n, tiempo, tiempo/pow(n,1.1)*log(n), tiempo/pow(n,1.24)*log(n),
               tiempo/pow(n,1.4)*log(n));
        if(tiempo<500){
            printf("  (*)");
        }
    }
    printf("\nMonticulo aleatorio\n");
    printf("\t - Cota subestimada f(n): n^(1.1)*log(n)\n");
    printf("\t - Cota ajustada g(n): n^(1.21)*log(n)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.3)*log(n)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]_______[t(n)/g(n)]_____[t(n)/h(n)]______[t<500]_ ");
    for (n = 500; n <= max && tiempo <= tmax; n = n * 2) {
        tiempo = tiempos(aleatorio,ord_monticulo,n);
        printf("\n%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |",
              n, tiempo, tiempo/pow(n,1.1)*log(n), tiempo/pow(n,1.21)*log(n),
              tiempo/pow(n,1.3)*log(n));
        if(tiempo<500){
            printf("  (*)");
        }
    }
    printf("\n");
}

int main(void){
    inicializar_semilla();
    TestOrdenacion();
    TiempoCrear();
    tiempos_mont();
}

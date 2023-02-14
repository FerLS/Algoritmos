/*
Fernando Álvarez Rodríguez de Legísima
fernando.alvarezr@udc.es
Brais Sánchez Ferreiro
brais.sferreiro@udc.es 
*/
/*
Fernando Álvarez Rodríguez de Legísima
fernando.alvarezr@udc.es
Brais Sánchez Ferreiro
brais.sferreiro@udc.es
*/
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "arboles.h"


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

void aleatorio(int v[], int n){ /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

double tiempos(bool isBuscar, int n ) {

    double t1, t2, t;
    int *v;
    int i;
    arbol T = creararbol();
    v = malloc(n * sizeof(int));
    aleatorio(v,n);
    if(isBuscar){
        for (i = 0; i < n; ++i) {
            T = insertar(v[i], T);
        }
        aleatorio(v,n);
        t1 = microsegundos();
        for (i = 0; i < n; ++i) {
            buscar(v[i], T);
        }
    }else{
        t1 = microsegundos();
        for (i = 0; i < n; ++i) {
            T = insertar(v[i], T);
        }
    }
    t2 = microsegundos();
    t = t2 - t1;

    free(v);
    eliminararbol(T);
    return t;
}


void CalTiempos() {


    printf("\nTiempos de Insercion y Busqueda:\n\n");

    printf(" ______[N]__________[t_ins(n)]______[t_bus(n)]___\n");

    int counter = 0,i;
    double *vIns,*vBus;
    vBus = malloc(16 * sizeof(double));
    vIns = malloc(16 * sizeof(double));

    for ( i = 500; i<=256000; i *= 2) {


        vIns[counter] = tiempos(true, i);
        vBus[counter] = tiempos(false, i);

        if(vIns[counter] < 500 || vBus[counter] <500){
            counter++;

            continue;
        }

        printf("%10d    \t|%14.0lf\t|%14.0lf\t|\n", i,vIns[counter],vBus[counter]);
        counter++;

    }

    printf("\nInserción de n elementos:\n\n");
    printf("\t - Cota subestimada f(n): n^(1.1)\n");
    printf("\t - Cota ajustada g(n): n^(1.19)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.3)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]_______[t(n)/g(n)]_____[t(n)/h(n)]_____ \n");
    counter = 0;
    for(i=500;i<=256000;i=i*2){
        if(vIns[counter] < 500 ){
            counter++;
            continue;
        }

        printf("%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |\n",
               i, vIns[counter], vIns[counter] / pow(i, 1.1), vIns[counter] /  pow(i, 1.19),
               vIns[counter] / pow(i, 1.3));
        counter++;

    }
    counter=0;

    printf("\nBúsqueda de n elementos:\n\n");
    printf("\t - Cota subestimada f(n): n^(1.1)\n");
    printf("\t - Cota ajustada g(n): n^(1.23)\n");
    printf("\t - Cota sobreestimada h(n): n^(1.3)\n\n");
    printf(" ______[N]____________[t(n)]_______[t(n)/f(n)]_______[t(n)/g(n)]_____[t(n)/h(n)]_____ \n");
    for(i=500;i<=256000;i=i*2){
        if(vBus[counter] <500){
            counter++;
            continue;
        }

        printf("%10d    \t|%14.3f\t|%14.8f\t|%14.8f\t|%14.8f\t    |\n",
               i, vBus[counter], vBus[counter] / pow(i, 1.1), vIns[counter] / pow(i, 1.23),
               vBus[counter] / pow(i, 1.3));
        counter++;
    }

    free(vIns);
    free(vBus);
}

int main() {
    inicializar_semilla();
    test();
    CalTiempos();
    return 0;
}

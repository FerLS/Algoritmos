#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define K 1000

double microsegundos();

int fib1(int n);

int fib2(int n);

int fib3(int n);

void timeRecord(int n, int fib);

void testfib1();

void testfib2();

void testfib3();

void tabla(int n);

/* obtiene la hora actual en microsegundos */

struct fib {
    int (*fib_fun)(int n);
} fibs[] = {
        {fib1},
        {fib2},
        {fib3}
};


double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


int fib1(int n) {

    if (n < 2) return n;
    else return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n) {

    int i = 1, j = 0;
    for (int k = 0; k < n; ++k) {

        j = i + j;
        i = j - i;
    }
    return j;
}

int fib3(int n) {
    int i, j, k, h, t;
    i = 1;
    j = 0;
    k = 0;
    h = 1;
    while (n > 0) {
        if ((n % 2) != 0) {
            t = j * h;
            j = (i * h) + (j * k) + t;
            i = (i * k) + t;
        }
        t = h * h;
        h = (2 * k * h) + t;
        k = (k * k) + t;
        n = n / 2;
    }
    return j;
}


void timeRecord(int n, int fib) {

    double t1, t2, t, x, y, z;
    int counter = 0;
    t1 = microsegundos();
    fibs[fib - 1].fib_fun(n);
    t2 = microsegundos();
    t = t2 - t1;
    if (t < 500) {
        t1 = microsegundos();
        for (counter = 0; counter < K; ++counter) {
            fibs[fib - 1].fib_fun(n);
        }
        t2 = microsegundos();
        t = (t2 - t1) / 1000;
    }
    switch (fib) {
        case 1:
            x = t / pow((1 + sqrt(5)) / 2, n);
            y = t / pow(1.1f, n);
            z = t / pow(2, n);
            break;
        case 2:
            x = t / n;
            y = t / pow(n, 0.8f);
            z = t / (n * log10(n));
            break;
        case 3:
            x = t / log10(n);
            y = t / sqrt((log10(n)));
            z = t / pow(n, 0.5f);
            break;
        default:
            break;
    }

    printf("%10d    \t|%14.3f\t|%14.6f\t|%14.6f\t|%14.6f\t    |", n, t, x, y, z);
    if (counter > 0) { printf("  (*)"); }
    printf("\n    \t\t|               |               |               |                   |\n");
}

void testfib1() {

    timeRecord(2, 1);
    timeRecord(4, 1);
    timeRecord(8, 1);
    timeRecord(16, 1);
    timeRecord(32, 1);


}

void testfib2() {

    timeRecord(1000, 2);
    timeRecord(10000, 2);
    timeRecord(100000, 2);
    timeRecord(1000000, 2);
    timeRecord(10000000, 2);


}

void testfib3() {
    timeRecord(1000, 3);
    timeRecord(10000, 3);
    timeRecord(100000, 3);
    timeRecord(1000000, 3);
    timeRecord(10000000, 3);

}

void tabla(int n) {

    printf("n\t|\tfib1(n)\t\tfib2()\t\tfib(3)");
    printf("\n-----------------------------------------------------------");

    for (int i = 1; i <= n; ++i) {

        printf("\n%d\t|\t%d\t\t%d\t\t%d", i, fib1(i), fib2(i), fib3(i));

    }
    printf("\n");

}

void Tiempos() {
    printf("\n _______________________________________ Test con Fib1 ________________________________________ \n");

    printf(" ______[N]___________[Tiempo]_______[Ajustada]_____[Subestimada]____[SobreEstimada]_____[t<500]_ \n\n");
    testfib1();

    printf("\n _______________________________________ Test con Fib2 ________________________________________ \n");
    printf(" ______[N]___________[Tiempo]_______[Ajustada]_____[Subestimada]____[SobreEstimada]_____[t<500]_ \n\n");
    testfib2();


    printf("\n _______________________________________ Test con Fib3 ________________________________________ \n");
    printf(" ______[N]___________[Tiempo]_______[Ajustada]_____[Subestimada]____[SobreEstimada]_____[t<500]_ \n\n");

    testfib3();

}

int main() {

    Tiempos();
    printf("\n\n");
    tabla(20);


    return 0;
}
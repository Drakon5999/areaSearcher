#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAXARR 100000
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

double root(double f(double), double g(double), double f1(double), double g1(double),
            double a, double b, double eps) {
    double xlast=(a+b)/2, xcur = 0;
    double d;
    bool isRise = (f(a) - g(a) < 0);
    bool aboveChord = 2*(f(xlast) - g(xlast)) >= f(a) - g(a) + f(b) - g(b);
    bool first;
    if((isRise && !aboveChord) || (!isRise && aboveChord)) {
        d = b;
        first = true;
    }
    else {
        d = a;
        first = false;
    }
    xcur = d - (f(d)-g(d))/(f1(d)-g1(d));

    while ((first && ((signbit(f(xcur)-g(xcur)) > 0 && signbit(f(xcur-eps) - g(xcur-eps)) == 0)
                    || (signbit(f(xcur)-g(xcur)) == 0 && signbit(f(xcur-eps) - g(xcur-eps)) > 0))) ||
            (!first && ((signbit(f(xcur)-g(xcur)) > 0 && signbit(f(xcur+eps) - g(xcur+eps)) == 0)
            || (signbit(f(xcur)-g(xcur)) == 0 && signbit(f(xcur+eps) - g(xcur+eps)) > 0)))) {
        xlast = xcur;
        xcur = xlast - (f(xlast) - g(xlast)) / (f1(xlast) - g1(xlast));
    }
    return  xcur;
}
double integral(double f(double), double a, double b, double eps) {
    double *arrLast = malloc(sizeof(double) * MAXARR);
    double *arrCur = malloc(sizeof(double) * MAXARR);
    double intCur, intLast;
    int n = 2;
    double h = (b-a)/n;
    arrCur[0] = f(a)/2;
    arrCur[1] = f((a+b)/2);
    arrCur[2] = f(b)/2;
    intCur = (arrCur[0] + arrCur[1] + arrCur[2]) * h;
    intLast = intCur*10 +1;
    while (fabs(intCur - intLast) / 3 > eps) {
        n*=2;
        if (n > MAXARR) {
            printf("ERROR: Array size is too small");
            return intCur;
        }
        h = (b-a)/n;
        intLast = intCur;
        double *tmp = arrLast;
        arrLast = arrCur;
        arrCur = tmp;
        intCur = 0;
        for (int i = 0; i <= n; ++i) {
            if(i%2 == 0) {
                arrCur[i] = arrLast[i/2];
            }
            else {
                arrCur[i] = f(a+i*h);
            }
            intCur += arrCur[i];
        }
        intCur *= h;
    }
    return intCur;
}

int main(int argc, char * argv[]) {

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAXARR 100000
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double f11(double x);
extern double f21(double x);
extern double f31(double x);
int its = 0;

/*double f1(double x) { return  exp(-x) + 3; }
double f2(double x) { return 2*x-2; }
double f3(double x) { return 1/x; }
double f11(double x) { return -exp(-x); }
double f21(double x) { return 2; }
double f31(double x) { return  -1/(x*x); }*/

double root(double f(double), double g(double), double df1(double), double dg1(double),
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
    xcur = d - (f(d)-g(d))/(df1(d)-dg1(d));
    its = 1;
    while (!((first && ((signbit(f(xcur)-g(xcur)) > 0 && signbit(f(xcur-eps) - g(xcur-eps)) == 0)
                    || (signbit(f(xcur)-g(xcur)) == 0 && signbit(f(xcur-eps) - g(xcur-eps)) > 0))) ||
            (!first && ((signbit(f(xcur)-g(xcur)) > 0 && signbit(f(xcur+eps) - g(xcur+eps)) == 0)
            || (signbit(f(xcur)-g(xcur)) == 0 && signbit(f(xcur+eps) - g(xcur+eps)) > 0))))) {
        xlast = xcur;
        xcur = xlast - (f(xlast) - g(xlast)) / (df1(xlast) - dg1(xlast));
        its++;
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
    double eps1 = 0.00001;
    double eps2 = 0.00001;
    double x12, x13, x23;
    x12 = root(f1, f2, f11, f21, 2, 3, eps1);
    int x12c = its;
    x13 = root(f1, f3, f11, f31, 0.2, 0.5, eps1);
    int x13c = its;
    x23 = root(f2, f3, f21, f31, 1, 1.5, eps1);
    int x23c = its;
    if (argc > 1) {
        if (!strcmp("-help",argv[1])) {
            printf("Run without parameters for print answer\n");
            printf("-ax for print absciss of intersection points\n");
            printf("-cx for print iterations counts for root finder\n");
            printf("-tr for for test root function\n");
            printf("-ti for for test integral function\n");
        }
        else if (!strcmp("-ax", argv[1])) {
            printf("F1 and F2: %f\nF1 and F3: %f\nF2 and F3: %f\n", x12, x13, x23);
        }
        else if (!strcmp("-cx", argv[1])) {
            printf("For F1 and F2: %d iterations\n", x12c);
            printf("For F1 and F3: %d iterations\n", x13c);
            printf("For F2 and F3: %d iterations\n", x23c);
        }
        else if (!strcmp("-tr", argv[1])) {
            printf("Please enter arguments in format: function 1 {f1,f2,f3}\n function 2 {f1,f2,f3}\n start point\n end point\n epsilon");
            char namef[3];
            char nameg[3];
            double sp, ep, eps;
            scanf("%2s%2s%lf%lf%lf", namef, nameg, &sp, &ep, &eps);
            if (!strcmp(namef,"f1")) {
                if (!strcmp(nameg, "f1")) {
                    printf("\nResult: %f\n", root(f1, f1, f11, f11, sp, ep, eps));
                }
                else if (!strcmp(nameg, "f2")) {
                    printf("\nResult: %f\n", root(f1, f2, f11, f21, sp, ep, eps));
                }
                else if (!strcmp(nameg, "f3")) {
                    printf("\nResult: %f\n", root(f1, f3, f11, f31, sp, ep, eps));
                }
            }
            else if (!strcmp(namef,"f2")) {
                if (!strcmp(nameg, "f1")) {
                    printf("\nResult: %f\n", root(f2, f1, f21, f11, sp, ep, eps));
                }
                else if (!strcmp(nameg, "f2")) {
                    printf("\nResult: %f\n", root(f2, f2, f21, f21, sp, ep, eps));
                }
                else if (!strcmp(nameg, "f3")) {
                    printf("\nResult: %f\n", root(f2, f3, f21, f31, sp, ep, eps));
                }
            }
            else if (!strcmp(namef,"f3")) {
                if (!strcmp(nameg, "f1")) {
                    printf("\nResult: %f\n", root(f3, f1, f31, f11, sp, ep, eps));
                }
                else if (!strcmp(nameg, "f2")) {
                    printf("\nResult: %f\n", root(f3, f2, f31, f21, sp, ep, eps));
                }
                else if (!strcmp(nameg, "f3")) {
                    printf("\nResult: %f\n", root(f3, f3, f31, f31, sp, ep, eps));
                }
            }

        }
        else if (!strcmp("-ti", argv[1])) {
            printf("Please enter arguments in format: function {f1,f2,f3}\n start point\n end point\n epsilon");
            char namef[3];
            double sp, ep, eps;
            scanf("%2s%lf%lf%lf", namef, &sp, &ep, &eps);
            if (!strcmp(namef,"f1")) {
                    printf("\nResult: %f\n", integral(f1, sp, ep, eps));
            }
            else if (!strcmp(namef,"f2")) {
                printf("\nResult: %f\n", integral(f2, sp, ep, eps));
            }
            else if (!strcmp(namef,"f3")) {
                printf("\nResult: %f\n", integral(f3, sp, ep, eps));
            }
        }

    }
    else {
        double i1 = integral(f1, x13, x12, eps2);
        printf("F1 from %f to %f integral is %f\n", x13, x12, i1);
        double i2 = integral(f2, x23, x12, eps2);
        printf("F2 from %f to %f integral is %f\n", x23, x12, i2);
        double i3 = integral(f3, x13, x23, eps2);
        printf("F3 from %f to %f integral is %f\n", x13, x23, i3);
        double ans = i1 - i2 - i3;
        printf("Area of the figure: %f\n", ans);
    }
    return 0;
}
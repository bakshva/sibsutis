#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double f(long double x) {
    return 3.0L - sqrtl(x) - 0.5L * logl(x);
}

long double steffensen(long double a, long double b, long double eps) {
    long double x0 = (a + b) / 2.0L, x1;
    int iter = 0;
    while (1) {
        long double fx0 = f(x0);
        long double denom = f(x0 + fx0) - fx0;
        if (fabsl(denom) < 1e-15L) {
            printf("Деление на 0 или очень малая разность в точке x = %.10Lf.\n", x0);
            break;
        }
        x1 = x0 - (fx0 * fx0) / denom;
        iter++;
        if (fabsl(x1 - x0) < eps) {
            printf("Сошлось за %d итераций, x = %.10Lf\n", iter, x1);
            return x1;
        }
        x0 = x1;
        if (iter > 10000) {
            printf("Превышено максимальное число итераций.\n");
            break;
        }
    }
    return x0;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Использование: %s a b eps\n", argv[0]);
        return 1;
    }
    long double a = strtold(argv[1], NULL);
    long double b = strtold(argv[2], NULL);
    long double eps = strtold(argv[3], NULL);
    if (a <= 0.0L || b <= 0.0L) {
        printf("Границы должны быть > 0, так как f(x) содержит sqrt(x) и ln(x).\n");
        return 1;
    }
    long double fa = f(a);
    long double fb = f(b);
    if (fa * fb > 0.0L) {
        printf("f(a) и f(b) одного знака. Корень может не лежать в [%.2Lf, %.2Lf].\n", a, b);
        return 1;
    }
    steffensen(a, b, eps);
    return 0;
}

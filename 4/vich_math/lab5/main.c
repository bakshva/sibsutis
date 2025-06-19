#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x) {
    return exp(-x * x);
}


double trapezoidal_integration(double a, double b, double epsilon) {
    int n = 1; 
    double h = (b - a) / n;
    double integral_prev = 0.0;
    double integral_current = (f(a) + f(b)) * h / 2.0;
    
    do {
        integral_prev = integral_current;
        n *= 2; 
        h = (b - a) / n;
        integral_current = 0.0;
        
        
        for (int i = 0; i < n; i++) {
            double x1 = a + i * h;
            double x2 = x1 + h;
            integral_current += (f(x1) + f(x2)) * h / 2.0;
        }
        
    } while (fabs(integral_current - integral_prev) > epsilon);
    
    return integral_current;
}

int main() {
    double a, b, epsilon;
    
    printf("Введите начало отрезка a: ");
    scanf("%lf", &a);
    
    printf("Введите конец отрезка b: ");
    scanf("%lf", &b);
    
    printf("Введите погрешность epsilon: ");
    scanf("%lf", &epsilon);
    
    double result = trapezoidal_integration(a, b, epsilon);
    printf("Значение интеграла: %.15lf\n", result);
    
    return 0;
}

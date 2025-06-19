#include <stdio.h>
#include <stdlib.h>

#define N 2798170.0

double alpha_E = 0.999;
double alpha_I = 0.999;
double kappa   = 0.042;
double rho     = 0.952;
double beta    = 0.999;
double mu      = 0.0188;
double g       = 0;
double c_isol  = 0;

double S0 = N - 99 - 24;
double E0 = 99.0;
double I0 = 0.0;
double R0 = 24.0;
double D0 = 0.0;

double c(double t) {
    return 1.0;
}

double h = 1.0;
int    T_max = 90;

void euler_method() {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        perror("");
        return;
    }

    double S = S0, E = E0, I = I0, R = R0, D = D0;
    double dS, dE, dI, dR, dD;

    printf("Day\t  S\t\t E\t  I\t  R\t\t  D\n");
    printf("-------------------------------------------------------------\n");
    fprintf(fp, "Day\t  S\t\t E\t  I\t  R\t\t  D\n");
    fprintf(fp, "-------------------------------------------------------------\n");

    for (int t = 0; t <= T_max; t++) {
        printf("%-3d %10.2f %10.2f %10.2f %10.2f %10.2f\n", t, S, E, I, R, D);
        fprintf(fp, "%-3d %10.2f %10.2f %10.2f %10.2f %10.2f\n", t, S, E, I, R, D);

        dS = -c(t) * ((alpha_I * S * I / N) + (alpha_E * S * E / N)) + g * R;
        dE =  c(t) * ((alpha_I * S * I / N) + (alpha_E * S * E / N)) - (kappa + rho) * E;
        dI =  kappa * E - (beta + mu) * I;
        dR =  beta * I + rho * E - g * R;
        dD =  mu * I;

        S += h * dS;
        E += h * dE;
        I += h * dI;
        R += h * dR;
        D += h * dD;
    }

    fclose(fp);
}

int main() {
    euler_method();
    return 0;
}

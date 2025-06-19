#include <stdio.h>
#include <stdlib.h>

void buildDivDiffTable(int n, const double x[], const double y[], double diff[][100]) {
    for (int i = 0; i < n; i++) {
        diff[i][0] = y[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            diff[i][j] = (diff[i + 1][j - 1] - diff[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

double newtonPolynomialValue(int n, const double x[], double diff[][100], double X) {
    double result = diff[0][0];
    for (int j = 1; j < n; j++) {
        double term = diff[0][j];
        for (int i = 0; i < j; i++) {
            term *= (X - x[i]);
        }
        result += term;
    }
    return result;
}

int main() {
    FILE *fp = fopen("in.txt", "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }
    
    int n;
    fscanf(fp, "%d", &n);
    double x[100], y[100], diff[100][100];
    
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%lf", &x[i]);
    }
    
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%lf", &y[i]);
    }
    
    double X;
    fscanf(fp, "%lf", &X);
    fclose(fp);
    
    buildDivDiffTable(n, x, y, diff);
    double result = newtonPolynomialValue(n, x, diff, X);
    printf("%lf\n", result);
    return 0;
}

#include <stdio.h>

#define MAX_N 100
#define EPS 1e-9

int gauss(int n, double a[MAX_N][MAX_N], double x[MAX_N], double b[MAX_N]) {
    int i, j, k, imax;
    double maxEl, c;

    for (k = 0; k < n; k++) {
        imax = k;
        maxEl = (a[k][k] < 0) ? -a[k][k] : a[k][k];
        for (i = k + 1; i < n; i++) {
            double absVal = (a[i][k] < 0) ? -a[i][k] : a[i][k];
            if (absVal > maxEl) {
                maxEl = absVal;
                imax = i;
            }
        }

        if (maxEl < EPS) {
            printf("Ошибка: матрица вырождена или система не имеет единственного решения.\n");
            return 1;
        }

        if (imax != k) {
            for (j = 0; j < n; j++) {
                double temp = a[k][j];
                a[k][j] = a[imax][j];
                a[imax][j] = temp;
            }
            double tempB = b[k];
            b[k] = b[imax];
            b[imax] = tempB;
        }

        c = a[k][k];
        for (j = k; j < n; j++) {
            a[k][j] /= c;
        }
        b[k] /= c;

        for (i = k + 1; i < n; i++) {
            c = a[i][k];
            for (j = k; j < n; j++) {
                a[i][j] -= c * a[k][j];
            }
            b[i] -= c * b[k];
            a[i][k] = 0;
        }
    }

    for (i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
    }
    return 0;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл input.txt\n");
        return 1;
    }

    int n, i, j;
    double a[MAX_N][MAX_N], b[MAX_N], x[MAX_N];

    fscanf(file, "%d", &n);
    if (n <= 0 || n > MAX_N) {
        printf("Ошибка: некорректный размер матрицы\n");
        fclose(file);
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(file, "%lf", &a[i][j]);
        }
        fscanf(file, "%lf", &b[i]);
    }
    fclose(file);

    if (gauss(n, a, x, b)) {
        return 1;
    }

    printf("Решение системы:\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] = %.6f\n", i, x[i]);
    }

    return 0;
}

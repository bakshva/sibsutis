#include <stdio.h>
#define N 4

double ab(double x){return x<0?-x:x;}

void readData(double A[N][N], double B[N]){
    FILE *f = fopen("input.txt", "r");
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            fscanf(f, "%lf", &A[i][j]);
        }
        fscanf(f, "%lf", &B[i]);
    }
    fclose(f);
}

void printVector(double x[N]){
    int i;
    for(i = 0; i < N; i++){
        printf("x%d = %.6lf\n", i + 1, x[i]);
    }
}

void simpleIteration(double A[N][N], double B[N], double x[N], double tol){
    double x_new[N];
    int i, j, iter = 0, max_iter = 10000;
    for(i = 0; i < N; i++){
        x[i] = 0;
    }
    while(iter < max_iter){
        for(i = 0; i < N; i++){
            double sum = 0;
            for(j = 0; j < N; j++){
                if(j != i) sum += A[i][j] * x[j];
            }
            x_new[i] = (B[i] - sum) / A[i][i];
        }
        double diff = 0;
        for(i = 0; i < N; i++){
            double d = ab(x_new[i] - x[i]);
            if(d > diff) diff = d;
            x[i] = x_new[i];
        }
        if(diff < tol) break;
        iter++;
    }
    printf("Количество итераций: %d\n", iter);
}

int main(){
    double A[N][N], B[N], x[N];
    double tol = 0.001;
    readData(A, B);
    simpleIteration(A, B, x, tol);
    printVector(x);
    return 0;
}

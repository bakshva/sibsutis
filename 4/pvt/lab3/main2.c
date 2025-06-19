#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double getrand(unsigned int *seed) 
{
    return (double)rand_r(seed) / RAND_MAX;
}

double func(double x, double y) {
    return exp(x - y);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <num_threads> [output_file]\n", argv[0]);
        return 1;
    }
    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);

    const int n = 100000000; // количество точек
    double t = omp_get_wtime();
    printf("Numerical integration by Monte Carlo method: n = %d, threads = %d\n", n, num_threads);
    
    int in = 0; // счетчик попавших точек
    double s = 0; 
    
    #pragma omp parallel
    {
        double s_loc = 0; // локальная сумма для потока
        int in_loc = 0;
        unsigned int seed = omp_get_thread_num();
        
        #pragma omp for nowait
        for (int i = 0; i < n; i++) {
            double x = getrand(&seed) - 1; 
            double y = getrand(&seed); 
            in_loc++;
            s_loc += func(x, y);
        }
        
        #pragma omp atomic
        s += s_loc;
        #pragma omp atomic
        in += in_loc;
    }
    
    double v = 1; // площадь области интегрирования
    double res = v * s / in;
    t = omp_get_wtime() - t;
    
    printf("Result: %.12f, n %d\n", res, n);
    printf("Elapsed time (sec.): %.6f\n", t);

    
    const char *filename = (argc >= 3) ? argv[2] : "results.csv";
    FILE *fp = fopen(filename, "a");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }
    fprintf(fp, "%d %.6f\n", num_threads, t);
    fclose(fp);

    return 0;
}

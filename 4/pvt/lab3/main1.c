#include <stdio.h>
#include <math.h>
#include <omp.h>

double func(double x)
{
    return (log(1+x))/x;
}

int main(int argc, char **argv)
{
    double t = omp_get_wtime();
    const double eps = 1E-5; // 10**5
    const double a = 0.1;
    const double b = 1.0;
    const int n0 = 100000000;
    
    if (argc < 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }
    int num_threads = atoi(argv[1]);
    omp_set_num_threads(num_threads);
    

    double sq[2]; 
    #pragma omp parallel
    {
        
        int n = n0, k;
        double delta = 1;
        for (k = 0; delta > eps; n *=2, k^= 1){
            double h = (b - a) / n;
            double s = 0.0;
            sq[k] = 0;
            #pragma omp barrier

            #pragma omp for nowait
            for (int i = 0; i < n; i++)
                s += func(a + h * (i + 0.5));
            
            #pragma omp atomic
            sq[k] += s * h;

            #pragma omp barrier
            if (n > n0){
                delta = fabs(sq[k] - sq[k ^ 1]) / 3.0; 
            }
        }

        #pragma omp master 
        {
            printf("Num integration: [%f, %f], n0 = %d, EPS = %f on %d threads\n", a, b, n0, eps, num_threads);
            printf("Result: %.12f; Runge rule: EPS %e, n: %d\n", sq[k], eps, n / 2);
        }
        
    }
    t = omp_get_wtime() - t;
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

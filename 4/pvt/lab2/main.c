#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <omp.h>
 

void matrix_vector_product(double *a, double *b, double *c, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        c[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            c[i] += a[i * cols + j] * b[j];
        }
    }
}

void matrix_vector_product_omp(double *a, double *b, double *c, int rows, int cols) {
    #pragma omp parallel
    {
        int threadid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        int items_per_thread = rows / nthreads;
        int lb = threadid * items_per_thread;
        int ub = (threadid == nthreads - 1) ? (rows - 1) : (lb + items_per_thread - 1);

        for (int i = lb; i <= ub; i++) {
            c[i] = 0.0;
            for (int j = 0; j < cols; j++) {
                c[i] += a[i * cols + j] * b[j];
            }
        }
    }
}

double run_parallel(int M, int N, int threads) {
    omp_set_num_threads(threads);
    
    double *a, *b, *c;
    a = malloc(sizeof(*a) * M * N);
    b = malloc(sizeof(*b) * N);
    c = malloc(sizeof(*c) * M);

    if (!a || !b || !c) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = i + j;
        }
    }
    for (int j = 0; j < N; j++) {
        b[j] = j;
    }

    double t = omp_get_wtime();
    matrix_vector_product_omp(a, b, c, M, N);
    t = omp_get_wtime() - t;

    free(a);
    free(b);
    free(c);
    return t;
}

double run_serial(int M, int N) {
    double *a, *b, *c;
    a = malloc(sizeof(*a) * M * N);
    b = malloc(sizeof(*b) * N);
    c = malloc(sizeof(*c) * M);

    if (!a || !b || !c) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = i + j;
        }
    }
    for (int j = 0; j < N; j++) {
        b[j] = j;
    }

    double t = omp_get_wtime();
    matrix_vector_product(a, b, c, M, N);
    t = omp_get_wtime() - t;

    free(a);
    free(b);
    free(c);
    return t;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <matrix_size> <threads> [output_file]\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int threads = atoi(argv[2]);
    
    if (size <= 0 || threads <= 0) {
        printf("Invalid parameters! Size and threads must be positive integers.\n");
        return 1;
    }

    int M = size, N = size;
    printf("Matrix-vector product (c[m] = a[m, n] * b[n]; m = %d, n = %d)\n", M, N);
    printf("Memory used: %" PRIu64 " MiB\n", ((uint64_t)(M * N + M + N) * sizeof(double)) >> 20);
    printf("Using %d OpenMP threads\n", threads);

    double time_serial = run_serial(M, N);
    double time_parallel = run_parallel(M, N, threads);

    printf("Elapsed time (serial): %.6f sec.\n", time_serial);
    printf("Elapsed time (parallel): %.6f sec.\n", time_parallel);

    const char *filename = (argc >= 4) ? argv[3] : "results.csv";
    FILE *fp = fopen(filename, "a");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    fprintf(fp, "%d %d %.6f %.6f\n", size, threads, time_serial, time_parallel);
    fclose(fp);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 10000000
#define NUM_RUNS 20
// меняем местами переменные
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
// разбиение массива
int partition(int *arr, int left, int right)
{
    int mid = left + (right - left) / 2;
    int pivot = arr[mid]; // средний элемент массива
    swap(&arr[mid], &arr[right]);
    int i = left;
    for (int j = left; j < right; j++)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]); // возврат
    return i;
}
// последовательная версия
void quicksort_seq(int *arr, int left, int right)
{
    if (left < right)
    {
        int pi = partition(arr, left, right);
        quicksort_seq(arr, left, pi - 1);  // левая часть
        quicksort_seq(arr, pi + 1, right); // правая часть
    }
}

void quicksort_omp(int *arr, int left, int right, int THRESHOLD)
{
    if (right - left + 1 <= THRESHOLD)
    {
        quicksort_seq(arr, left, right); 
        return;
    }
    if (left < right)
    {
        int pi = partition(arr, left, right);
#pragma omp task shared(arr) 
        quicksort_omp(arr, left, pi - 1, THRESHOLD);
#pragma omp task shared(arr)
        quicksort_omp(arr, pi + 1, right, THRESHOLD);
#pragma omp taskwait
    }
}


int is_sorted(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i - 1] > arr[i])
            return 0;
    }
    return 1;
}

void write_results(const char *filename, int size, int threshold, double time)
{
    FILE *f = fopen(filename, "a");
    if (!f)
    {
        perror("Ошибка открытия файла для записи");
        return;
    }
    fprintf(f, "%d %d %lf\n", size, threshold, time);
    fclose(f);
}

int main()
{
    int sizes[] = {100000, 500000, 1000000, 5000000, 10000000};
    int thresholds[] = {100, 1000, 10000, 50000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_thresholds = sizeof(thresholds) / sizeof(thresholds[0]);

    const char *filename = "quicksort_results.txt";
    remove(filename);

    int *arr = malloc(MAX_SIZE * sizeof(int));
    int *copy = malloc(MAX_SIZE * sizeof(int));
    if (!arr || !copy)
    {
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    srand(3);
    for (int i = 0; i < MAX_SIZE; i++)
    {
        arr[i] = rand();
    }

    omp_set_num_threads(omp_get_max_threads());

    for (int s = 0; s < num_sizes; s++)
    {
        int size = sizes[s];

        
        double total_seq_time = 0.0;
        for (int run = 0; run < NUM_RUNS; run++)
        {
            for (int i = 0; i < size; i++)
            {
                copy[i] = arr[i];
            }
            double t1 = omp_get_wtime();
            quicksort_seq(copy, 0, size - 1);
            double t2 = omp_get_wtime();
            if (!is_sorted(copy, size))
            {
                printf("Ошибка сортировки последовательной для размера %d\n", size);
                break;
            }
            total_seq_time += (t2 - t1);
        }
        double avg_seq_time = total_seq_time / NUM_RUNS;
        write_results(filename, size, 0, avg_seq_time);

        for (int th = 0; th < num_thresholds; th++)
        {
            int threshold = thresholds[th];
            double total_par_time = 0.0;

            for (int run = 0; run < NUM_RUNS; run++)
            {
                for (int i = 0; i < size; i++)
                {
                    copy[i] = arr[i];
                }
                double t3 = omp_get_wtime();
#pragma omp parallel
                {
#pragma omp single nowait 
                    quicksort_omp(copy, 0, size - 1, threshold);
                }
                double t4 = omp_get_wtime();
                if (!is_sorted(copy, size))
                {
                    printf("Ошибка сортировки параллельной для размера %d, threshold %d\n", size, threshold);
                    break;
                }
                total_par_time += (t4 - t3);
            }

            double avg_par_time = total_par_time / NUM_RUNS;
            printf("Size: %d, Threshold: %d, Avg Time: %.5f s\n", size, threshold, avg_par_time);
            write_results(filename, size, threshold, avg_par_time);
        }
    }

    free(arr);
    free(copy);

    return 0;
}

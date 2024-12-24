#include <iostream>
#include <cstdlib>
#include <ctime>

// Использование пространства имен std
using namespace std;

// Функция для генерации случайного массива
int *genRandArray(int size, int maxValue)
{
    // Выделение памяти для массива
    int *arr = new int[size + 1];
    arr[0] = size; // Первый элемент массива хранит его размер
    for (int i = 0; i < size; i++)
    {
        // Заполнение массива случайными числами
        arr[i + 1] = rand() % maxValue;
    }
    return arr; // Возврат указателя на массив
}

// Функция для печати массива
void print(int *arr)
{
    for (int i = 0; i < arr[0]; i++)
    {
        // Печать элементов массива
        cout << arr[i + 1] << " | ";
    }
}

int main()
{
    srand(time(0));             // Инициализация генератора случайных чисел
    int size = rand() % 10 + 1; // Генерация случайного размера массива от 1 до 10
    cout << size << ": ";
    int maxValue = 100;                      // Максимальное значение элементов массива
    int *arr = genRandArray(size, maxValue); // Генерация случайного массива
    print(arr);                              // Печать массива
    // Очистка выделенной памяти
    delete[] arr;
}

#include <iostream>
#include <cstdlib>
#include <ctime>

// Использование пространства имен std
using namespace std;

// Функция для генерации случайного массива
int *genRandArray(int size, int maxValue)
{
    // Выделение памяти для массива
    int *arr = new int[size + 1];
    arr[0] = size; // Первый элемент массива хранит его размер
    for (int i = 0; i < size; i++)
    {
        // Заполнение массива случайными числами
        arr[i + 1] = rand() % maxValue;
    }
    return arr; // Возврат указателя на массив
}

// Функция для генерации случайной матрицы
int **genRandMatrix(int intsize, int intmaxValue)
{
    // Выделение памяти для матрицы (двумерного массива)
    int **arr = new int *[intsize];
    for (int i = 0; i < intsize; i++)
    {
        // Генерация строк матрицы как случайных массивов
        arr[i] = genRandArray(rand() % 10 + 1, intmaxValue);
    }
    return arr; // Возврат указателя на матрицу
}

// Функция для печати матрицы
void printMatrix(int **matrix, int intmaxValue)
{
    for (int i = 0; i < intmaxValue; i++)
    {
        // Печать размера текущей строки матрицы
        cout << matrix[i][0] << ": ";
        for (int j = 0; j < matrix[i][0] - 1; j++)
        {
            // Печать элементов строки матрицы
            cout << matrix[i][j + 1] << " | ";
        }
        // Печать последнего элемента строки матрицы
        cout << matrix[i][(matrix[i][0] - 1)];
        cout << endl;
    }
}

int main()
{
    srand(time(0));             // Инициализация генератора случайных чисел
    int size = rand() % 10 + 1; // Генерация случайного размера матрицы от 1 до 10
    cout << size << endl;
    int maxValue = 100;                           // Максимальное значение элементов массива
    int **matrix = genRandMatrix(size, maxValue); // Генерация случайной матрицы
    printMatrix(matrix, size);                    // Печать матрицы

    // Очистка выделенной памяти
    for (int i = 0; i < size; i++)
    {
        delete[] matrix[i]; // Удаление строк матрицы
    }
    delete[] matrix; // Удаление самой матрицы
}

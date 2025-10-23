#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
const int N0 = 15;
void insertion_sort(int* A, int N) //сортировка вставками
{
    int i, j, t;
    for (i = 0; i < N; i++)
    {
        for (j = i; j > 0 && A[j - 1] > A[j]; j--)
        {
            t = A[j];
            A[j] = A[j - 1];
            A[j - 1] = t;
        }
    }
}
void choice_sort(int* A, int N) //сортировка выбором
{
    int i, j, t, min;
    for (i = 0; i < N; i++)
    {
        min = i;
        for (j = i; j < N; j++)
        {
            if (A[j] < A[min]) min = j;
        }
        t = A[min];
        A[min] = A[i];
        A[i] = t;
    }
}
int* merge(int* L, int* R, int n) //функция слияния
{
    int* mergedLR = (int*)malloc(n * sizeof(int));
    for (int k = 0, i = 0, j = 0; k < n; k++)
    {
        if (i < n / 2 && j < n / 2 + n % 2)
        {
            if (L[i] > R[j])
            {
                mergedLR[k] = R[j];
                j++;
            }
            else
            {
                mergedLR[k] = L[i];
                i++;
            }
        }
        else
        {
            if (i >= n / 2)
            {
                while (k < n)
                {
                    mergedLR[k] = R[j];
                    j++;
                    k++;
                }
            }
            if (j >= n / 2 + n % 2)
            {
                while (k < n)
                {
                    mergedLR[k] = L[i];
                    i++;
                    k++;
                }
            }
        }
        
    }
    return mergedLR;
}
int* merge_sort(int* A, int N) //сортировка слиянием
{
    if (N <= 1) return A;
    int* left = (int*) malloc(N / 2 * sizeof(int));
    for (int i = 0, j = 0; i < N / 2; i++, j++)
    {
        left[j] = A[i];
    }
    int* right = (int*) malloc((N / 2 + N % 2) * sizeof(int));
    for (int i = N / 2, j = 0; i < N; i++, j++)
    {
        right[j] = A[i];
    }
    left = merge_sort(left, N / 2);
    right = merge_sort(right, N / 2 + N % 2);
    int* result = merge(left, right, N);
    return result;
}
void heapify(int* A, int root, int size) //функция упорядочивания в кучу
{
    int t;
    int largest = root, left = 2 * root + 1, right = 2 * root + 2;
    if (left < size && A[left] > A[largest]) largest = left;
    if (right < size && A[right] > A[largest]) largest = right;
    if (largest != root)
    {
        t = A[root];
        A[root] = A[largest];
        A[largest] = t;
        heapify(A, largest, size);
    }
}
void heap_sort(int* A, int N) //сортировка кучей
{
    int i, t;
    for (i = N / 2 - 1; i >= 0; i--)
    {
        heapify(A, i, N);
    }
    for (i = N - 1; i >= 1; i--)
    {
        t = A[0];
        A[0] = A[i];
        A[i] = t;
        heapify(A, 0, i);
    }
}
int main()
{
    int A[N0]; //массив
    char choice = ' '; //переменная выбора пользователя
    std::ifstream file;
    file.open("array.txt"); //открытие файла
    if (file.is_open())
    {
        std::cout << "initial array is: "; //чтение неотсортированного
        for (int k = 0; k < N0; k++)
        {
            file >> A[k];
            std::cout << A[k] << ' '; //и вывод на экран
        }
        //предложение пользователю выбрать один метод, все методы или выйти из программы:
        std::cout << "\nchoose sorting method:\ninsertion (i)\nchoice (c)\nheap (h)\nmerge (m)\nall (a)\nexit (e)\n";
        //цикл для повторного ввода в случае выбора несуществующего варианта:
        while (choice != 'i' && choice != 'c' && choice != 'm' && choice != 'h' && choice != 'a' && choice != 'e')
        {
            std::cin >> choice;
            if (choice == 'i' || choice == 'a')
            {
                insertion_sort(A, N0);
                std::cout << "insertion method:\n";
                for (int k = 0; k < N0; k++) //вывод отсортированного на экран
                    std::cout << A[k] << ' ';
                std::cout << '\n';
            }
            if (choice == 'c' || choice == 'a')
            {
                for (int k = 0; k < N0; k++)
                    file >> A[k];
                std::cout << "choice method:\n";
                choice_sort(A, N0);
                for (int k = 0; k < N0; k++)
                    std::cout << A[k] << ' ';
                std::cout << '\n';
            }
            if (choice == 'm' || choice == 'a')
            {
                for (int k = 0; k < N0; k++)
                    file >> A[k];
                std::cout << "merge method:\n";
                merge_sort(A, N0);
                for (int k = 0; k < N0; k++)
                    std::cout << A[k] << ' ';
                std::cout << '\n';
            }
            if (choice == 'h' || choice == 'a')
            {
                for (int k = 0; k < N0; k++)
                    file >> A[k];
                std::cout << "heap method:\n";
                heap_sort(A, N0);
                for (int k = 0; k < N0; k++)
                    std::cout << A[k] << ' ';
            }
        }
        if (choice != 'e') //сохранение отсортированного массива в файл если пользователь не выбрал выйти
        {
            std::ofstream write;
            write.open("array_sorted.txt");
            for (int k = 0; k < N0; k++)
                write << A[k] << '\n';
        }
        return 0;
    }
    else return 1;
}
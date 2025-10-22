#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
const int N0 = 15;
int insertion_sort(int* A, int N)
{
    int Tcount = 0;
    int i, j, t;
    for (i = 0; i < N; i++)
    {
        for (j = i; j > 0 && A[j - 1] > A[j]; j--, Tcount++)
        {
            t = A[j];
            A[j] = A[j - 1];
            A[j - 1] = t;
        }
    }
    return Tcount;
}
int choice_sort(int* A, int N)
{
    int Tcount = 0;
    int i, j, t, min;
    for (i = 0; i < N; i++)
    {
        min = i;
        for (j = i; j < N; j++, Tcount++)
        {
            if (A[j] < A[min]) min = j;
        }
        t = A[min];
        A[min] = A[i];
        A[i] = t;
    }
    return Tcount;
}
int* merge(int* L, int* R, int n, int* TRcount)
{
    int* mergedLR = (int*)malloc(n * sizeof(int));
    for (int k = 0, i = 0, j = 0; k < n; k++)
    {
        *TRcount += 2;
        if (i < n / 2 && j < n / 2 + n % 2)
        {
            *TRcount++;
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
            *TRcount++;
            if (i >= n / 2)
            {
                while (k < n)
                {
                    mergedLR[k] = R[j];
                    j++;
                    k++;
                }
            }
            *TRcount++;
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
int* merge_sort(int* A, int N, int* TRcount)
{
    *TRcount++;
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
    left = merge_sort(left, N / 2, TRcount);
    right = merge_sort(right, N / 2 + N % 2, TRcount);
    int* result = merge(left, right, N, TRcount);
    return result;
}
void heapify(int* A, int root, int size, int* TRcount)
{
    int t;
    int largest = root, left = 2 * root + 1, right = 2 * root + 2;
    *TRcount += 2;
    if (left < size && A[left] > A[largest]) largest = left;
    *TRcount += 2;
    if (right < size && A[right] > A[largest]) largest = right;
    *TRcount++;
    if (largest != root)
    {
        t = A[root];
        A[root] = A[largest];
        A[largest] = t;
        heapify(A, largest, size, TRcount);
    }
}
void heap_sort(int* A, int N, int* TRcount)
{
    int i, t;
    for (i = N / 2 - 1; i >= 0; i--)
    {
        heapify(A, i, N, TRcount);
    }
    for (i = N - 1; i >= 1; i--)
    {
        t = A[0];
        A[0] = A[i];
        A[i] = t;
        heapify(A, 0, i, TRcount);
    }
}
void main()
{
    int A[N0], Tn;
    int* TRn = new int;
    std::ifstream file;
    file.open("array3.txt");
    for (int k = 0; k < N0; k++)
        file >> A[k];
    Tn = insertion_sort(A, N0);
    std::cout << "insertion method:\n";
    for (int k = 0; k < N0; k++)
        std::cout << A[k] << ' ';
    std::cout << "Its T = " << Tn << '\n';
    for (int k = 0; k < N0; k++)
        file >> A[k];
    std::cout << "choice method:\n";
    Tn = choice_sort(A, N0);
    for (int k = 0; k < N0; k++)
        std::cout << A[k] << ' ';
    std::cout << "Its T = " << Tn << '\n';
    for (int k = 0; k < N0; k++)
        file >> A[k];
    std::cout << "heap method:\n";
    *TRn = 0;
    heap_sort(A, N0, TRn);
    for (int k = 0; k < N0; k++)
        std::cout << A[k] << ' ';
    std::cout << "Its T = " << *TRn << '\n';
    for (int k = 0; k < N0; k++)
        file >> A[k];
    std::cout << "merge method:\n";
    *TRn = 0;
    merge_sort(A, N0, TRn);
    for (int k = 0; k < N0; k++)
        std::cout << A[k] << ' ';
    std::cout << "Its T = " << *TRn << '\n';
}
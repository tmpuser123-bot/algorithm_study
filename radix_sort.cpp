#include <iostream>
using namespace std;

#define MAX 10000

void radixSort(int *a, int n) {
    int result[MAX], maxValue = 0;
    int exp = 1;
    for (int i = 0; i < n; i++)
        if (a[i] > maxValue) maxValue = a[i];
    while (maxValue / exp > 0) {
        int bucket[10] = {0};
        for (int i = 0; i < n; i++) bucket[a[i] / exp % 10]++;
        for (int i = 1; i < 10; i++) bucket[i] += bucket[i - 1]; // 계수 정렬이랑 합친거 아니야?

        for (int i = n - 1; i >= 0; i--) {
            result[--bucket[a[i] / exp % 10]] = a[i];
        }

        for (int i = 0; i < n; i++) a[i] = result[i];
        exp *= 10;
    }
}
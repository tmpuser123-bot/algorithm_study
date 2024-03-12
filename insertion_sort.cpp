#include <iostream>
#include <vector>
using namespace std;

void InsertionSort(vector<int> arr) {
    int i, j;
    int key;

    for (i = 1; i < arr.size(); i++) {
        key = arr[i];
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
            }
            else
                break;
        }
        arr[j + 1] = key;
    }
}
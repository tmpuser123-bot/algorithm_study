#include <iostream>
#include <vector>
using namespace std;

#define MAX 10
vector<vector<int>> arr = vector<int>(MAX, vector<int>(MAX, 0));
vector<vector<int>> path = vector<int>(MAX, vector<int>(MAX, 0));

int main(void) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            path[i][j] = i;
        }
    }
    
    for (int k = 0; k < MAX; k++) {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                if (arr[i][j] > arr[i][k] + arr[k][j]) {
                    arr[i][j] = arr[i][k] + arr[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

vector<int> tmp;
void findPath(int from, int to) {
    int prev = path[from][to];
    if (from == prev) {
        tmp.push_back(from);
        return;
    }

    findPath(from, prev);
    findPath(prev, to);
}
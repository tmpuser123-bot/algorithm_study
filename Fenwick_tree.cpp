#include <iostream>
#include <vector>
using namespace std;
/*
    일반 Fenwick Tree 에 Lazy Propagation 기법을 추가한 코드

    펜윅트리
        1. 구간 업데이트, 점 쿼리
        2. 점 업데이트, 구간 쿼리
        3. 구간 업데이트, 구간 쿼리 (해당 방법을 구현한 방법)
*/
const int TREESIZE = 1000001;

class LazyFenwickTree {
public:
    vector<int> degree_tree = vector<int>(TREESIZE);
    vector<int> const_tree = vector<int>(TREESIZE);

    void RangeUpdate(int L, int R, int x) {
        Update(degree_tree, L, x);
        Update(degree_tree, R + 1, -x);

        Update(const_tree, L, (-L + 1) * x);
        Update(const_tree, R + 1, R * x);
    }

    int RangeSum(int L, int R) {
        int ret = Sum(degree_tree, R) * R + Sum(const_tree, R);
        return ret -= Sum(degree_tree, L - 1) * (L - 1) + Sum(const_tree, L - 1);
    }

    int Sum(vector<int> &tree, int idx) {
        int ret = 0;
        while (idx > 0) {
            ret += tree[idx];
            idx &= (idx - 1);
        }
        return ret;
    }

    void Update(vector<int> &tree, int idx, int x) {
        while (idx <= tree.size()) {
            tree[idx] += x;
            idx += (idx & -idx);
        }
    }
};
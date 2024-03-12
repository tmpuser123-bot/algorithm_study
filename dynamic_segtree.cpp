#include <iostream>
#include <vector>
using namespace std;

#define POINTER
typedef long long ll;

#ifdef POINTER
struct Node {
    Node *l, *r;
    ll v;
    Node() {l = r = NULL; v = 0;}    
} *root;

void update(Node *node, int s, int e, int x, int v) {
    if (s == e) {
        node->v = v;
        return;
    }
    int m = (s + e) >> 1;
    if (x <= m) {
        if (!node->l) node->l = new Node();
        update(node->l, s, m, x, v);
    }
    else {
        if (!node->r) node->r = new Node();
        update(node->r, m + 1, e, x, v);
    }
    ll t1 = node->l ? node->l->v : 0;
    ll t2 = node->r ? node->r->v : 0;
    node->v = t1 + t2;
}

int query(Node *node, int s, int e, int l, int r) {
    if (!node) return 0;
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return node->v;
    int m = s + e >> 1;
    return query(node->l, s, m, l, r) + query(node->r, m + 1, e, l, r);
}
#else
struct Node {
    int l, r;
    ll v;
    Node() {l = r = -1; v = 0;}
}
Node nd[4040404]; // nd[0] 이 루트
int pv = 1; // 현재 몇개의 정점을 사용했는지

void update(int node, int s, int e, int x, int v) {
    if (s == e) {
        return tree[node].v = v; return;
    }
    int m = s + e >> 1;
    if (x <= m) {
        if (nd[node].l == -1) nd[node].l = pv++;
        update(nd[node].l, s, m, x, v);
    }
    else {
        if (nd[node].r == -1) nd[node].r = pv++;
        update(nd[node].r, m + 1, e, x, v);
    }
    ll t1 = nd[node].l != -1 ? nd[node].l : 0;
    ll t2 = nd[node].r != -1 ? nd[node].r : 0;
    nd[node].v = t1 + t2;
}

int query(int node, int s, int e, int l, int r) {
    if (node == -1) return 0;
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return nd[node].v;
    int m = s + e >> 1;
    return query(nd[node].l, s, m, l, r) + query(nd[node].r, m + 1, e, l, r);
}
#endif

int main(void) {
  cout << "hello world!" << endl;
}














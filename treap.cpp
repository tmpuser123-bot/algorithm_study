#include <iostream>
#include <vector>
using namespace std;
/*
    랜덤한 가중치와 이진트리의 특징을 이용해서
    BBST 를 만드는 것
*/
typedef int KeyType;

struct Node {
    KeyType key;
    int priority, size;
    Node *right = NULL, *left = NULL;
    Node(const KeyType& _key) : key(_key), priority(rand()), size(1) {}

    void setLeft(Node *newLeft) { left = newLeft; CalcSize(); }
    void setRight(Node *newRight) { right = newRight; CalcSize(); }

    void CalcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

typedef <Node *, Node *> NodePair;

// key 를 기준으로 트리를 분할한다.
// key 보다 작은 트리는 왼쪽으로 큰 트리는 오른쪽으로 붙인다.
NodePair Split(Node *root, KeyType key) {
    if (!root) return {NULL, NULL};
    if (root->key < key) {
        NodePair r_sub = Split(r->right, key); // key 보다 작으므로 현재 root 의 오른쪽 서브트리를 split 하러 간다.
        root->setRight(r_sub.first); // 현재 root 의 오른쪽 서브트리에 key 보다 작은 r->right 의 서브트리를 붙인다.
        return NodePair(root, r_sub.second); // 현재 root 를 왼쪽 서브트리로 key 보다 큰 r->right 의 서브트리를 오른쪽으로 붙인다.
    }
    NodePair l_sub = Split(root->left, key); // key 보다 크므로 현재 root 의 왼쪽 서브트리를 split 한다
    root->setLeft(l_sub.second); // key 보다 큰 값이 root 의 왼쪽에 붙는다. 
    return NodePair(l_sub.first, root); // 현재 root 를 오른쪽 서브트리로 key 보다 작은 r->left 를 서브트리의 왼쪽으로 붙인다.
}

Node *Insert(Node *root, Node *node) {
    if (!root)
        return node;

    // 현재 노드가 위 쪽에 들어가야 한다.
    if (root->priority < node->priority) {
        NodePair splitted = split(root, node->key);
        node->SetLeft(splitted.left); // key 를 기준으로 분할된 트리가 붙어서 온다.
        node->SetRight(splitted.right);
        return node;
    }

    if (root->key > node->key)
        root->SetLeft(Insert(root->left, node));
    else
        root->SetRight(Insert(root->right, node));
    return root;
}
// a의 key 가 b 의 key 보다 작다는 가정하에 
Node *Merge(Node *a, Node *b) {
    if (!a) return b;
    if (!b) return a;
    if (a->priority < b->priority) {
        b->SetLeft(Merge(a, b->left)); // b의 왼쪽 서브트리랑 Merge 해 주고
        return b;
    }
    a->SetRight(a->right, b); // a 의 오른쪽 서브트리랑 Merge 해 준다.
    return a;
}

Node *Erase(Node *root, KeyType key) {
    if (!root) return root;
    if (root->key == key) {
        Node *ret = Merge(root->left, root->right);
        delete root;
        return ret;
    }
    // 이진트리의 특징상 당연한 것
    // key 보다 작은 건 왼쪽 서브트리에 key 보다 큰 건 오른쪽 서브트리에 붙으므로
    // 이렇게 Merge 해 주는 것은 이미 BBST 가 완성되어 있기 때문에? 왼쪽이든 오른쪽이든
    if (key < root->key)
        root->SetLeft(Erase(root->left, key));
    else
        root->SetRight(Erase(root->right, key));
    return root;
}

Node *KthNode(Node *root, int k) {
    int left_size = 0;
    if (root->left != NULL) left_size = root->left->size;
    if (k <= left_size) return KthNode(root->left, k);
    if (k == left_size + 1) return root;
    return KthNode(root->right, k - left_size - 1);
}

int CountLessThan(Node *root, KeyType key) {
    if (!root) return 0;
    if (root->key >= key)
        return CountLessThan(root->left, key);
    int left_size = root->left ? root->left->size : 0;
    return left_size + 1 + CountLessThan(root->right, key);
}

int main() {
    ios_base::sync_with_stdio(0);
    int test_num, arr_size;
    int arr[50000];
    int answer[50000];
    cin >> test_num;

    while (test_num--) {
        cin >> arr_size;
        for (int i = 0; i < arr_size; ++i)
            cin >> arr[i];

        Node *root = NULL;

        for (int i = 1; i <= arr_size; ++i)
            root = Insert(root, new Node(i));

        for (i = arr_size - 1; i >= 0; --i) {
            Node *k = KthNode(root, i + 1 - arr[i]);
            answer[i] = k->key;
            root = Erase(root, k->key);
        }

        for (int i = 0; i < arr_size; ++i)
            cout << answer[i] << ' ';
        cout << '\n';
    }
}






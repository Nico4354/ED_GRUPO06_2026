#include <iostream>
using namespace std;

template <typename Traits>
class CBinaryTree {
public:
    using T = typename Traits::value_type;

    struct Node {
        T data;
        Node* pChild[2];
        Node(const T& v) : data(v) { pChild[0] = pChild[1] = nullptr; }
        T& GetDataRef() { return data; }
    };

private:
    Node* m_pRoot = nullptr;

private:
    // Inserción BST
    Node* internalInsert(Node* node, const T& val) {
        if (!node) return new Node(val);
        if (val < node->data) node->pChild[0] = internalInsert(node->pChild[0], val);
        else if (val > node->data) node->pChild[1] = internalInsert(node->pChild[1], val);
        return node;
    }

    // Búsqueda BST
    bool internalSearch(Node* node, const T& val) const {
        if (!node) return false;
        if (val < node->data) return internalSearch(node->pChild[0], val);
        if (val > node->data) return internalSearch(node->pChild[1], val);
        return true;
    }

    // 7.6 Recorrido inorden con templates variádicos
    template <typename Func, typename... Args>
    void internalInorden(Node* pNode, Func& fn, Args&... args) {
        if (pNode) {
            internalInorden(pNode->pChild[0], fn, args...);
            fn(pNode->GetDataRef(), args...);
            internalInorden(pNode->pChild[1], fn, args...);
        }
    }

    // 7.5 Eliminación
    Node* findMin(Node* node) {
        while (node && node->pChild[0]) node = node->pChild[0];
        return node;
    }

    Node* internalRemove(Node* node, const T& val) {
        if (!node) return nullptr;

        if (val < node->data) {
            node->pChild[0] = internalRemove(node->pChild[0], val);
        } else if (val > node->data) {
            node->pChild[1] = internalRemove(node->pChild[1], val);
        } else {
            if (!node->pChild[0]) {
                Node* tmp = node->pChild[1];
                delete node;
                return tmp;
            }
            if (!node->pChild[1]) {
                Node* tmp = node->pChild[0];
                delete node;
                return tmp;
            }
            Node* succ = findMin(node->pChild[1]);
            node->data = succ->data;
            node->pChild[1] = internalRemove(node->pChild[1], succ->data);
        }
        return node;
    }

    void internalClear(Node* node) {
        if (!node) return;
        internalClear(node->pChild[0]);
        internalClear(node->pChild[1]);
        delete node;
    }

public:
    ~CBinaryTree() { internalClear(m_pRoot); }

    void insert(const T& val) { m_pRoot = internalInsert(m_pRoot, val); }

    bool search(const T& val) const { return internalSearch(m_pRoot, val); }

    // 7.6
    template <typename Func, typename... Args>
    void inorden(Func fn, Args... args) {
        internalInorden(m_pRoot, fn, args...);
    }

    // 7.5
    bool remove(const T& val) {
        if (!search(val)) return false;
        m_pRoot = internalRemove(m_pRoot, val);
        return true;
    }
};

// 7.7 Ejemplo completo
struct IntTraits {
    using value_type = int;
};

void printNode(int val) {
    cout << val << " ";
}

int main() {
    CBinaryTree<IntTraits> tree;

    // Insertar
    tree.insert(70);
    tree.insert(30);
    tree.insert(80);
    tree.insert(0);
    tree.insert(40);
    tree.insert(75);

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- 5.2 Estructura del Nodo ---
template <typename T, int M>
struct BTreeNode {
    T keys[M];                   
    BTreeNode* children[M + 1];  
    int nKeys;                   
    bool isLeaf;                 

    BTreeNode(bool leaf) : nKeys(0), isLeaf(leaf) {
        for (int i = 0; i <= M; i++) children[i] = nullptr;
    }
};

// --- Clase BTree ---
template <typename T, int M>
class BTree {
    BTreeNode<T, M>* root;

public:
    BTree() { root = nullptr; }

    // --- 5.3 Búsqueda ---
    BTreeNode<T, M>* search(BTreeNode<T, M>* node, const T& key) {
        if (!node) return nullptr;
        int i = 0;
        while (i < node->nKeys && key > node->keys[i]) i++;
        if (i < node->nKeys && key == node->keys[i]) return node;
        if (node->isLeaf) return nullptr;
        return search(node->children[i], key);
    }

    // --- 5.4 Inserción y Split ---
    void splitChild(BTreeNode<T, M>* x, int i, BTreeNode<T, M>* y) {
        int t = M / 2;
        BTreeNode<T, M>* z = new BTreeNode<T, M>(y->isLeaf);
        
        // El nuevo nodo z toma las m - t - 1 claves de la derecha
        z->nKeys = M - t - 1;

        for (int j = 0; j < z->nKeys; j++)
            z->keys[j] = y->keys[j + t + 1];

        if (!y->isLeaf) {
            for (int j = 0; j <= z->nKeys; j++)
                z->children[j] = y->children[j + t + 1];
        }

        y->nKeys = t;

        for (int j = x->nKeys; j >= i + 1; j--)
            x->children[j + 1] = x->children[j];

        x->children[i + 1] = z;

        for (int j = x->nKeys - 1; j >= i; j--)
            x->keys[j + 1] = x->keys[j];

        x->keys[i] = y->keys[t];
        x->nKeys++;
    }

    void insertNonFull(BTreeNode<T, M>* x, const T& k) {
        int i = x->nKeys - 1;
        if (x->isLeaf) {
            while (i >= 0 && k < x->keys[i]) {
                x->keys[i + 1] = x->keys[i];
                i--;
            }
            x->keys[i + 1] = k;
            x->nKeys++;
        } else {
            while (i >= 0 && k < x->keys[i]) i--;
            i++;
            if (x->children[i]->nKeys == M) {
                splitChild(x, i, x->children[i]);
                if (k > x->keys[i]) i++;
            }
            insertNonFull(x->children[i], k);
        }
    }

    void insert(const T& k) {
        if (!root) {
            root = new BTreeNode<T, M>(true);
            root->keys[0] = k;
            root->nKeys = 1;
        } else {
            if (root->nKeys == M) {
                BTreeNode<T, M>* s = new BTreeNode<T, M>(false);
                s->children[0] = root;
                splitChild(s, 0, root);
                root = s;
                insertNonFull(s, k);
            } else {
                insertNonFull(root, k);
            }
        }
    }

    void display(BTreeNode<T, M>* node, int level = 0) {
        if (node != nullptr) {
            cout << "Nivel " << level << ": ";
            for (int i = 0; i < node->nKeys; i++) cout << "[" << node->keys[i] << "]";
            cout << endl;
            if (!node->isLeaf) {
                for (int i = 0; i <= node->nKeys; i++) display(node->children[i], level + 1);
            }
        }
    }

    BTreeNode<T, M>* getRoot() { return root; }
};

int main() {
    // Usamos m = 3 para que con 4 elementos (5, 7, C, M) ocurra el Split
    BTree<string, 3> tree;

    cout << "--- Insertando datos de tus apuntes ---" << endl;
    tree.insert("5");
    tree.insert("7");
    tree.insert("C");
    tree.insert("M"); // Provoca el Split

    cout << "\nEstructura del Arbol B resultante:" << endl;
    tree.display(tree.getRoot());

    return 0;
}
#include <iostream>

using namespace std;

// 5.2 Estructura del Nodo 
template <typename T, int M>
struct BTreeNode {
    T keys[M];                   
    BTreeNode* children[M + 1];  
    int nKeys;                   
    bool isLeaf;                 

    BTreeNode(bool leaf = true) : nKeys(0), isLeaf(leaf) {
        for (int i = 0; i <= M; i++) children[i] = nullptr; 
    }

    int findKeyIndex(const T& k) {
        int idx = 0;
        while (idx < nKeys && keys[idx] < k) ++idx;
        return idx;
    }
};

template <typename T, int M>
class BTree {
    BTreeNode<T, M>* root;
    const int minKeys = (M + 1) / 2 - 1; 

public:
    BTree() : root(nullptr) {}

    // --- 5.5 ELIMINACIÓN PRINCIPAL ---
    void remove(const T& k) {
        if (!root) return;
        internalRemove(root, k);

        // 5.7 Ajuste de raíz si queda vacía
        if (root->nKeys == 0) {
            BTreeNode<T, M>* tmp = root;
            if (root->isLeaf) root = nullptr;
            else root = root->children[0];
            delete tmp;
        }
    }

    // Inserción básica para pruebas
    void insert(const T& k) {
        if (!root) {
            root = new BTreeNode<T, M>(true);
            root->keys[0] = k;
            root->nKeys = 1;
        } else if (root->nKeys < M) {
            int i = root->nKeys - 1;
            while (i >= 0 && root->keys[i] > k) {
                root->keys[i + 1] = root->keys[i];
                i--;
            }
            root->keys[i + 1] = k;
            root->nKeys++;
        }
    }

private:
    void internalRemove(BTreeNode<T, M>* node, const T& k) {
        int idx = node->findKeyIndex(k);

        if (idx < node->nKeys && node->keys[idx] == k) {
            if (node->isLeaf) {
                removeFromLeaf(node, idx); 
            } else {
                removeFromNonLeaf(node, idx); 
            }
        } else {
            if (node->isLeaf) return;
            bool isLastChild = (idx == node->nKeys);
            if (node->children[idx]->nKeys < minKeys + 1) fill(node, idx);

            if (isLastChild && idx > node->nKeys)
                internalRemove(node->children[idx - 1], k);
            else
                internalRemove(node->children[idx], k);
        }
    }

    // 5.5 Caso 1: Hoja
    void removeFromLeaf(BTreeNode<T, M>* node, int idx) {
        for (int i = idx + 1; i < node->nKeys; ++i)
            node->keys[i - 1] = node->keys[i];
        node->nKeys--;
    }

    // 5.5 Caso 2: Nodo Interno
    void removeFromNonLeaf(BTreeNode<T, M>* node, int idx) {
        BTreeNode<T, M>* cur = node->children[idx + 1];
        while (!cur->isLeaf) cur = cur->children[0]; 
        
        T succ = cur->keys[0];
        node->keys[idx] = succ; 
        internalRemove(node->children[idx + 1], succ);
    }

    // 5.6 REDISTRIBUCIÓN
    void fill(BTreeNode<T, M>* node, int idx) {
        if (idx != 0 && node->children[idx - 1]->nKeys > minKeys)
            borrowFromPrev(node, idx);
        else if (idx != node->nKeys && node->children[idx + 1]->nKeys > minKeys)
            borrowFromNext(node, idx);
        else {
            if (idx != node->nKeys) merge(node, idx);
            else merge(node, idx - 1);
        }
    }

    void borrowFromPrev(BTreeNode<T, M>* node, int idx) {
        BTreeNode<T, M>* child = node->children[idx];
        BTreeNode<T, M>* sibling = node->children[idx - 1];
        for (int i = child->nKeys - 1; i >= 0; --i) child->keys[i + 1] = child->keys[i];
        if (!child->isLeaf) {
            for (int i = child->nKeys; i >= 0; --i) child->children[i + 1] = child->children[i];
        }
        child->keys[0] = node->keys[idx - 1]; 
        if (!child->isLeaf) child->children[0] = sibling->children[sibling->nKeys];
        node->keys[idx - 1] = sibling->keys[sibling->nKeys - 1]; 
        child->nKeys++; sibling->nKeys--;
    }

    void borrowFromNext(BTreeNode<T, M>* node, int idx) {
        BTreeNode<T, M>* child = node->children[idx];
        BTreeNode<T, M>* sibling = node->children[idx + 1];
        child->keys[child->nKeys] = node->keys[idx];
        if (!child->isLeaf) child->children[child->nKeys + 1] = sibling->children[0];
        node->keys[idx] = sibling->keys[0];
        for (int i = 1; i < sibling->nKeys; ++i) sibling->keys[i - 1] = sibling->keys[i];
        if (!sibling->isLeaf) {
            for (int i = 1; i <= sibling->nKeys; ++i) sibling->children[i - 1] = sibling->children[i];
        }
        child->nKeys++; sibling->nKeys--;
    }

    // 5.7 CONCATENACIÓN
    void merge(BTreeNode<T, M>* node, int idx) {
        BTreeNode<T, M>* child = node->children[idx];
        BTreeNode<T, M>* sibling = node->children[idx + 1];
        child->keys[minKeys] = node->keys[idx]; 
        for (int i = 0; i < sibling->nKeys; ++i) child->keys[i + minKeys + 1] = sibling->keys[i];
        if (!child->isLeaf) {
            for (int i = 0; i <= sibling->nKeys; ++i) child->children[i + minKeys + 1] = sibling->children[i];
        }
        for (int i = idx + 1; i < node->nKeys; ++i) node->keys[i - 1] = node->keys[i];
        for (int i = idx + 2; i <= node->nKeys; ++i) node->children[i - 1] = node->children[i];
        child->nKeys += sibling->nKeys + 1;
        node->nKeys--;
        delete sibling;
    }
};

int main() {
    BTree<int, 3> t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    
    cout << "Eliminando 20..." << endl;
    t.remove(20);
    
    cout << "Finalizado correctamente." << endl;
    return 0;
}

#include <iostream>
using namespace std;

template <typename T>
struct BSTNode {
	T data;
	BSTNode* pChild[2]; // [0]=izquierda, [1]=derecha

	BSTNode(const T& val)
		: data(val) {
		pChild[0] = pChild[1] = nullptr;
	}

	T& GetDataRef() {
		return data;
	}
};

template <typename Traits>
class CBinaryTree {
	using T = typename Traits::value_type;
	using Node = BSTNode<T>;

	Node* m_pRoot;

	// MC)todos internos recursivos (privados)
	Node* internalInsert(Node* node, const T& val);
	Node* internalRemove(Node* node, const T& val);
	Node* internalSearch(Node* node, const T& val);
	Node* findMin(Node* node);

	template <typename Func, typename ...Args>
	void internalInorden(Node* pNode, Func fn, Args... args);

public:
	CBinaryTree() : m_pRoot(nullptr) {}
	void insert(const T& val);
	bool remove(const T& val);
	bool search(const T& val);

	template <typename Func, typename ...Args>
	void inorden(Func fn, Args... args);
};

template <typename Traits>
auto CBinaryTree<Traits>::internalInsert(Node* node, const T& val)
-> Node* {
	if (!node) return new Node(val);

	if (val < node->data)
		node->pChild[0] = internalInsert(node->pChild[0], val);
	else if (val > node->data)
		node->pChild[1] = internalInsert(node->pChild[1], val);
	// si val == node->data, no se inserta (sin duplicados)

	return node;
}

template <typename Traits>
void CBinaryTree<Traits>::insert(const T& val) {
	m_pRoot = internalInsert(m_pRoot, val);
}
template <typename Traits>
auto CBinaryTree<Traits>::internalSearch(Node* node, const T& val)
-> Node* {
	if (!node) return nullptr;
	if (val == node->data) return node;
	if (val < node->data)
		return internalSearch(node->pChild[0], val);
	return internalSearch(node->pChild[1], val);
}

template <typename Traits>
bool CBinaryTree<Traits>::search(const T& val) {
	return internalSearch(m_pRoot, val) != nullptr;
}
// Definir traits para int
struct IntTraits {
	using value_type = int;
};

// FunciC3n para imprimir
void printNode(int& val) {
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
	tree.insert(90);
	// BC:squeda
	cout << "Buscamos 40: ";
	cout << (tree.search(40) ? "Encontrado!" : "No Encontrado!") << "\n";
	cout << "Buscamos 99: ";
	cout << (tree.search(99) ? "Encontrado!" : "No Encontrado!") << "\n";

	return 0;
}

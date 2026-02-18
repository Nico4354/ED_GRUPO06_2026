#include <iostream>
using namespace std;

/* =========================
   FUNCIONES OBJETO
   ========================= */

// f1: incrementa en 1
template <typename T>
void f1(T &n) {
    n++;
}

// f2: incrementa en p1
template <typename T>
void f2(T &n, int p1) {
    n += p1;
}

// f3: operación con múltiples argumentos
template <typename T>
void f3(T &n, int a, int b, int c, int d) {
    n = n * a + b - c + d;
}


/* =========================
   CLASE CArray
   ========================= */

template <typename T>
class CArray {
    T* m_data;
    int m_size;
    int m_capacity;

public:
    using value_type = T;

    // Constructor
    CArray() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    ~CArray() {
        delete[] m_data;
    }

    // Iteradores
    T* begin() { return m_data; }
    T* end()   { return m_data + m_size; }

    // Insertar elemento
    void push_back(const T& val) {
        if (m_size == m_capacity) {
            int newCap = (m_capacity == 0) ? 4 : m_capacity * 2;

            T* tmp = new T[newCap];

            for (int i = 0; i < m_size; i++)
                tmp[i] = m_data[i];

            delete[] m_data;
            m_data = tmp;
            m_capacity = newCap;
        }

        m_data[m_size++] = val;
    }

    // Búsqueda
    int search(const T& val) const {
        for (int i = 0; i < m_size; i++)
            if (m_data[i] == val)
                return i;
        return -1;
    }

    // Eliminar por índice
    void removeAt(int idx) {
        if (idx < 0 || idx >= m_size) return;

        for (int i = idx; i < m_size - 1; i++)
            m_data[i] = m_data[i + 1];

        m_size--;
    }

    // Eliminar por valor
    bool removeByValue(const T& val) {
        int idx = search(val);
        if (idx == -1) return false;

        removeAt(idx);
        return true;
    }

    int size() const { return m_size; }

    // Mostrar contenido (para pruebas)
    void print() const {
        for (int i = 0; i < m_size; i++)
            cout << m_data[i] << " ";
        cout << endl;
    }

    // ========= FOREACH VARIÁDICO =========
    template <typename ObjFunc, typename... Args>
    void Foreach(ObjFunc fn, Args... args) {
        for (auto iter = begin(); iter != end(); ++iter)
            fn(*iter, args...);
    }
};


/* =========================
   FOREACH COMO FUNCIÓN LIBRE
   ========================= */

// Nivel contenedor
template <typename Container, typename FuncObj, typename... Args>
void ForEach(Container &cont, FuncObj fn, Args... args) {
    for (auto iter = cont.begin(); iter != cont.end(); ++iter)
        fn(*iter, args...);
}

// Nivel iteradores
template <typename Iterator, typename FuncObj, typename... Args>
void ForEach(Iterator begin, Iterator end,
             FuncObj fn, Args... args) {
    for (; begin != end; ++begin)
        fn(*begin, args...);
}


/* =========================
   MAIN DE PRUEBA
   ========================= */

int main() {

    CArray<int> arr;

    arr.push_back(7);
    arr.push_back(4);
    arr.push_back(9);
    arr.push_back(2);
    arr.push_back(5);

    cout << "Inicial: ";
    arr.print();

    // Caso 1
    arr.Foreach(f1<int>);
    cout << "Despues f1 (+1): ";
    arr.print();

    // Caso 2
    arr.Foreach(f2<int>, 5);
    cout << "Despues f2 (+5): ";
    arr.print();

    // Caso 3
    arr.Foreach(f3<int>, 7, 4, 8, 14);
    cout << "Despues f3: ";
    arr.print();

    // Probando ForEach libre
    ForEach(arr, f1<int>);
    cout << "ForEach libre (+1): ";
    arr.print();

    return 0;
}

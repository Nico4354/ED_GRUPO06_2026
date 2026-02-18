#include <iostream>
#include <stdexcept>

using namespace std;


template <typename T>
class Array {
protected:
    T* m_data;      
    int m_size;     
    int m_cap;      

public:
    Array() : m_data(nullptr), m_size(0), m_cap(0) {}

    virtual ~Array() {
        if (m_data) delete[] m_data;
    }

    void resize(int newCap) {
        T* tmp = new T[newCap];
        for (int i = 0; i < m_size; i++) {
            tmp[i] = m_data[i];
        }
        if (m_data) delete[] m_data;
        m_data = tmp;
        m_cap = newCap;
    }

    T& operator[](int i) {
        if (i < 0 || i >= m_size) {
            throw std::out_of_range("Indice fuera de rango");
        }
        return m_data[i]; 
    }

    int size() const { return m_size; }
    
    bool empty() const { return m_size == 0; }
};

template <typename T>
class Stack : public Array<T> {
public:
    void push(const T& val) {
        if (this->m_size == this->m_cap) {
            this->resize(this->m_cap == 0 ? 4 : this->m_cap * 2);
        }
        this->m_data[this->m_size++] = val;
    }

    T pop() {
        if (this->empty()) {
            throw std::underflow_error("Pila vacia");
        }
        return this->m_data[--this->m_size];
    }

    int search(const T& val) const {
        for (int i = this->m_size - 1; i >= 0; i--) {
            if (this->m_data[i] == val) {
                return (this->m_size - 1 - i);
            }
        }
        return -1;
    }

    T& top() {
        if (this->empty()) {
            throw std::underflow_error("Pila vacia");
        }
        return this->m_data[this->m_size - 1];
    }

    bool removeVal(const T& val) {
        for (int i = this->m_size - 1; i >= 0; i--) {
            if (this->m_data[i] == val) {
                for (int j = i; j < this->m_size - 1; j++) {
                    this->m_data[j] = this->m_data[j + 1];
                }
                this->m_size--;
                return true;
            }
        }
        return false;
    }
};

template <typename T>
void printStack(Stack<T>& p, string msg) {
    cout << "--- " << msg << " ---" << endl;
    if (p.empty()) {
        cout << "(Vacia)" << endl;
    } else {
        cout << "Tope -> " << p.top() << endl;
        cout << "Size: " << p.size() << endl;
    }
    cout << endl;
}

int main() {
    try {
        cout << "=== PRUEBA DE PILA===" << endl << endl;

        Stack<int> s;
        
        cout << "[Push] 10, 20, 30..." << endl;
        s.push(10);
        s.push(20);
        s.push(30);
        printStack(s, "Inicio");

        cout << "[Top] " << s.top() << endl; 

        cout << "[Pop] Eliminando..." << endl;
        cout << " Eliminado: " << s.pop() << endl;
        printStack(s, "Despues de Pop");

        cout << "[Remove] Valor 10..." << endl;
        if(s.removeVal(10)) cout << " OK." << endl;
        printStack(s, "Final");

    } catch (const exception& e) {
        cout << "ERROR: " << e.what() << endl;
    }

    cout << "\nPresiona Enter para salir...";
    cin.get();
    return 0;
}
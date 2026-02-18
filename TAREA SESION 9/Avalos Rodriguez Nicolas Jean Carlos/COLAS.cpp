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

    int size() const { return m_size; }
    int capacity() const { return m_cap; }
};


template <typename T>
class Queue : public Array<T> {
private:
    int m_front; 
    int m_rear;  
    int m_count; 

public:
    Queue() : m_front(0), m_rear(-1), m_count(0) {
        this->resize(8); 
    }

    void enqueue(const T& val) {
        if (m_count == this->m_cap) {
            int newCap = this->m_cap * 2;
            T* tmp = new T[newCap];
            
            for (int i = 0; i < m_count; i++) {
                tmp[i] = this->m_data[(m_front + i) % this->m_cap];
            }
            
            delete[] this->m_data;
            this->m_data = tmp;
            this->m_cap = newCap;
            
            m_front = 0;
            m_rear = m_count - 1;
        }

        m_rear = (m_rear + 1) % this->m_cap;
        this->m_data[m_rear] = val;
        m_count++;
    }

    T dequeue() {
        if (m_count == 0) throw std::underflow_error("Cola vacia");
        
        T val = this->m_data[m_front];
        m_front = (m_front + 1) % this->m_cap;
        m_count--;
        return val;
    }

    T& front() {
        if (m_count == 0) throw std::underflow_error("Cola vacia");
        return this->m_data[m_front];
    }

    T& back() {
        if (m_count == 0) throw std::underflow_error("Cola vacia");
        return this->m_data[m_rear];
    }

    bool empty() const { return m_count == 0; }
    int count() const { return m_count; }

    int search(const T& val) const {
        for (int i = 0; i < m_count; i++) {
            int idx = (m_front + i) % this->m_cap;
            if (this->m_data[idx] == val) return i; 
        }
        return -1;
    }

    bool removeByValue(const T& val) {
        int pos = search(val);
        if (pos == -1) return false;
        return removeByIndex(pos);
    }

    bool removeByIndex(int idx) {
        if (idx < 0 || idx >= m_count) return false;

        for (int i = idx; i < m_count - 1; i++) {
            int cur = (m_front + i) % this->m_cap;
            int nxt = (m_front + i + 1) % this->m_cap;
            this->m_data[cur] = this->m_data[nxt];
        }

        m_rear = (m_rear - 1 + this->m_cap) % this->m_cap;
        m_count--;
        return true;
    }
};

template <typename T>
void printQueue(Queue<T>& q, string msg) {
    cout << "--- " << msg << " ---" << endl;
    if (q.empty()) {
        cout << "(Cola vacia)" << endl;
    } else {
        cout << "Frente -> " << q.front() << endl;
        cout << "Final  -> " << q.back() << endl;
        cout << "Count: " << q.count() << endl;
    }
    cout << endl;
}

int main() {
    try {
        cout << "=== DEMO COLA CIRCULAR (QUEUE) ===" << endl << endl;

        Queue<int> q;
        
        cout << "[Enqueue] 10, 20, 30..." << endl;
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);
        printQueue(q, "Inicio");

        cout << "[Front] " << q.front() << endl; 
        cout << "[Search] 20 esta en pos relativa: " << q.search(20) << endl;
        cout << endl;

        cout << "[Dequeue] Sale el primero..." << endl;
        cout << " Salio: " << q.dequeue() << endl; 
        printQueue(q, "Despues de Dequeue");

        cout << "[Remove] Eliminando valor 30..." << endl;
        if(q.removeByValue(30)) cout << " Eliminado OK." << endl;
        printQueue(q, "Final");

    } catch (const exception& e) {
        cout << "ERROR: " << e.what() << endl;
    }

    cout << "\nPresiona Enter para salir...";
    cin.get();
    return 0;
}
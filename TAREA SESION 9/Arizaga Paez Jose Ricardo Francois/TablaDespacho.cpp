#include <iostream>
using namespace std;

// 3.4 Arreglo de Punteros a Métodos
class A {
public:
    int x, y;
    int ope1(int w) { return x + w; }
    int ope2(int w) { return y * w; } 
};

int main() {    
    int (A::*xvpm[2])(int) = { &A::ope1, &A::ope2 };

    A obj;
    obj.x = 10; 
    obj.y = 5;

    for (int i = 0; i < 2; i++) {
        cout << "Resultado funcion " << i << ": " << (obj.*xvpm[i])(3) << endl;
    }

    return 0;
}
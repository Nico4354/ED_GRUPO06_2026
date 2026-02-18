#include <iostream>
using namespace std;

// 3.1 Declaración de la Clase Base
class A {
public:
    int x, y;

    int ope1(int w) { 
        return x + w; 
    }

    int ope2(int w) { 
        return y * w; 
    }
};
//Demo
int main() {
    A objeto;
    objeto.x = 5;
    objeto.y = 10;
    
    cout << "x: " << objeto.x << ", y: " << objeto.y << endl;
    cout << "ope1(2): " << objeto.ope1(2) << endl;
    
    return 0;
}
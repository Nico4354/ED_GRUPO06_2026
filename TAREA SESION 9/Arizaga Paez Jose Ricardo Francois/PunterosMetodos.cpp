#include <iostream>
using namespace std;

// 3.3 Punteros a Métodos
class A {
public:
    int x, y;
    int ope1(int w) { return x + w; }
    int ope2(int w) { return y * w; }
};

int main() {

    int (A::*pMet)(int) = &A::ope1;

    A obj;
    obj.x = 10; 
    int r = (obj.*pMet)(7);      
    cout << "Resultado con objeto (10 + 7): " << r << endl;

    A *pObj = new A();
    pObj->x = 20;
    r = (pObj->*pMet)(5);      
    cout << "Resultado con puntero (20 + 5): " << r << endl;

    delete pObj;
    return 0;
}
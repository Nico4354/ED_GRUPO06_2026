#include <iostream>
using namespace std;

// 3.2 Punteros a Atributos
class A {
public:
    int x, y;
    int ope1(int w) { return x + w; }
    int ope2(int w) { return y * w; }
};

int main() {
    int A::*pAtt = &A::x; 

    A obj;
    obj.*pAtt = 42;         
    cout << "Valor de obj.x usando puntero: " << obj.x << endl;

    A *pObj = new A();
    pObj->*pAtt = 99;      
    cout << "Valor de pObj->x usando puntero: " << pObj->x << endl;

    delete pObj; 
    return 0;
}
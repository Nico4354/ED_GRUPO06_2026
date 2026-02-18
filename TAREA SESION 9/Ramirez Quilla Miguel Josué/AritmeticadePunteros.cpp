#include <iostream>
using namespace std;

int main() {

    cout << "===== 4.1 Equivalencia Puntero-Arreglo =====\n";

    int a[10] = {0};
    int *p = nullptr;

    p = a;   // equivalente a p = &a[0];

    cout << "Direccion base a: " << a << endl;
    cout << "Direccion p:      " << p << endl;
    cout << "a[7] == *(a+7) == *(p+7)\n";

    cout << "\n===== 4.2 Cuatro Notaciones Equivalentes =====\n";

    p[7] = 13;
    *(p + 7) = 13;
    *(7 + p) = 13;
    7[p] = 13;

    cout << "Valor en a[7]: " << a[7] << endl;

    cout << "\n===== 4.3 Indices Negativos =====\n";

    p = a + 5;   // ahora apunta a a[5]

    p[-2] = 9;
    *(p - 2) = 9;
    *(-2 + p) = 9;
    (-2)[p] = 9;

    cout << "Valor en a[3]: " << a[3] << endl;

    cout << "\n===== 4.4 Esquema de Memoria =====\n";

    for(int i = 0; i < 10; i++) {
        cout << "a[" << i << "] -> "
             << "Direccion: " << (a + i)
             << " Valor: " << a[i] << endl;
    }

    cout << "\nSi p = a + 5\n";
    cout << "p apunta a direccion: " << p << endl;
    cout << "p[-2] direccion: " << (p - 2) << endl;
    cout << "p[2]  direccion: " << (p + 2) << endl;

    cout << "\n===== 4.5 Punteros a Cadenas =====\n";

    char str[] = "UNXSM";   // arreglo modificable
    char *pStr = str;
    char *p2 = pStr + 3;

    cout << "Cadena original: " << str << endl;

    *(p2 - 1) = 'X';   // modifica str[2]
    p2[-1] = 'X';      // equivalente
    (-1)[p2] = 'X';      // equivalente

    cout << "Cadena modificada: " << str << endl;

    return 0;
}

#include <iostream>
using namespace std;

void numero_primo_recursivo(int n, int divisor = 2) {
    if (n < 2) {
        cout << n << " no es un numero primo." << "\n";
        return;
    }
    if (divisor * divisor > n) {
        cout << n << " es un numero primo." << "\n";
        return;
    }
    if (n % divisor == 0) {
        cout << n << " no es un numero primo." << "\n";
        return;
    }
    numero_primo_recursivo(n, divisor + 1);
}

int main(){
    int n;
    
    cout << "Ingrese un numero entero positivo: "; cin >> n;
    numero_primo_recursivo(n);
    return 0;
}
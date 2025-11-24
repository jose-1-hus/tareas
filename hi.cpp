#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

void mostrar_fibonacci_hasta(int n) {
    for (int i = 0; i < n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << "\n";
}

int main() {
    int n;
    cout << "Ingrese un numero entero positivo: "; cin >> n;
    cout << "Serie de Fibonacci hasta el termino " << n << ":\n";
    mostrar_fibonacci_hasta(n);
    return 0;
}
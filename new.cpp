#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int A[50];    // Vector de tamaño 50
    int n;        // Tamaño que usaremos del vector
    int x;        // Número que vamos a buscar
    int veces = 0;  // Contador de veces que aparece el número

    // Para generar números aleatorios diferentes cada vez
    srand(time(0));

    // Pedimos el tamaño del vector
    cout << "Ingrese el tamaño del vector (máximo 50): ";
    cin >> n;

    // Verificamos que el tamaño sea válido
    if (n <= 0 || n > 50) {
        cout << "Error: el tamaño debe ser entre 1 y 50" << endl;
        return 1;  // Terminamos el programa si el tamaño no es válido
    }

    // Pedimos el número a buscar
    cout << "Ingrese el número que quiere encontrar (1-10): ";
    cin >> x;

    // Llenamos el vector con números aleatorios y los mostramos
    cout << "\nVector generado:\n";
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 10 + 1;  // Números aleatorios del 1 al 10
        cout << A[i] << "\t";
    }
    cout << "\n";

    // Contamos cuántas veces aparece el número
    for (int i = 0; i < n; i++) {
        if (A[i] == x) {
            veces++;
        }
    }

    // Mostramos el resultado
    cout << "\n";
    if (veces > 0) {
        cout << "Tu número " << x << " se encuentra " << veces << " veces en el vector\n";
    } else {
        cout << "Tu número " << x << " no se encuentra en el vector\n";
    }

    return 0;
}
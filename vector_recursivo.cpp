#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void llenado_recursivo(int* vector, int tamaño, int indice = 0) {

    if (indice >= tamaño) {
        return; 
    }
    vector[indice] = rand() % 100 + 1;
    llenado_recursivo(vector, tamaño, indice + 1); 
}
int main() {

    srand(time(0)); 
    int tamaño;
    cout << "Ingrese el grande del vector: ";
    cin >> tamaño;
    int* vector = new int[tamaño];

    llenado_recursivo(vector, tamaño);

    cout << "Vector llenado";
    cout << "\n";

    for (int i = 0; i < tamaño; i++) {
        cout << vector[i];
        cout << "\t";
    }

    return 0;
}
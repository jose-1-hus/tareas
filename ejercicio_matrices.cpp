#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void suma_de_la_diagonal_P(int A[50][50], int n, int &s){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                s = s + A[i][j];
            }
        }
    }
}

void suma_de_la_diagonal_S(int A[50][50], int n, int &z){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j == n - 1 - i){
                z = z + A[i][j];
            }
        }
    }
}


int main(){
    int A[50][50];
    int n;
    int s = 0;
    int z = 0;
    srand(time(0));

    cout << "ingrese el grande de la matriz cuadrada: "; cin >> n;
    cout << "matriz A" << "\n\n";

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            A[i][j] = rand() % 10 + 1;
            cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
    suma_de_la_diagonal_P(A, n, s);
    suma_de_la_diagonal_S(A, n, z);
    cout << "\n";
    cout << "la suma de las diagonales principal es: " << s << "\n";
    cout << "\n";
    cout << "suma de la diagonal secundaria es: " << z << "\n";
    return 0;


}
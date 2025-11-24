#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void diagonal_de_A (int A[50][50], int f_a, int c_a, int C[50][50]){

    for (int i = 0; i < f_a; i++){
        for (int j = 0; j < c_a; j++){
            if (i == j){
                C[i][j] = A[i][j];
            }
            else {
                C[i][j] = 0;
            }
        }
    }
} 





int main (){
   int A[50][50];
   int B[50][50];
   int C[50][50];
   int f_a, c_a;
   int f_b, c_b;

   srand(time(0));

    cout << "ingrese el numero de filas de la matriz A: "; cin >> f_a;
    cout << "ingrese el numero de columnas de la matriz A: "; cin >> c_a;
    cout << "ingrese el numero de filas de la matriz B: "; cin >> f_b;
    cout << "ingrese el numero de columnas de la matriz B: "; cin >> c_b;
    cout << "\n";
    cout << "matriz A" << "\n";

    for (int i = 0; i < f_a; i++){
        for (int j = 0; j < c_a; j++){

            A[i][j] = rand() % 10 + 1;
            cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "matriz B" << "\n";

    for (int i = 0; i < f_b; i++){
        for (int j = 0; j < c_b; j++){

            B[i][j] = rand() % 10 + 1;
            cout << B[i][j] << "\t";
        }
        cout << "\n";
    }
    diagonal_de_A(A, f_a, c_a, C);
    cout << "matriz C" << "\n";

    for (int i = 0; i < f_a; i++){
        for (int j = 0; j < c_a; j++){

            cout << C[i][j] << "\t";
        }
        cout << "\n";
    }

        return 0;


}

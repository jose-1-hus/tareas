#include <iostream>
using namespace std;

void llenarEspiral(int n, int m) {
    int matriz[50][50];
    int a = 0, z = n - 1;
    int b = 0, x = m - 1;
    int num = 1;

    while (a <= z && b <= x) {

        for (int j = b; j <= x; j++) {
            matriz[a][j] = num++;
        }
        a++;

        for (int i = a; i <= z; i++) {
            matriz[i][x] = num++;
        }
        x--;

        if (a <= z) {
            for (int j = x; j >= b; j--) {
                matriz[z][j] = num++;
            }
            z--; 
        }
        if (b <= x) {
            for (int i = z; i >= a; i--) {
                matriz[i][b] = num++;
            }
            b++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}
int main() {
    int n, m;
    cout << "Digite filas: ";
    cin >> n;
    cout << "Digite columnas: ";
    cin >> m;

    llenarEspiral(n, m);

    return 0;
}
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

struct movimiento {
    string codigo_articulo;
    string tipo_movimiento; 
    int cantidad;
    string fecha_hora;
};

struct Articulo {
    string codigo;
    string nombre;
    int cantidad_minima;
    int cantidad_maxima;
    int stock;
    movimiento movimientos[100];  // Reducido de 1000 a 100
    int cantidad_de_movimientos;
};
string obtener_fecha_hora_actual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

bool codigo_existe(Articulo inventario[], int cantidad_de_articulos, string codigo_a_buscar){

    for (int i = 0; i < cantidad_de_articulos; i++) {
        if (inventario[i].codigo == codigo_a_buscar) {
            return true;
        }
    }
    return false;
}

void crear_articulo(Articulo inventario[], int &cantidad_de_articulos){
    string codigo_nuevo;

    while (true)
    {
        cout << "articulo numero " << cantidad_de_articulos + 1 << "\n";
        cout << "Ingrese el codigo del nuevo articulo: "; cin >> codigo_nuevo;
        if (codigo_existe(inventario, cantidad_de_articulos, codigo_nuevo)){
            cout << "El codigo ya existe. Ingrese un codigo diferente." << "\n";
        }
        else{
            break;
        }
    }
    Articulo nuevo_articulo;
    nuevo_articulo.codigo = codigo_nuevo;

    cout << "Ingrese el nombre del articulo: "; cin >> nuevo_articulo.nombre;

    while (true)
    {
        cout << "Ingrese la cantidad minima: "; cin >> nuevo_articulo.cantidad_minima;
        cout << "Ingrese la cantidad maxima: "; cin >> nuevo_articulo.cantidad_maxima;

        if (nuevo_articulo.cantidad_minima > nuevo_articulo.cantidad_maxima){
            cout << "La cantidad minima no puede ser mayor que la cantidad maxima. Intente de nuevo." << "\n";
        }
        else if (nuevo_articulo.cantidad_minima < 0){
            cout << "La cantidad minima no puede ser negativa. Intente de nuevo." << "\n";
        }
        else if (nuevo_articulo.cantidad_maxima < 0){
            cout << "La cantidad maxima no puede ser negativa. Intente de nuevo." << "\n";
        }
        else{
            break;
        }
    }
    nuevo_articulo.stock = 0;
    nuevo_articulo.cantidad_de_movimientos = 0;

    inventario[cantidad_de_articulos] = nuevo_articulo;
    cantidad_de_articulos++;

    cout << "Articulo creado exitosamente." << "\n";
}

void registro_de_entrada(Articulo &articulo, int cantidad){
    if (articulo.cantidad_de_movimientos >= 100) {
        cout << "No se pueden registrar más movimientos para este artículo." << "\n";
        return;
    }
    movimiento nuevo_movimiento;
    nuevo_movimiento.codigo_articulo = articulo.codigo;
    nuevo_movimiento.tipo_movimiento = "entrada";
    nuevo_movimiento.cantidad = cantidad;
    nuevo_movimiento.fecha_hora = obtener_fecha_hora_actual();

    articulo.movimientos[articulo.cantidad_de_movimientos] = nuevo_movimiento;
    articulo.cantidad_de_movimientos++;
}

int main(){
    cout << "PRUEBA: Programa iniciado" << endl;
    
    Articulo inventario[50];  // Reducido para evitar stack overflow
    cout << "PRUEBA: Array creado" << endl;
    
    int cantidad_de_articulos = 0;
    int opcion;
    int x;

    cout << " ===== Menu inventario ===== " << "\n";
    cout << " 1. Crear articulo " << "\n";
    cout << " 2. Entrada de articulos " << "\n";
    cout << " 3. Salida de articulos " << "\n";
    cout << " 4. Borrar un articulo " << "\n";
    cout << " 5. Editar/Consultar articulo " << "\n";
    cout << " 6. Mostrar listado de articulos " << "\n";
    cout << " 7. Mostrar registro de entradas " << "\n";
    cout << " 8. Mostrar registro de salidas " << "\n";
    cout << " 9. Salir " << "\n";
    cout << " ========================= " << "\n" << flush;

    cout << "PRUEBA: Menu mostrado, entrando al while..." << endl;

    while (true) {
        cout << "\n Ingrese el numero de la opcion: ";
        cin >> opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Ingrese un numero." << "\n";
            continue;
        }
        switch (opcion) {
            case 1:
                cout << "Crear articulo." << "\n";
                cout << "cuantos articulos quieres crear?: ";
                cin >> x;
                for (int i = 0; i < x; i++){
                    crear_articulo(inventario, cantidad_de_articulos);
                }
            
                break;
            case 2:
                cout << "Entrada de articulos seleccionado." << "\n";
                break;
            case 3:
                cout << "Salida de articulos seleccionado." << "\n";
                break;
            case 4:
                cout << "Borrar un articulo seleccionado." << "\n";
                break;
            case 5:
                cout << "Editar/Consultar articulo seleccionado." << "\n";
                break;
            case 6:
                cout << "Mostrar listado de articulos seleccionado." << "\n";
                break;
            case 7:
                cout << "Mostrar registro de entradas seleccionado." << "\n";
                break;
            case 8:
                cout << "Mostrar registro de salidas seleccionado." << "\n";
                break;
            case 9:
                cout << "Saliendo del programa." << "\n";
                return 0;
            default:
                cout << "Opcion no valida. Por favor intente de nuevo." << "\n";
        }
    }
    return 0;
}  
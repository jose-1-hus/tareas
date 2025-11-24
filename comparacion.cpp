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
    movimiento entrada[50];
    int cantidad_de_entrada;
    movimiento salida[50];
    int cantidad_de_salida;

};

int leer_opcion_menu(){
    string opcion;

    while (true){
        cout << " ingrese el numero de la opcion: ";
        getline(cin, opcion);
        if (opcion.length() != 1){
            cout << "Entrada invalida. Ingrese un numero." << "\n";
            cout << "\n";
            continue;
        }
        char opcion_char = opcion[0];

        if (opcion_char < '1' || opcion_char > '9'){
            cout << "Entrada invalida. Ingrese un numero." << "\n";
            continue;
        }
        else{
            return opcion_char - '0';
        }
    }
}

int verificacion_de_digitos(){
    string cantidades;

    while (true){

        getline(cin, cantidades);

        if (cantidades.empty()) {
            cout << "Entrada invalida. Ingrese un numero." << "\n";
            continue;
        }

        if(cantidades[0] == '-'){
            cout << "Entrada invalida. Ingrese un numero." << "\n";
            continue;
        }


        
    }
}

string obtener_fecha_hora_actual() {
    time_t now = time(0);
    tm *t = localtime(&now);
    char buffer[200];
    strftime(buffer, 200, "%Y-%m-%d %H:%M:%S", t);
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

    while (true){
        cout << "Ingrese la cantidad minima: "; cin >> nuevo_articulo.cantidad_minima;


        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Intente de nuevo." << "\n";
            continue;
        }
        else if (nuevo_articulo.cantidad_minima < 0){
            cout << "La cantidad minima no puede ser negativa. Intente de nuevo." << "\n";
            continue;
        }

        while(true){
            cout << "Ingrese la cantidad maxima: "; cin >> nuevo_articulo.cantidad_maxima;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Entrada invalida. Intente de nuevo." << "\n";
                continue;
            }
            else if (nuevo_articulo.cantidad_maxima < 0){
                cout << "La cantidad maxima no puede ser negativa. Intente de nuevo." << "\n";
                continue;
            }
            break;
        }

        if (nuevo_articulo.cantidad_minima > nuevo_articulo.cantidad_maxima){
            cout << "La cantidad minima no puede ser mayor que la cantidad maxima. Intente de nuevo." << "\n";
        }

        else{
            break;
        }
    }
    cout << "quiere agregar stock inicial? (s/n): ";
    char respuesta;
    cin >> respuesta;
    cin.ignore(10000, '\n');
    if (respuesta == 's' || respuesta == 'S'){
        while (true){
            cout << "Ingrese la cantidad de stock inicial: "; 
            int stock_inicial;
            cin >> stock_inicial;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Entrada invalida. Intente de nuevo." << "\n";
                continue;
            }

            if (stock_inicial < 0){
                cout << "El stock inicial no puede ser negativo. Intente de nuevo." << "\n";
            }
            else if (stock_inicial > nuevo_articulo.cantidad_maxima){
                cout << "El stock inicial no puede exceder la cantidad maxima. Intente de nuevo." << "\n";
            }
            else if (stock_inicial < nuevo_articulo.cantidad_minima){
                cout << "El stock inicial no puede ser menor que la cantidad minima. Intente de nuevo." << "\n";
            }
            else if (stock_inicial == 0){
                nuevo_articulo.stock = 0;
                break;
            }
            else{
                nuevo_articulo.stock = stock_inicial;
                if (nuevo_articulo.stock > 0){
                    movimiento nueva_entrada;
                    nueva_entrada.codigo_articulo = nuevo_articulo.codigo;
                    nueva_entrada.tipo_movimiento = "entrada";
                    nueva_entrada.cantidad = stock_inicial;
                    nueva_entrada.fecha_hora = obtener_fecha_hora_actual();

                    nuevo_articulo.entrada[0] = nueva_entrada;
                    nuevo_articulo.cantidad_de_entrada = 1;
                break;
                }
            }
        }
    }
    else{
        nuevo_articulo.stock = 0;
    }

    inventario[cantidad_de_articulos] = nuevo_articulo;
    cantidad_de_articulos++;

    cout << "Articulo creado exitosamente." << "\n\n";
}

void entrada_de_articulos(Articulo inventario[], int cantidad_de_articulos){
    string codigo_a_buscar;
    int intentos = 0;

    while (true){
        cout << "ingrese el codigo del articulo para entrada: "; cin >> codigo_a_buscar;

        if (!codigo_existe(inventario, cantidad_de_articulos, codigo_a_buscar)){
            cout << "El codigo no existe. Ingrese un codigo valido." << "\n";
            intentos++;
        }
        if (intentos == 3){
            cout << "Chequee su lista de articulos" << "\n";
            return;
        }
        else{
            break;
        }

    }

    for (int i = 0; i < cantidad_de_articulos; i++){

        if (inventario[i].codigo == codigo_a_buscar){

            int cantidad_a_entrar = 0;

            while(true){
                cout << "Stock actual: " << inventario[i].stock << "\n";
                cout << "Cantidad maxima: " << inventario[i].cantidad_maxima << "\n";
                cout << "Cantidad minima: " << inventario[i].cantidad_minima << "\n";
                cout << "cantidad disponible para ingresar: " << inventario[i].cantidad_maxima - inventario[i].stock << "\n";
                cout << "Cuanta cantidad desea ingresar?: ";
                int cantidad_a_entrar;
                cin >> cantidad_a_entrar;

                if (inventario[i].stock + cantidad_a_entrar > inventario[i].cantidad_maxima){
                    cout << "No se puede ingresar esa cantidad. Excede la cantidad maxima permitida." << "\n";
                }
                else{
                    break;
                }
            }

            if (inventario[i].cantidad_de_entrada >= 100){
                cout << "No se pueden registrar mas entradas para este articulo." << "\n";
                return;
            }

            movimiento nueva_entrada;
            nueva_entrada.codigo_articulo = inventario[i].codigo;
            nueva_entrada.tipo_movimiento = "entrada";
            nueva_entrada.cantidad = cantidad_a_entrar;
            nueva_entrada.fecha_hora = obtener_fecha_hora_actual();

            inventario[i].entrada[inventario[i].cantidad_de_entrada] = nueva_entrada;
            inventario[i].cantidad_de_entrada++;
            inventario[i].stock += cantidad_a_entrar;

            cout << "Entrada registrada exitosamente." << "\n";
        }
    }

}

int main(){

    Articulo inventario[100];
    int cantidad_de_articulos = 0;
    int opciones;
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
    cout << " ========================= " << "\n";

    while (true) {

        opciones = leer_opcion_menu();

        cout << "\n";  

        switch (opciones) {

            case 1:
            while (true) {
                cout << "\n";
                cout << "Crear articulo." << "\n\n";
                cout << "cuantos articulos quieres crear?: ";
                x = verificacion_de_digitos();
                cout << "\n";

            }
                for (int i = 0; i < x; i++){
                    crear_articulo(inventario, cantidad_de_articulos);
                }
                break;
            case 2:
                cout << "Entrada de articulos seleccionado." << "\n";
                // Lógica para entrada de artículos
                break;
            case 3:
                cout << "Salida de articulos seleccionado." << "\n";
                // Lógica para salida de artículos
                break;
            case 4:
                cout << "Borrar un articulo seleccionado." << "\n";
                // Lógica para borrar un artículo
                break;
            case 5:
                cout << "Editar/Consultar articulo seleccionado." << "\n";
                // Lógica para editar/consultar un artículo
                break;
            case 6:
                cout << "Mostrar listado de articulos seleccionado." << "\n";
                // Lógica para mostrar listado de artículos
                break;
            case 7:
                cout << "Mostrar registro de entradas seleccionado." << "\n";
                // Lógica para mostrar registro de entradas
                break;
            case 8:
                cout << "Mostrar registro de salidas seleccionado." << "\n";
                // Lógica para mostrar registro de salidas
                break;
            case 9:
                cout << "Saliendo del programa." << "\n";
                break;
            default:
                cout << "Opcion no valida. Por favor intente de nuevo." << "\n";
        }
    }
    return 0;
}  
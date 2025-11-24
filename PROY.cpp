#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdlib>
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

void verificacion_n_s(char &respuesta , const string& mensaje){
    string linea;
    while (true){
        cout << mensaje;
        getline(cin, linea);
        
        if (linea.length() == 1 && (linea[0] == 's' || linea[0] == 'S' || linea[0] == 'n' || linea[0] == 'N')){
            respuesta = linea[0];
            break;
        }
        else{
            cout << "Entrada invalida. Ingrese 's' para si o 'n' para no." << "\n";
        }
    }
}

void pausar(){
    system("pause");
}

void limpiar_pantalla(){
    system("cls");
}

void pantalla_menu(){
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
    cout << "\n";
}

int leer_opcion_menu(){
    string opcion;

    while (true){
        cout << " ingrese el numero de la opcion: ";
        getline(cin, opcion);
        if (opcion.length() != 1){
            cout << "Entrada invalida" << "\n";
            cout << "\n";
            continue;
        }
        char opcion_char = opcion[0];

        if (opcion_char < '1' || opcion_char > '9'){
            cout << "Entrada invalida" << "\n";
            continue;
        }
        else{
            return opcion_char - '0';
        }
    }
}

int verificacion_de_digitos(const string& mensaje){
    string cantidades;

    while (true){

        cout << mensaje;
        getline(cin, cantidades);

        if (cantidades.empty()) {
            cout << "Entrada invalida." << "\n";
            continue;
        }

        if(cantidades[0] == '-'){
            cout << "Entrada invalida" << "\n";
            continue;
        }

        bool numero_valido = true;
        for (char c : cantidades){
            if (c < '0' || c > '9'){
                numero_valido = false;
                break;
            }
        }

        if (!numero_valido){
            cout << "Entrada invalida" << "\n";
            continue;
        }
        int numero = 0;
        for (char c : cantidades){
            numero = numero * 10 + (c - '0');
        }
        return numero;
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
            cout << "El codigo ya existe, ingrese un codigo diferente." << "\n";
            cout << "\n";
        }
        else{
            break;
        }
    }

    Articulo nuevo_articulo;
    nuevo_articulo.codigo = codigo_nuevo;
    
    cout << "Ingrese el nombre del articulo: "; 
    cin >> nuevo_articulo.nombre;
    cin.ignore(10000, '\n');

    while (true){

        nuevo_articulo.cantidad_minima = verificacion_de_digitos("Ingrese la cantidad minima: ");

        if (nuevo_articulo.cantidad_minima < 0){
            cout << "La cantidad minima no puede ser negativa. Intente de nuevo." << "\n";
            continue;
        }

        while(true){
            nuevo_articulo.cantidad_maxima = verificacion_de_digitos("Ingrese la cantidad maxima: ");

            if (nuevo_articulo.cantidad_maxima < 0){
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
    char respuesta; 
    verificacion_n_s(respuesta, "quiere agregar stock inicial? (s/n): ");
    if (respuesta == 's' || respuesta == 'S'){
        while (true){ 
            int stock_inicial;
            stock_inicial = verificacion_de_digitos("Ingrese la cantidad de stock inicial: ");

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

void entrada_de_articulos(Articulo inventario[], int cantidad_de_articulos, int &cantidad_a_entrar){
    string codigo_a_buscar;

    while (true){
        cout << "entrada numero " << cantidad_a_entrar + 1 << "\n";
        cout << "ingrese el codigo del articulo para entrada: "; cin >> codigo_a_buscar;
        cin.ignore(10000, '\n');

        if (!codigo_existe(inventario, cantidad_de_articulos, codigo_a_buscar)){
            cout << "El codigo no existe. Ingrese un codigo valido." << "\n";
            continue;

        }
        else{
            break;
        }

    }

    for (int i = 0; i < cantidad_de_articulos; i++){
        if (inventario[i].codigo == codigo_a_buscar){
            if (inventario[i].stock >= inventario[i].cantidad_maxima){
                cout << "\n";
                cout << "cantidad maxima: " << inventario[i].cantidad_maxima << "\n";
                cout << "stock actual: " << inventario[i].stock << "\n";
                cout << "no puedes realizar entradas de este articulo por que el stock llego al maximo."; 
                cout << "\n";
                break;
            }
        }
        if (inventario[i].codigo == codigo_a_buscar){

            int cantidad_a_entrar = 0;

            while(true){
                cout << "Stock actual: " << inventario[i].stock << "\n";
                cout << "Cantidad maxima: " << inventario[i].cantidad_maxima << "\n";
                cout << "Cantidad minima: " << inventario[i].cantidad_minima << "\n";
                cout << "cantidad disponible para ingresar a stock: " << inventario[i].cantidad_maxima - inventario[i].stock << "\n";
                cantidad_a_entrar = verificacion_de_digitos("Cuanta cantidad desea ingresar?: ");

                if (inventario[i].stock + cantidad_a_entrar > inventario[i].cantidad_maxima){
                    cout << "No se puede ingresar esa cantidad, excede la cantidad maxima permitida." << "\n";
                    continue;
                }
                else{
                    break;
                }
            }

            if (inventario[i].cantidad_de_entrada >= 50){
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
    cantidad_a_entrar++;

}

void salida_de_articulos(Articulo inventario[], int cantidad_de_articulos, int &cantidad_a_salir){
    string codigo_a_buscar;

    while (true){
        cout << "salida numero " << cantidad_a_salir + 1 << "\n";
        cout << "ingrese el codigo del articulo para salida: "; cin >> codigo_a_buscar;
        cin.ignore(10000, '\n');

        if (!codigo_existe(inventario, cantidad_de_articulos, codigo_a_buscar)){
            cout << "El codigo no existe. Ingrese un codigo valido." << "\n";
            continue;

        }
        else{
            break;
        }

    }


    for (int i = 0; i < cantidad_de_articulos; i++){

        if (inventario[i].codigo == codigo_a_buscar){
            if (inventario[i].stock <= inventario[i].cantidad_minima){
                cout << "\n";
                cout << "cantidad minima: " << inventario[i].cantidad_minima << "\n";
                cout << "stock actual: " << inventario[i].stock << "\n";
                cout << "no puedes realizar salidas de este articulo por que el stock llego al minimo."; 
                cout << "\n";
                break;
            }
        }   
        if (inventario[i].codigo == codigo_a_buscar){

            int cantidad_a_salir = 0;

            while(true){
                cout << "Stock actual: " << inventario[i].stock << "\n";
                cout << "Cantidad minima: " << inventario[i].cantidad_minima << "\n";                  
                cout << "cantidad disponible para salir de stock: " << inventario[i].stock - inventario[i].cantidad_minima << "\n";
                cantidad_a_salir = verificacion_de_digitos("Cuanta cantidad desea retirar?: ");

                if (inventario[i].stock - cantidad_a_salir < inventario[i].cantidad_minima){
                    cout << "No se puede retirar esa cantidad, excede la cantidad minima permitida." << "\n";
                    continue;
                }
                else{
                    break;
                }
            }

            if (inventario[i].cantidad_de_salida >= 50){
                cout << "No se pueden registrar mas salidas para este articulo." << "\n";
                return;
            }

            movimiento nueva_salida;
            nueva_salida.codigo_articulo = inventario[i].codigo;
            nueva_salida.tipo_movimiento = "salida";
            nueva_salida.cantidad = cantidad_a_salir;
            nueva_salida.fecha_hora = obtener_fecha_hora_actual();

            inventario[i].salida[inventario[i].cantidad_de_salida] = nueva_salida;
            inventario[i].cantidad_de_salida++;
            inventario[i].stock -= cantidad_a_salir;

            cout << "Salida registrada exitosamente." << "\n";
        }
    }

}

void borrar_articulo(Articulo inventario[], int &cantidad_de_articulos) {

    if (cantidad_de_articulos == 0) {
        cout << "No hay articulos en el inventario para borrar.\n\n";
        return;
    }

    string codigo_borrar;
    cout << "Ingrese el codigo del articulo a borrar: ";
    cin >> codigo_borrar;
    cin.ignore(10000, '\n');

    int pos = -1;
    for (int i = 0; i < cantidad_de_articulos; i++) {
        if (inventario[i].codigo == codigo_borrar) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "El articulo con ese codigo no existe.\n\n";
        return;
    }

    // Mostrar el articulo encontrado
    cout << "\n--- Datos del Articulo ---\n";
    cout << "Codigo: " << inventario[pos].codigo << endl;
    cout << "Nombre: " << inventario[pos].nombre << endl;
    cout << "Stock: " << inventario[pos].stock << endl;
    cout << "--------------------------\n";

    // CONFIRMACION USANDO TU FUNCION
    char confirmar;
    verificacion_n_s(confirmar, "¿Seguro que desea borrar este articulo? (s/n): ");

    if (confirmar == 'n' || confirmar == 'N') {
        cout << "\nOperacion cancelada. No se borro nada.\n\n";
        return;
    }

    // Borrar (solo si dijo s o S)
    for (int i = pos; i < cantidad_de_articulos - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    cantidad_de_articulos--;

    cout << "\nArticulo eliminado correctamente.\n\n";
}


int main(){

    Articulo inventario[100];
    int cantidad_de_articulos = 0;
    int cantidad_a_entrar = 0;
    int cantidad_a_salir = 0;
    int opciones;
    int x;
    pantalla_menu();

    while (true) {
        opciones = leer_opcion_menu();
        cout << "\n";  

        switch (opciones){

            case 1:
                limpiar_pantalla();
                while (true){

                    cout << "\n";
                    cout << "Crear articulo." << "\n\n";
                    x = verificacion_de_digitos("cuantos articulos quieres crear?: ");
                    limpiar_pantalla();
                    if (x == 0){
                        cout << "no se creara ningun articulo." << "\n\n";
                        break;
                    }
                    for (int i = 0; i < x; i++){
                        crear_articulo(inventario, cantidad_de_articulos);
                    }
                    cout << "\n";
                    break;
                }
                pausar();
                limpiar_pantalla();
                pantalla_menu();
                break;

            case 2:

                limpiar_pantalla();
                if (cantidad_de_articulos == 0){
                    cout << "No se puede hacer entradas, por que no hay articulos en el inventario." << "\n";
                    cout << "Cree un articulo primero." << "\n";
                    cout << "\n";
                    pausar();
                    limpiar_pantalla();
                    pantalla_menu();
                    break;
                }
                cout << "Entrada de articulos." << "\n";
                cout << "\n";
                while (true){
                    x = verificacion_de_digitos("cuantas entradas quieres hacer?: ");
                    limpiar_pantalla();
                    if (x == 0){
                        cout << "no se ingresara ningun articulo." << "\n\n";
                        break;
                    }
                    for (int i = 0; i < x; i++){
                        entrada_de_articulos(inventario, cantidad_de_articulos, cantidad_a_entrar);
                        cout << "\n";
                    }
                    cout << "\n";
                    break;
                }
                pausar();
                limpiar_pantalla();
                pantalla_menu();
                break; 
                
            case 3:
                limpiar_pantalla();
                if (cantidad_de_articulos == 0){
                    cout << "No se puede realizar salidas por que no hay articulos." << "\n" <<  "Cree un articulo primero.";
                    cout << "\n\n";
                    pausar();
                    limpiar_pantalla();
                    pantalla_menu();
                    break;
                }
                cout << "Salida de articulos." << "\n";
                cout << "\n";
                while (true){
                    x = verificacion_de_digitos("cuantas salidas quieres hacer?: ");
                    limpiar_pantalla();
                    if (x == 0){
                        cout << "no se retirara ningun articulo." << "\n\n";
                        break;
                    }
                    for (int i = 0; i < x; i++){
                        salida_de_articulos(inventario, cantidad_de_articulos, cantidad_a_salir);
                        cout << "\n";
                    }
                    cout << "\n";
                    break;
                }
                pausar();
                limpiar_pantalla();
                pantalla_menu();
                break;
            case 4:
                limpiar_pantalla();
                cout << "Borrar un articulo seleccionado." << "\n";
                // Lógica para borrar un artículo
                borrar_articulo(inventario, cantidad_de_articulos);
                pausar();
                limpiar_pantalla();
                pantalla_menu();
                break;
            case 5:
                cout << "Editar/Consultar articulo seleccionado." << "\n";
                // Lógica para editar/consultar un artículo
                pausar();
                pantalla_menu();
                break;
            case 6:
                cout << "Mostrar listado de articulos seleccionado." << "\n";
                // Lógica para mostrar listado de artículos
                pausar();
                pantalla_menu();
                break;
            case 7:
                cout << "Mostrar registro de entradas seleccionado." << "\n";
                // Lógica para mostrar registro de entradas
                pausar();
                pantalla_menu();
                break;
            case 8:
                cout << "Mostrar registro de salidas seleccionado." << "\n";
                // Lógica para mostrar registro de salidas
                pausar();
                pantalla_menu();
                break;
            case 9:

                cout << "Saliendo del programa." << "\n";
                return 0;
            default:
                cout << "Opcion no valida. Por favor intente de nuevo." << "\n";
        
        }
    }
}
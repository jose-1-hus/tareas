#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// Funci�n para limpiar el buffer de entrada (teclado)
// Se usa para evitar que queden caracteres pendientes (como '\n') en el flujo de entrada
// despu�s de usar 'cin >>', lo que puede causar que 'getline()' salte la lectura.
void limpiarBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}

// Estructura que representa un art�culo en el inventario
struct Articulo {
    string codigo;       // C�digo �nico que identifica al art�culo
    string nombre;       // Nombre descriptivo del art�culo
    int stockMinimo;     // Cantidad m�nima que debe mantenerse en inventario
    int stockMaximo;     // Cantidad m�xima permitida en inventario
    int stockActual;     // Cantidad actual disponible del art�culo
};

// Estructura que representa un movimiento de inventario (entrada o salida)
struct Movimiento {
    string codigo;       // C�digo del art�culo al que pertenece el movimiento
    string nombre;       // Nombre del art�culo (guardado por comodidad)
    int cantidad;        // Cantidad de unidades ingresadas o retiradas
    string fechaHora;    // Fecha y hora exacta en que ocurri� el movimiento
};

Articulo inventario[500];      // capacidad m�xima
Movimiento registroEntradas[500];
Movimiento registroSalidas[500];

int totalInventario = 0;
int totalEntradas = 0;
int totalSalidas = 0;

// Funci�n que obtiene la fecha y hora actual en formato legible
string obtenerFechaHora() {
    time_t ahora = time(0);           // Obtiene la hora actual del sistema (en segundos desde 1970)
    tm *t = localtime(&ahora);        // Convierte la hora actual a formato local (d�a, mes, hora, etc.)
    char buffer[100];                 // Buffer para almacenar la fecha formateada
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", t);  // Da formato: d�a/mes/a�o hora:minuto
    return string(buffer);            // Retorna la fecha como cadena de texto (string)
}

// Funci�n que busca un art�culo por su c�digo dentro del inventario
Articulo* buscarArticulo(string codigo) {
    // Recorre todo el inventario
    for (int i = 0; i < totalInventario; i++) {
        // Si encuentra el art�culo con el c�digo solicitado, devuelve su direcci�n en memoria
        if (inventario[i].codigo == codigo)
            return &inventario[i];
    }
    // Si no lo encuentra, devuelve NULL (puntero nulo)
    return NULL;
}

void buscarArticuloMenu() {
    system(CLEAR);
    string codigo;

    cout << "\n===== BUSCAR ARTICULO =====\n";
    cout << "Ingrese el codigo del articulo: ";
    cin >> codigo;

    Articulo* art = buscarArticulo(codigo);

    if (!art) {
        cout << "El articulo (" << codigo << ") no existe.\n";
        cin.get();
        return;
    }

    cout << "\nCodigo: " << art->codigo
         << "\nNombre: " << art->nombre
         << "\nStock minimo: " << art->stockMinimo
         << "\nStock maximo: " << art->stockMaximo
         << "\nStock actual: " << art->stockActual << endl;
         
	cin.get();
}


// Funci�n para crear y registrar un nuevo art�culo en el inventario
void crearArticulo() {
    system(CLEAR);   // Limpia la pantalla (usa "cls" en Windows o "clear" en Linux/Mac)

    Articulo art;    // Crea una variable temporal de tipo Articulo para almacenar los datos ingresados
    
    cout << "\n===== CREAR ARTICULO =====\n";

    // Solicita el c�digo del nuevo art�culo
    cout << "Ingrese el codigo del articulo: ";
    cin >> art.codigo;

    // Verifica si ya existe un art�culo con el mismo c�digo
    if (buscarArticulo(art.codigo)) {
        cout << "El articulo con codigo " << art.codigo << " ya existe.\n";
        return;  // Finaliza la funci�n sin agregar el art�culo
    }

    // Solicita el nombre del art�culo (usa getline para permitir espacios en el texto)
    cout << "Ingrese el nombre del articulo: ";
    limpiarBuffer();            // Limpia el buffer de entrada antes de usar getline()
    getline(cin, art.nombre); // Captura el nombre completo (con espacios si los hay)

    // Solicita los valores del stock m�nimo y m�ximo
    cout << "Ingrese el stock minimo: ";
    cin >> art.stockMinimo;
    cout << "Ingrese el stock maximo: ";
    cin >> art.stockMaximo;

    // Inicializa el stock actual en cero (ya que es un art�culo reci�n creado)
    art.stockActual = 0;
    
    // Agrega el art�culo al inventario
    inventario[totalInventario] = art;
	totalInventario++;

    // Confirma al usuario que el art�culo fue agregado exitosamente
    cout << "Articulo agregado correctamente.\n";
    
	cin.get();
}


// Funci�n que gestiona la ENTRADA (ingreso) de unidades al inventario
void entradaArticulo() {
    system(CLEAR);   // Limpia la pantalla antes de mostrar el formulario

    string codigo;   // Variable para almacenar el c�digo del art�culo
    int cantidad;    // Variable para la cantidad que se desea ingresar
    
    cout << "\n===== ENTRADA UNIDADES ARTICULOS =====\n";

    // Solicita al usuario el c�digo del art�culo
    cout << "Ingrese el codigo del articulo: ";
    cin >> codigo;

    // Busca el art�culo en el inventario mediante su c�digo
    Articulo* art = buscarArticulo(codigo);

    // Si no se encuentra el art�culo, muestra mensaje y termina la funci�n
    if (!art) {
        cout << "El articulo (" << codigo << ") no existe en el inventario.\n";
        cin.get();
        return;
    }

    // Solicita la cantidad de unidades a ingresar
    cout << "Ingrese la cantidad a ingresar: ";
    cin >> cantidad;

    // Validaci�n 1: si el stock actual es 0, la cantidad ingresada debe ser al menos igual al stock m�nimo
    if (art->stockActual == 0 && cantidad < art->stockMinimo) {
        cout << "La entrada del articulo (" << codigo << ") no corresponde con el minimo permitido ("
             << art->stockMinimo << " unidades).\n";
             cin.get();
        return;
    }

    // Validaci�n 2: no se puede exceder el stock m�ximo permitido
    if (art->stockActual + cantidad > art->stockMaximo) {
        cout << "La entrada del articulo (" << codigo << ") supera el maximo permitido ("
             << art->stockMaximo << " unidades).\n";
             cin.get();
        return;
    }

    // Si pasa las validaciones, se actualiza el stock actual sumando la cantidad ingresada
    art->stockActual += cantidad;

    // Crea un registro del movimiento (entrada) con fecha y hora
    Movimiento mov = {codigo, art->nombre, cantidad, obtenerFechaHora()};
    registroEntradas[totalEntradas] = mov;
	totalEntradas++;  // Agrega el movimiento al registro global de entradas

    // Muestra confirmaci�n al usuario con el nuevo stock actualizado
    cout << "Entrada registrada para el articulo (" << codigo
         << ") - stock actual: " << art->stockActual << " unidades.\n";
         
    cin.get();
}


// Funci�n que gestiona la SALIDA (retiro) de unidades del inventario
void salidaArticulo() {
    system(CLEAR);   // Limpia la pantalla antes de mostrar el formulario
    
    string codigo;   // Variable para almacenar el c�digo del art�culo
    int cantidad;    // Variable para la cantidad que se desea retirar
    
    cout << "\n===== SALIDA UNIDADES ARTICULOS =====\n";
    
    // Solicita al usuario el c�digo del art�culo
    cout << "Ingrese el codigo del articulo: ";
    cin >> codigo;

    // Busca el art�culo en el inventario mediante su c�digo
    Articulo* art = buscarArticulo(codigo);

    // Si no se encuentra el art�culo, muestra mensaje y termina la funci�n
    if (!art) {
        cout << "El articulo (" << codigo << ") no existe en el inventario.\n";
        cin.get();
        return;
    }

    // Solicita la cantidad de unidades a retirar
    cout << "Ingrese la cantidad a retirar: ";
    cin >> cantidad;

    // Validaci�n 1: No se puede retirar m�s de lo que hay disponible en el stock actual
    if (cantidad > art->stockActual) {
        cout << "No hay suficientes unidades en stock.\n";
        cin.get();
        return;
    }

    // Validaci�n 2: No se permite que el stock actual quede por debajo del m�nimo permitido
    // Si al restar la cantidad, el stock resultante es menor que el m�nimo ? se bloquea la salida
    if ((art->stockActual - cantidad) < art->stockMinimo) {
        cout << "La salida del articulo (" << codigo << ") supera la cantidad permitida "
             << "para el stock minimo (" << art->stockMinimo << " unidades).\n";
        cin.get();
        return;
    }

    // Si pasa las validaciones, se actualiza el stock restando la cantidad retirada
    art->stockActual -= cantidad;

    // Crea un registro del movimiento (salida) con fecha y hora
    Movimiento mov = {codigo, art->nombre, cantidad, obtenerFechaHora()};
    registroSalidas[totalSalidas] = mov;
	totalSalidas++;  // Agrega el movimiento al registro global de salidas

    // Muestra confirmaci�n al usuario con el nuevo stock actualizado
    cout << "Salida registrada para el articulo (" << codigo
         << ") - stock actual: " << art->stockActual << " unidades.\n";
         
	cin.get();
}


// Funci�n para eliminar un art�culo del inventario
void borrarArticulo() {
    system(CLEAR);  // Limpia la consola (depende del sistema operativo)

    string codigo;  // Variable para almacenar el c�digo del art�culo a eliminar
	
	cout << "\n===== BORRADO ARTICULOS INVENTARIO =====\n";    
    
    // Solicita al usuario el c�digo del art�culo
    cout << "Ingrese el codigo del articulo a eliminar: ";
    cin >> codigo;

    // Recorre todo el inventario buscando el art�culo con el c�digo ingresado
    for (int i = 0; i < totalInventario; i++) {
        if (inventario[i].codigo == codigo) {  // Si encuentra coincidencia

            // Muestra los datos del art�culo encontrado
            cout << "\nCodigo: " << inventario[i].codigo
                 << "\nNombre: " << inventario[i].nombre
                 << "\nStock minimo: " << inventario[i].stockMinimo
                 << "\nStock maximo: " << inventario[i].stockMaximo
                 << "\nStock actual: " << inventario[i].stockActual << endl;

            // Pide confirmaci�n al usuario antes de eliminar
            char confirm;
            cout << "�Desea eliminar este articulo? (y/n): ";
            cin >> confirm;

            // Si el usuario confirma con 'y' o 'Y'
            if (confirm == 'y' || confirm == 'Y') {
                // Elimina el art�culo del 'inventario'
                for (int j = i; j < totalInventario - 1; j++) {
				    inventario[j] = inventario[j + 1];
				}
				totalInventario--;
                cout << "Articulo (" << codigo << ") eliminado.\n";
            } else {
                // Si el usuario cancela
                cout << "Operacion cancelada.\n";
            }
            
            cin.get();

            return;  // Sale de la funci�n despu�s de eliminar o cancelar
        }
    }

    // Si no se encontr� el c�digo en el inventario
    cout << "El articulo (" << codigo << ") no existe.\n";
    
    cin.get();
}


// Funci�n para editar o consultar los datos de un art�culo existente
void editarConsultarArticulo() {
    system(CLEAR);  // Limpia la consola

    string codigo;  // Variable para almacenar el c�digo del art�culo que se desea editar
    
    cout << "\n=== EDICION DE ARTICULOS ===\n";
    
    // Solicita el c�digo del art�culo
    cout << "Ingrese el codigo del articulo: ";
    cin >> codigo;

    // Busca el art�culo en el inventario
    Articulo* art = buscarArticulo(codigo);

    // Si no se encuentra, se notifica y se termina la funci�n
    if (!art) {
        cout << "El articulo (" << codigo << ") no existe.\n";
        cin.get();
        return;
    }

    int op;  // Variable para controlar el men� de opciones

    // Ciclo que permite editar distintos campos hasta que el usuario decida salir
    do {
        system(CLEAR);  // Limpia la consola en cada iteraci�n del men�

        // Muestra las opciones de edici�n con los valores actuales del art�culo
        cout << "\n=== EDICION DEL ARTICULO (" << codigo << ") ===\n";
        cout << "1. Modificar Nombre (actual: " << art->nombre << ")\n";
        cout << "2. Modificar Stock Minimo (actual: " << art->stockMinimo << ")\n";
        cout << "3. Modificar Stock Maximo (actual: " << art->stockMaximo << ")\n";
        cout << "4. Modificar Stock Actual (actual: " << art->stockActual << ")\n";
        cout << "5. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> op;

        // Controla las distintas opciones seleccionadas por el usuario
        switch (op) {
            case 1: { // Modificar nombre
                limpiarBuffer();  // Limpia el buffer del teclado
                cout << "Nuevo nombre: ";
                getline(cin, art->nombre);  // Permite ingresar nombres con espacios
                cout << "Nombre actualizado correctamente.\n";
                break;
            }
            case 2: { // Modificar stock m�nimo
                cout << "Nuevo stock minimo: ";
                int nuevo;
                cin >> nuevo;

                // Verifica que el nuevo stock m�nimo no sea mayor al m�ximo
                if (nuevo > art->stockMaximo) {
                    cout << "El stock minimo no puede ser mayor que el maximo (" << art->stockMaximo << " unidades).\n";
                    cin.get();
                } else {
                    art->stockMinimo = nuevo;
                    cout << "Stock minimo actualizado correctamente.\n";
                    cin.get();
                }
                break;
            }
            case 3: { // Modificar stock m�ximo
                cout << "Nuevo stock maximo: ";
                int nuevo;
                cin >> nuevo;

                // Verifica que el nuevo stock m�ximo no sea menor al m�nimo
                if (nuevo < art->stockMinimo) {
                    cout << "El stock maximo no puede ser menor que el minimo (" << art->stockMinimo << " unidades).\n";
                    cin.get();
                } else {
                    art->stockMaximo = nuevo;
                    cout << "Stock maximo actualizado correctamente.\n";
                    cin.get();
                }
                break;
            }
            case 4: { // Modificar stock actual
                int nuevoStock;
                cout << "Nuevo stock actual: ";
                cin >> nuevoStock;

                // Valida que el nuevo stock est� dentro del rango permitido
                if (nuevoStock < art->stockMinimo) {
                    cout << "El stock no puede ser menor al minimo (" << art->stockMinimo << " unidades).\n";
                    cin.get();
                } else if (nuevoStock > art->stockMaximo) {
                    cout << "El stock no puede ser mayor al maximo (" << art->stockMaximo << " unidades).\n";
                    cin.get();
                } else {
                    art->stockActual = nuevoStock;
                    cout << "Stock actualizado correctamente.\n";
                    cin.get();
                }
                break;
            }
            case 5: // Salir del men�
                break;
            default: // En caso de opci�n inv�lida
                cout << "Opcion invalida.\n";
        }

        // Pausa antes de volver a mostrar el men� (excepto al salir)
        if (op != 5) {
            cout << "\nPresione cualquier tecla para continuar...";
            cin.get();
        }

    } while (op != 5);  // Repite mientras el usuario no elija salir
}


// Funci�n para mostrar un listado completo de los art�culos del inventario
void mostrarListadoArticulos() {
    system(CLEAR);  // Limpia la consola antes de mostrar el listado

    cout << "\n=== LISTADO DE ARTICULOS ===\n";

    // Encabezados de las columnas, alineados a la izquierda con formato de ancho fijo
    cout << left << setw(10) << "Codigo"
         << setw(20) << "Nombre"
         << setw(10) << "Minimo"
         << setw(10) << "Maximo"
         << setw(10) << "Stock" << endl;

    // L�nea separadora para mayor legibilidad
    cout << string(60, '-') << endl;

    // Recorre el 'inventario' para mostrar cada art�culo
    for (int i = 0; i < totalInventario; i++) {
        Articulo a = inventario[i];  // Obtiene una copia del art�culo actual

        // Muestra la informaci�n del art�culo en formato tabular
        cout << left << setw(10) << a.codigo
             << setw(20) << a.nombre
             << setw(10) << a.stockMinimo
             << setw(10) << a.stockMaximo
             << setw(10) << a.stockActual << endl;
    }
}


// Funci�n para mostrar el historial de movimientos de entrada de art�culos al inventario
void mostrarRegistroEntradas() {
    system(CLEAR);  // Limpia la pantalla antes de mostrar el registro

    cout << "\n=== REGISTRO DE ENTRADAS ===\n";

    // Encabezado de columnas con formato alineado
    cout << left << setw(10) << "Codigo"
         << setw(20) << "Nombre"
         << setw(10) << "Cantidad"
         << setw(20) << "Fecha" << endl;

    // L�nea divisoria para una mejor presentaci�n
    cout << string(60, '-') << endl;

    // Recorre el 'registroEntradas' para mostrar cada movimiento registrado
    for (int i = 0; i < totalEntradas; i++) {
        Movimiento r = registroEntradas[i];  // Obtiene una copia del movimiento actual

        // Muestra los datos del movimiento: c�digo, nombre, cantidad y fecha/hora
        cout << left << setw(10) << r.codigo
             << setw(20) << r.nombre
             << setw(10) << r.cantidad
             << setw(20) << r.fechaHora << endl;
    }
}


// Funci�n para mostrar el historial de movimientos de salida de art�culos del inventario
void mostrarRegistroSalidas() {
    system(CLEAR);  // Limpia la pantalla antes de mostrar el registro

    cout << "\n=== REGISTRO DE SALIDAS ===\n";

    // Encabezado de columnas con formato alineado
    cout << left << setw(10) << "Codigo"
         << setw(20) << "Nombre"
         << setw(10) << "Cantidad"
         << setw(20) << "Fecha" << endl;

    // L�nea divisoria para separar visualmente el encabezado del contenido
    cout << string(60, '-') << endl;

    // Recorre el 'registroSalidas' para mostrar cada movimiento de salida
    for (int i = 0; i < totalSalidas; i++) {
        Movimiento r = registroSalidas[i];  // Obtiene una copia del movimiento actual

        // Muestra los datos del movimiento: c�digo, nombre, cantidad retirada y fecha/hora
        cout << left << setw(10) << r.codigo
             << setw(20) << r.nombre
             << setw(10) << r.cantidad
             << setw(20) << r.fechaHora << endl;
    }
}


// Funci�n principal del programa - Controla el flujo general del sistema de inventario
int main() {
    int opcion;

    do {
    	
    	system(CLEAR);  // Limpia la pantalla en cada iteraci�n del men�
    	
    	// Muestra el men� principal del sistema de inventario
        cout << "==== Sistema de Inventario ====\n";
        cout << "1. Crear Articulos\n";
        cout << "2. Entrada de Articulos\n";
        cout << "3. Salida de Articulos\n";
        cout << "4. Borrar un Articulo\n";
        cout << "5. Editar/Consultar Articulo\n";
        cout << "6. Mostrar Listado de Articulos\n";
        cout << "7. Mostrar Registro de Entradas\n";
        cout << "8. Mostrar Registro de Salidas\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cout << "Entrada invalida, intentelo de nuevo.\n";
            cin.clear();
            limpiarBuffer();
            continue;
        }

        limpiarBuffer(); // limpiar buffer despu�s de leer n�meros

        switch (opcion) {
            case 1:
                crearArticulo();
                break;
            case 2:
                entradaArticulo();
                break;
            case 3:
                salidaArticulo();
                break;
            case 4:
                borrarArticulo();
                break;
            case 5:
                editarConsultarArticulo();
                break;
            case 6:
                mostrarListadoArticulos();
                break;
            case 7:
                mostrarRegistroEntradas();
                break;
            case 8:
                mostrarRegistroSalidas();
                break;
            case 9:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

        if (opcion != 9) {
            cout << "\nPresione cualquier tecla para continuar...";
            cin.get();
        }

    } while (opcion != 9);

    return 0;
}


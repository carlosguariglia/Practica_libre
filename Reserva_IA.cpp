#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Definimos los enumeradores para códigos de aeropuertos y clases
enum CodigoAero { BHI = 1, AEP, EPA, EZE, BRC, CTC, CRD };
enum Clase { PRIMERA = 1, BUSSINESS, ECONOMICA };

// Definimos la estructura para almacenar los datos de la reserva
struct Reserva {
    int IDReserva;
    string dni;
    string apellido;
    string nombre;
    Clase clase;
    CodigoAero origen;
    CodigoAero destino;
};

// Definimos la longitud máxima del arreglo de reservas
const int MAX = 10;

// Función para tomar una nueva reserva
void tomarReserva(Reserva reservas[], int& siguienteIDReserva) {
    for (int i = 0; i < MAX; ++i) {
        if (reservas[i].IDReserva == -1) {
            reservas[i].IDReserva = siguienteIDReserva++;
            
            cin.ignore();
            cout << "Introduzca su DNI: ";
            getline(cin, reservas[i].dni);

            cout << "Introduzca su Apellido: ";
            getline(cin, reservas[i].apellido);

            cout << "Introduzca su Nombre: ";
            getline(cin, reservas[i].nombre);

            int clase;
            cout << "Seleccione la clase (1. Primera, 2. Bussiness, 3. Economica): ";
            cin >> clase;
            reservas[i].clase = static_cast<Clase>(clase);

            cout << "Código Aeropuerto:\n";
            cout << "1. Bahía Blanca - BHI\n";
            cout << "2. Buenos Aires Aeroparque - AEP\n";
            cout << "3. Buenos Aires El Palomar - EPA\n";
            cout << "4. Buenos Aires Ezeiza - EZE\n";
            cout << "5. San Carlos de Bariloche - BRC\n";
            cout << "6. San Fernando del Valle de Catamarca - CTC\n";
            cout << "7. Comodoro Rivadavia - CRD\n";

            int opcionOrigen, opcionDestino;
            cout << "Seleccione el aeropuerto de origen (número): ";
            cin >> opcionOrigen;
            reservas[i].origen = static_cast<CodigoAero>(opcionOrigen);

            cout << "Seleccione el aeropuerto de destino (número): ";
            cin >> opcionDestino;
            while (opcionOrigen == opcionDestino) {
                cout << "El aeropuerto de destino no puede ser el mismo que el de origen.\n";
                cout << "Introduzca el aeropuerto de destino (número): ";
                cin >> opcionDestino;
            }
            reservas[i].destino = static_cast<CodigoAero>(opcionDestino);
            break;
        }
    }
}

// Función para cargar las reservas desde un archivo
void cargarReservasDesdeArchivo(Reserva reservas[], int& siguienteIDReserva) {
    ifstream archivo("reservas.txt");
    if (archivo.is_open()) {
        for (int i = 0; i < MAX; ++i) {
            archivo >> reservas[i].IDReserva;
            if (reservas[i].IDReserva == -1) {
                break; // Fin del archivo
            }
            archivo >> reservas[i].dni >> reservas[i].apellido >> reservas[i].nombre;
            int clase;
            archivo >> clase;
            reservas[i].clase = static_cast<Clase>(clase);
            int origen;
            archivo >> origen;
            reservas[i].origen = static_cast<CodigoAero>(origen);
            int destino;
            archivo >> destino;
            reservas[i].destino = static_cast<CodigoAero>(destino);
            if (reservas[i].IDReserva >= siguienteIDReserva) {
                siguienteIDReserva = reservas[i].IDReserva + 1;
            }
        }
        archivo.close();
        cout << "Reservas cargadas desde el archivo 'reservas.txt'.\n";
    } else {
        // Si el archivo no existe, inicializar el arreglo y crear el archivo con un valor inicial de -1
        for (int i = 0; i < MAX; ++i) {
            reservas[i].IDReserva = -1;
        }
        ofstream nuevoArchivo("reservas.txt");
        if (nuevoArchivo.is_open()) {
            nuevoArchivo << -1 << "\n";
            nuevoArchivo.close();
            cout << "Archivo 'reservas.txt' creado con el sentinela -1.\n";
        } else {
            cout << "No se pudo crear el archivo 'reservas.txt'.\n";
        }
    }
}

// Función para guardar las reservas en un archivo
void guardarReservasEnArchivo(Reserva reservas[]) {
    ofstream archivo("reservas.txt");
    if (archivo.is_open()) {
        for (int i = 0; i < MAX; ++i) {
            if (reservas[i].IDReserva == -1) {
                break; // No escribir más allá del sentinela
            }
            archivo << reservas[i].IDReserva << " "
                    << reservas[i].dni << " "
                    << reservas[i].apellido << " "
                    << reservas[i].nombre << " "
                    << reservas[i].clase << " "
                    << reservas[i].origen << " "
                    << reservas[i].destino << "\n";
        }
        archivo << -1 << "\n"; // Escribir el sentinela al final del archivo
        archivo.close();
        cout << "Reservas guardadas en el archivo 'reservas.txt'.\n";
    } else {
        cout << "No se pudo abrir el archivo para guardar las reservas.\n";
    }
}

// Función para mostrar las reservas
void mostrarReservas(const Reserva reservas[]) {
    cout << "Reservas actuales:\n";
    for (int i = 0; i < MAX; ++i) {
        if (reservas[i].IDReserva == -1) {
            break; // No mostrar más allá del sentinela
        }                   
        cout << "IDReserva:\t " << reservas[i].IDReserva << "\n"
             << "DNI:\t\t " << reservas[i].dni << "\n"
             << "Apellido:\t " << reservas[i].apellido << "\n"
             << "Nombre:\t\t " << reservas[i].nombre << "\n"
             << "Clase:\t\t " << reservas[i].clase << "\n"
             << "Origen:\t\t " << reservas[i].origen << "\n"
             << "Destino:\t " << reservas[i].destino << "\n"
             << "------------------------------\n";
    }
}

// Función para eliminar una reserva
void eliminarReserva(Reserva reservas[]) {
    int id;
    cout << "Introduzca el ID de la reserva a eliminar: ";
    cin >> id;

    for (int i = 0; i < MAX; ++i) {
        if (reservas[i].IDReserva == id) {
            reservas[i].IDReserva = -1; // Marcar la reserva como eliminada
            cout << "Reserva eliminada.\n";
            return;
        }
    }
    cout << "Reserva no encontrada.\n";
}

// Función para modificar una reserva
void modificarReserva(Reserva reservas[]) {
    int id;
    cout << "Introduzca el ID de la reserva a modificar: ";
    cin >> id;

    for (int i = 0; i < MAX; ++i) {
        if (reservas[i].IDReserva == id) {
            cin.ignore();
            cout << "Introduzca su DNI: ";
            getline(cin, reservas[i].dni);

            cout << "Introduzca su Apellido: ";
            getline(cin, reservas[i].apellido);

            cout << "Introduzca su Nombre: ";
            getline(cin, reservas[i].nombre);

            int clase;
            cout << "Seleccione la clase (1. Primera, 2. Bussiness, 3. Economica): ";
            cin >> clase;
            reservas[i].clase = static_cast<Clase>(clase);

            cout << "Código Aeropuerto:\n";
            cout << "1. Bahía Blanca - BHI\n";
            cout << "2. Buenos Aires Aeroparque - AEP\n";
            cout << "3. Buenos Aires El Palomar - EPA\n";
            cout << "4. Buenos Aires Ezeiza - EZE\n";
            cout << "5. San Carlos de Bariloche - BRC\n";
            cout << "6. San Fernando del Valle de Catamarca - CTC\n";
            cout << "7. Comodoro Rivadavia - CRD\n";

            int opcionOrigen, opcionDestino;
            cout << "Seleccione el aeropuerto de origen (número): ";
            cin >> opcionOrigen;
            reservas[i].origen = static_cast<CodigoAero>(opcionOrigen);

            cout << "Seleccione el aeropuerto de destino (número): ";
            cin >> opcionDestino;
            while (opcionOrigen == opcionDestino) {
                cout << "El aeropuerto de destino no puede ser el mismo que el de origen.\n";
                cout << "Introduzca el aeropuerto de destino (número): ";
                cin >> opcionDestino;
            }
            reservas[i].destino = static_cast<CodigoAero>(opcionDestino);

            cout << "Reserva modificada.\n";
            return;
        }
    }
    cout << "Reserva no encontrada.\n";
}

int main() {
    Reserva reservas[MAX];
    int siguienteIDReserva = 1;
    int menu;

    // Cargar reservas desde el archivo
    cargarReservasDesdeArchivo(reservas, siguienteIDReserva);

    do {
        cout << "1. Tomar Reserva" << endl;
        cout << "2. Mostrar Reservas" << endl;
        cout << "3. Actualizar una Reserva" << endl;
        cout << "4. Eliminar una Reserva" << endl;
        cout << "0. Guardar a Archivo y Salir" << endl;
        cout << "Opcion: ";
        cin >> menu;

        switch(menu) {
            case 1:
                tomarReserva(reservas, siguienteIDReserva);
                break;
            case 2:
                mostrarReservas(reservas);
                break;
            case 3:
                modificarReserva(reservas);
                break;
            case 4:
                eliminarReserva(reservas);
                break;
            case 0:
                guardarReservasEnArchivo(reservas);
                break;
            default:
                cout << "Opción inválida. Inténtelo de nuevo.\n";
        }
    } while (menu != 0);

    return 0;
}

  //La variable siguienteIDReserva se utiliza para mantener un valor único y
                                // consecutivo para el campo IDReserva de cada nueva reserva que se tome.
 
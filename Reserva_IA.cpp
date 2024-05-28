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
const int MAX = 3;

void clearConsole();
void tomarReserva(Reserva reservas[], int &siguienteIDReserva);
void cargarReservasDesdeArchivo(Reserva reservas[], int &siguienteIDReserva);
void guardarReservasEnArchivo(Reserva reservas[]);
void mostrarReservas(const Reserva reservas[]);
void eliminarReserva(Reserva reservas[]);
void modificarReserva(Reserva reservas[]);
string getnombreclase(Clase clase);
string getnombreaeropuerto(CodigoAero aeropuerto);

int main() {
    Reserva reservas[MAX];
    int siguienteIDReserva = 1;
    int menu;

    // Cargar reservas desde el archivo reservas.txt
    // y asigna a siguienteIDReserva la posicion libre para ingresar una nueva reserva
    cargarReservasDesdeArchivo(reservas, siguienteIDReserva);
    clearConsole();

    do {
        cout << "************************************************" << endl;
        cout << "Programa de Reservas de Vuelos" << endl;
        cout << "************************************************" << endl;
        cout << "1. Tomar Reserva" << endl;
        cout << "2. Mostrar Reservas" << endl;
        cout << "3. Actualizar una Reserva" << endl;
        cout << "4. Eliminar una Reserva" << endl;
        cout << "0. Guardar a Archivo y Salir" << endl;
        cout << "************************************************" << endl;
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

void tomarReserva(Reserva reservas[], int &siguienteIDReserva) {
    clearConsole();
    for (int i = 0; i < MAX; ++i) {
        if (reservas[i].IDReserva == -1)
        {
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
            while (clase < 1 || clase > 3)
            {
                cout << "Opcion inválida. Por favor, ingrese una opción valida.\n";
                cout << "Seleccione la clase (1. Primera, 2. Bussiness, 3. Economica): ";
                cin >> clase;
            }
            reservas[i].clase = static_cast<Clase>(clase);

            cout << "Código Aeropuerto:\n";
            cout << "1. Bahía Blanca (BHI)\n";
            cout << "2. Buenos Aires Aeroparque (AEP)\n";
            cout << "3. Buenos Aires El Palomar (EPA)\n";
            cout << "4. Buenos Aires Ezeiza (EZE)\n";
            cout << "5. San Carlos de Bariloche (BRC)\n";
            cout << "6. San Fernando del Valle de Catamarca (CTC)\n";
            cout << "7. Comodoro Rivadavia (CRD)\n";

            int opcionOrigen, opcionDestino;
            cout << "Seleccione el aeropuerto de origen (número): ";
            cin >> opcionOrigen;
            while (opcionOrigen < 1 || opcionOrigen > 7) {
                cout << "Opcion inválida. Por favor, ingrese una opción valida.\n";
                cout << "Seleccione el aeropuerto de origen (número): ";
                cin >> opcionOrigen;
            }
            reservas[i].origen = static_cast<CodigoAero>(opcionOrigen);

            cout << "Seleccione el aeropuerto de destino (número): ";
            cin >> opcionDestino;
            while (opcionDestino < 1 || opcionDestino > 7)
            {   
                cout << "Opcion inválida. Por favor, ingrese una opción valida.\n";
                cout << "Seleccione el aeropuerto de destino: ";
                cin >> opcionDestino;
            
                // Verificar que el aeropuerto de destino no sea el mismo que el de origen
                if (opcionOrigen == opcionDestino)
                    {   cout << "El aeropuerto de destino no puede ser el mismo que el de origen.\n";
                        cout << "Seleccione el aeropuerto de destino: ";
                        cin >> opcionDestino;
                    }   
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
//TODO hacer las funciones de getnombre para imprimir los valores de los enumeradores en reserva.clase y reserva.origen y reserva.destino
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
             << "Clase:\t\t " << getnombreclase(reservas[i].clase) << "\n"
             << "Origen:\t\t " << getnombreaeropuerto(reservas[i].origen) << "\n"
             << "Destino:\t " << getnombreaeropuerto(reservas[i].destino) << "\n"
             << "------------------------------\n";
    }
}

string getnombreclase(Clase clase) {
    switch (clase) {
        case PRIMERA:
            return "Primera";
        case BUSSINESS:
            return "Bussiness";
        case ECONOMICA:
            return "Economica";
        default:
            return "";
    }
}

string getnombreaeropuerto(CodigoAero aeropuerto) {
    switch (aeropuerto) {
        case BHI:
            return "Bahia Blanca";
        case AEP:
            return "Aeroparque";
        case EPA:
            return "El Palomar";
        case EZE:
            return "Ezeiza";
        case BRC:
            return "Bariloche";
        case CTC:
            return "Catamarca";
        case CRD:
            return "Comodoro Rivadavia";
        default:
            return "";
    }
}
 
// Función para eliminar una reserva
void eliminarReserva(Reserva reservas[])
{   
    clearConsole();
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
void modificarReserva(Reserva reservas[])
{
    int id;
    cout << "Introduzca el ID de la reserva a modificar: ";
    cin >> id;

    for (int i = 0; i < MAX; ++i)
    {
        if (reservas[i].IDReserva == id)
        {
            cout << "Esta es la reserva que desa modificar:\n";
            cout << "IDReserva:\t " << reservas[i].IDReserva << "\n"
             << "DNI:\t\t " << reservas[i].dni << "\n"
             << "Apellido:\t " << reservas[i].apellido << "\n"
             << "Nombre:\t\t " << reservas[i].nombre << "\n"
             << "Clase:\t\t " << reservas[i].clase << "\n"
             << "Origen:\t\t " << reservas[i].origen << "\n"
             << "Destino:\t " << reservas[i].destino << "\n"
             << "------------------------------\n";

            cout << "Indique el dato que quiere actualizar: \n";
            cout << "1. DNI                 2. Apellido\n";
            cout << "3. Nombre              4. Clase\n";
            cout << "5. Origen              6. Destino\n";  
            cout << "7. Salir sin modificar\n";
            int opcion;
            cin >> opcion;

            switch (opcion)
            {
            case 1:
                cout << "Introduzca el nuevo DNI: ";
                cin >> reservas[i].dni;
                break;
            case 2:
                cout << "Introduzca el nuevo Apellido: ";
                cin >> reservas[i].apellido;
                break;
            case 3:
                cout << "Introduzca el nuevo Nombre: ";
                cin >> reservas[i].nombre;
                break;
            case 4:
                int clase;
                cout << "Seleccione la nueva clase (1. Primera, 2. Bussiness, 3. Economica): ";
                cin >> clase;
                reservas[i].clase = static_cast<Clase>(clase);
                break;
            case 5:
                int origen;
                cout << "Código Aeropuerto:\n";
                cout << "1. Bahía Blanca - BHI\n";
                cout << "2. Buenos Aires Aeroparque - AEP\n";
                cout << "3. Buenos Aires El Palomar - EPA\n";
                cout << "4. Buenos Aires Ezeiza - EZE\n";
                cout << "5. San Carlos de Bariloche - BRC\n";
                cout << "6. San Fernando del Valle de Catamarca - CTC\n";
                cout << "7. Comodoro Rivadavia - CRD\n";
                cin >>  origen;
                reservas[i].origen = static_cast<CodigoAero>(origen);
                break;
            case 6:
                int destino;
                cout << "Código Aeropuerto:\n";
                cout << "1. Bahía Blanca - BHI\n";
                cout << "2. Buenos Aires Aeroparque - AEP\n";
                cout << "3. Buenos Aires El Palomar - EPA\n";
                cout << "4. Buenos Aires Ezeiza - EZE\n";
                cout << "5. San Carlos de Bariloche - BRC\n";
                cout << "6. San Fernando del Valle de Catamarca - CTC\n";
                cout << "7. Comodoro Rivadavia - CRD\n";
                cin >> destino;
                reservas[i].destino = static_cast<CodigoAero>(destino);
                break;
            case 7:
                return;
            default:
                cout << "Opción inválida. Por favor, ingrese una opción valida (presione una tecla para continuar).\n";
                break;
            }
            
            cout << "Reserva actualizada.\n";
            return;
        }
    }
    cout << "Reserva no encontrada.\n";
}


void clearConsole() {
    #ifdef __unix__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN64)
        system("cls");
    #endif
}

  //La variable siguienteIDReserva se utiliza para mantener un valor único y
                                // consecutivo para el campo IDReserva de cada nueva reserva que se tome.
 
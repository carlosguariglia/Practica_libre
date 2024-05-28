/*
        b. Un empresa de viaje nos pide que realicemos un programa para tomar reservas en avión,
         las mismas pueden ser clase Primera, Bussiness y económica, además del dni apellido y nombre,
          aeropuerto origen y destino:
Código Aeropuerto
1. Bahía Blanca-BHI
2. Buenos Aires Aeroparque-AEP
3. Buenos Aires El Palomar-EPA
4. Buenos Aires Ezeiza-EZE
5. San Carlos de Bariloche-BRC
6. San Fernando del Valle de Catamarca-CTC
7. Comodoro Rivadavia-CRD
El usuario introduce los datos personales, la clase y el origen – destino, mostrando el resultado x pantalla.

se usara un arreglo de tipo estructura para almacenar los datos tambien se grabara a un archivo llamado reservas.txt 
que guardara la informacion al salir el programa. 

*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


file myfile("reservas.txt");

enum CodigoAero { BHI=1, AEP, EPA, EZE, BRC, CTC, CRD };
enum Clase { PRIMERA=1, BUSSINESS, ECONOMICA };


struct Ticket {
    string nombre;
    string apellido;
    string dni;
    Clase claseVuelo;
    CodigoAero origen;
    CodigoAero destino;
};

Clase IngresarClase(int opcion);
CodigoAero IngresarOrigen(int opcion);
CodigoAero IngresarDestino(int opcion);
string getClase(Clase clase);
string getOrigen(CodigoAero origen);
string getDestino(CodigoAero destino);
void TomarReserva(string &nombre, string &apellido, string &dni, Clase &claseVuelo, CodigoAero &origen, CodigoAero &destino);
void Mostrarreserva(Clase clase, string dni, string nombre, string apellido, CodigoAero origen, CodigoAero destino);
void pauseConsole();
void clearConsole();


int main() {
    const int MAX = 100;
    Ticket viaje[MAX];

    int opcion, menu=0;
    clearConsole();
    cout << "================================================\n";
    cout << "Programa de Reservas de Vuelos\n";
    cout << "================================================\n";
    
    do {
        cout << "1- Tomar Reserva\n";
        cout << "2- Mostrar Reservas\n";
        cout << "0- Guardar y Salir\n";
        cin >> menu;
        cin.ignore();

        switch(menu) {
            case 1: TomarReserva();
                    break;
            case 2: Mostrarreserva();
                    break;
            case 0: GuardarArchivo(); 
                    cout << "Gracias por usar el sistema de reservas.\n";
                    break;
            default:cout << "\nOpción inválida. Por favor, ingrese una opción valida (presione una tecla para continuar).\n";
                    pauseConsole();
                    clearConsole();
                    break;
        }
    } while (menu != 0);

    return 0;
}

void TomarReserva(string &nombre, string &apellido, string &dni, Clase &claseVuelo, CodigoAero &origen, CodigoAero &destino) {
    int opcion,opcion2;

    clearConsole();
    cout << "Por favor ingrese los datos personales:\n";
    cout << "Nombre: ";
    getline (cin, nombre);
    //cin.ignore();
    clearConsole();
    cout << "Apellido: ";
    getline (cin, apellido);
    //cin.ignore();
    clearConsole();
    cout << "DNI: ";
    getline (cin, dni);
    //cin.ignore();
    clearConsole();
    cout << "Clase del vuelo (1-Primera, 2-Bussiness, 3-Economica): ";
    cin >> opcion;
    while (opcion < 1 || opcion > 3) {
        cout << "\nOpcion inválida. Por favor, ingrese una opción valida.\n";
        cout << "Clase del vuelo (1-Primera, 2-Bussiness, 3-Economica): ";
        cin >> opcion;
    }
    claseVuelo = IngresarClase(opcion);
    clearConsole();
    cout << "\nPor favor ingrese los datos del vuelo:\n";
    cout << "Origen (1-Bahia Blanca, 2-Buenos Aires, 3-San Carlos de Bariloche, 4-San Fernando de Valle de Catamarca, 5-Comodoro Rivadavia): ";
    cin >> opcion;
    while (opcion < 1 || opcion > 5) {
        cout << "\nOpcion inválida. Por favor, ingrese una opción valida.\n";
        cout << "Origen (1-Bahia Blanca, 2-Buenos Aires, 3-San Carlos de Bariloche, 4-San Fernando de Valle de Catamarca, 5-Comodoro Rivadavia): ";
        cin >> opcion;
    }
    origen = IngresarOrigen(opcion);
    clearConsole();
    cout << "Destino (1-Bahia Blanca, 2-Buenos Aires, 3-San Carlos de Bariloche, 4-San Fernando de Valle de Catamarca, 5-Comodoro Rivadavia): ";
    cin >> opcion2;
      
    while ((opcion2 < 1 || opcion2 > 5) || (opcion2 == opcion)) {
        if (opcion == opcion2) {
            cout << "\nOpcion inválida, No puede elegir el mismo Aeropuerto como destino y origen.\n";
            cout << "Destino (1-Bahia Blanca, 2-Buenos Aires, 3-San Carlos de Bariloche, 4-San Fernando de Valle de Catamarca, 5-Comodoro Rivadavia): ";
            cin >> opcion2;
        } else {
            cout << "\nOpcion inválida. Por favor, ingrese una opción valida.\n";
            cout << "Destino (1-Bahia Blanca, 2-Buenos Aires, 3-San Carlos de Bariloche, 4-San Fernando de Valle de Catamarca, 5-Comodoro Rivadavia): ";
            cin >> opcion2;
        }
    }

    destino = IngresarDestino(opcion2);
    clearConsole();
}




void Mostrarreserva(Clase clase, string dni, string nombre, string apellido, CodigoAero origen, CodigoAero destino) {
    clearConsole();
    cout << "\nClase: " << getClase(clase) << "\n";
    cout << "DNI: " << dni << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Apellido: " << apellido << "\n";
    cout << "Origen: " << getOrigen(origen) << "\n";
    cout << "Destino: " << getDestino(destino) << "\n";
    cout << endl;
}

string getClase(Clase clase) {
    switch(clase) {
        case PRIMERA: return "Primera";
        case BUSSINESS: return "Bussiness";
        case ECONOMICA: return "Economica";
        default: return "Desconocido";
    }
}

string getOrigen(CodigoAero origen) {
    switch(origen) {
        case BHI: return "Bahia Blanca";
        case AEP: return "Buenos Aires Aeroparque";
        case EPA: return "Buenos Aires El Palomar";
        case EZE: return "Buenos Aires Ezeiza";
        case BRC: return "San Carlos de Bariloche";
        case CTC: return "San Fernando de Valle de Catamarca";
        case CRD: return "Comodoro Rivadavia";
        default: return "Desconocido";
    }
}

string getDestino(CodigoAero destino) {
    switch(destino) {
        case BHI: return "Bahia Blanca";
        case AEP: return "Buenos Aires Aeroparque";
        case EPA: return "Buenos Aires El Palomar";
        case EZE: return "Buenos Aires Ezeiza";
        case BRC: return "San Carlos de Bariloche";
        case CTC: return "San Fernando de Valle de Catamarca";
        case CRD: return "Comodoro Rivadavia";
        default: return "Desconocido";
    }
}   



Clase IngresarClase(int opcion) {
    switch(opcion) {
        case 1: return PRIMERA;
        case 2: return BUSSINESS;
        case 3: return ECONOMICA;
        default: return ECONOMICA;
    }
}

CodigoAero IngresarOrigen(int opcion) {
    switch(opcion) {
        case 1: return BHI;
        case 2: return AEP;
        case 3: return BRC;
        case 4: return CTC;
        case 5: return CRD;
        default: return CTC;
    }
}

CodigoAero IngresarDestino(int opcion) {
    switch(opcion) {
        case 1: return BHI;
        case 2: return AEP;
        case 3: return BRC;
        case 4: return CTC;
        case 5: return CRD;
        default: return CTC;
    }
}

void pauseConsole() {
    std::cin.get();
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

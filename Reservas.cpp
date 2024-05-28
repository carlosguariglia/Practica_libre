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
#include <string.h>
#include <fstream>

using namespace std;

enum CodigoAero { BHI=1, AEP, EPA, EZE, BRC, CTC, CRD };
enum Clase { PRIMERA=1, BUSSINESS, ECONOMICA };


struct Reserva
{
    int IDreserva;
    string dni;
    string apellido;
    string nombre;
    Clase claseVuelo;
    CodigoAero origen;
    CodigoAero destino;
};

const int MAX = 100;

void TomarReserva(ifstream archive,Reserva reserva[], int max);


int main()
{   
   Reserva reserva[MAX];
   ifstream archivo;
   archivo.open("Reservas.txt");

   if (archivo.is_open())
   {    

        cout << "---------------------" << endl;
        cout << "REGISTRO DE RESERVAS" << endl;
        cout << "---------------------" << endl;
        int menu;
        do
        {
            cout << "1. Tomar Reserva" << endl;
            cout << "2. Mostrar Reservas" << endl;
            cout << "3. Actualizar una Reserva" << endl;
            cout << "4. Eliminar una Reserva" << endl;
            cout << "5. Buscar una Reserva" << endl;
            cout << "0. Guardar a Archivo y Salir" << endl;
            cout << "Opcion: ";
            cin >> menu;

            switch (menu)
            {
            case 1:
                cout << "------------------" << endl;
                cout << "Tomar Reserva" << endl;
                cout << "------------------" << endl;
                TomarReserva(archivo,reserva, MAX);
                break;
            case 2:
                cout << "Mostrar Reservas" << endl;
                break;
            case 0:
                cout << "Guardando..." << endl;
                break;
            }
            

        
        
        } while (menu !=0);



   } 
    else 
    {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    return 0;
}

void TomarReserva(ifstream archive,Reserva reserva[], int max)
{   
    
    int cantidad = 0;
    int opcion;
    
    archive >> reserva[0].IDreserva;
    
    for (int i = 0; i < max; i++)
    {
        if (reserva[i].IDreserva == -1)
        {
            cout << "------------------" << endl;
            cout << "Registrar Reserva" << endl;
            cout << "------------------" << endl;
            cout << "ID Reserva: " << endl;
            cin >> reserva[i].IDreserva;
            cout << "DNI: ";
            getline(cin, reserva[i].dni);
            cout << "Apellido: ";
            getline(cin, reserva[i].apellido);
            cout << "Nombre: ";
            getline(cin, reserva[i].nombre);
            cout << "Clase de Vuelo: ";
            cout << "Primera: 1, Bussiness: 2, Económica: 3";
            cin >> opcion;
            reserva[i].claseVuelo = static_cast<Clase>(opcion);
            cout << "Origen: ";
            cout << "Bahia Blanca: 1, Buenos Aires Aeroparque: 2, Buenos Aires El Palomar: 3, Buenos Aires Ezeiza: 4, San Carlos de Bariloche: 5, San Fernando del Valle de Catamarca: 6, Comodoro Rivadavia: 7";
            cin >> opcion;
            reserva[i].origen = static_cast<CodigoAero>(opcion);
            cout << "Destino: ";
            cout << "Bahia Blanca: 1, Buenos Aires Aeroparque: 2, Buenos Aires El Palomar: 3, Buenos Aires Ezeiza: 4, San Carlos de Bariloche: 5, San Fernando del Valle de Catamarca: 6, Comodoro Rivadavia: 7";
            cin >> opcion;
            reserva[i].destino = static_cast<CodigoAero>(opcion);
            cantidad++;
            break;  
        }
    }   
    if (cantidad == 0)
    {
        cout << "No se puede registrar ninguna reserva (Almacenamiento lleno o corrupto)" << endl;
    }
}

void MostrarReservas(const Reserva reserva[], int max)
{
    for (int i = 0; i < max; i++)
    {
        cout << "------------------" << endl;
        cout << "Reserva ID: " << reserva[i].IDreserva << endl;
        cout << "DNI: " << reserva[i].dni << endl;
        cout << "Apellido: " << reserva[i].apellido << endl;
        cout << "Nombre: " << reserva[i].nombre << endl;
        cout << "Clase de Vuelo: " << reserva[i].claseVuelo << endl;
        cout << "Origen: " << reserva[i].origen << endl;
        cout << "Destino: " << reserva[i].destino << endl;
        cout << "------------------" << endl;
    }
}
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

struct Reserva
{
    string dni;
    string apellido;
    string nombre;
    string clase;
    string origen;
    string destino;
};

const int MAX = 100;

int main()
{   
    Reserva reserva[MAX];
    ofstream archivo;
    archivo.open("reservas.txt", ios::app);

    for (int i = 0; i < MAX; i++)
    {
        cout << "DNI: ";
        cin >> reserva[i].dni;
        cout << "Apellido: ";
        cin >> reserva[i].apellido;
        cout << "Nombre: ";
        cin >> reserva[i].nombre;
        cout << "Clase: ";
        cin >> reserva[i].clase;
        cout << "Origen: ";
        cin >> reserva[i].origen;
        cout << "Destino: ";
        cin >> reserva[i].destino;
        cout << endl;
        archivo << reserva[i].dni << "," << reserva[i].apellido << "," << reserva[i].nombre << "," << reserva[i].clase << "," << reserva[i].origen << "," << reserva[i].destino << endl;
    }
    archivo.close();
    return 0;
}

    
#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>

using namespace std;

class Cliente
{
public:
    Cliente(string nombre, int numeroConfiramcion);

    void setNombre(string nombre);
    void setNumeroConfiramcion(long long numeroConfirmacion);
    void setHabitacion(string habitacion);
    void setEstadoReserva(string estadoReserva);

    string getNombre(){return this->nombre;}
    int getNumeroConfirmacion(){return this->numeroConfirmacion;}
    string getHabitacion(){return this->habitacion;}
    string getEstadoReserva(){return this->estadoReserva;}
    float getImporte();
    vector <pair <string, float> > getDesgloseGastos(){return this->desgloseGastos;}

    void AniadirGasto(string nombreServicio, float coste);

private:
    string nombre;
    long long numeroConfirmacion;
    string habitacion;
    string estadoReserva;
    vector < pair <string, float> > desgloseGastos;
    float importe;
};

#endif // CLIENTE_H

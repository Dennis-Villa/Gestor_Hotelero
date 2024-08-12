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
    void setNumeroConfiramcion(int numeroConfirmacion){this->numeroConfirmacion = numeroConfirmacion;}
    void setHabitacion(string habitacion){this->habitacion = habitacion;}
    void setEstadoReserva(string estadoReserva){this->estadoReserva = estadoReserva;}
    void setImporte(float importe){this->importe = importe;}

    string getNombre(){return this->nombre;}
    int getNumeroConfirmacion(){return this->numeroConfirmacion;}
    string getHabitacion(){return this->habitacion;}
    string getEstadoReserva(){return this->estadoReserva;}
    float getImporte(){return this->importe;}

    void AniadirGasto(string nombreServicio, float coste);

private:
    string nombre;
    int numeroConfirmacion;
    string habitacion;
    string estadoReserva;
    vector < pair <string, float> > desgloseGastos;
    float importe;
};

#endif // CLIENTE_H

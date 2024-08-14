#ifndef RESERVA_H
#define RESERVA_H

#include <string>
#include <vector>
#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"

using namespace std;

class Reserva
{
public:
    Reserva(long long numeroConfirmacion, Cliente *cliente, string estadoReserva = "Pendiente");
    Reserva(long long numeroConfirmacion, Cliente *cliente, Habitacion *habitacion, string estadoReserva = "Pendiente");

    void setNumeroConfiramcion(long long numeroConfirmacion);
    void setEstadoReserva(string estadoReserva);
    void setCliente(Cliente *cliente);
    void setHabitacion(Habitacion *habitacion);

    float getImporte();
    vector <pair <string, float> > getDesgloseGastos(){return this->desgloseGastos;}

    void registarEntrada();
    void registarSalida();

    void AniadirGasto(string nombreServicio, float coste);

private:
    long long numeroConfirmacion;
    string estadoReserva;
    vector < pair <string, float> > desgloseGastos;
    float importe;
    time_t fechaInicio;
    time_t fechaFin;
    Cliente *cliente;
    Habitacion *habitacion;
};

#endif // RESERVA_H

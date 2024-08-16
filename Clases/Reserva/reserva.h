#ifndef RESERVA_H
#define RESERVA_H

#include <QString>
#include <vector>
#include "stdexcept"
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"
#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"

using namespace std;

class Reserva
{
public:
    Reserva(long long numeroConfirmacion, Cliente *cliente, QString estadoReserva = "Pendiente");
    Reserva(long long numeroConfirmacion, Cliente *cliente, Habitacion *habitacion, QString estadoReserva = "Pendiente");

    void setNumeroConfiramcion(long long numeroConfirmacion);
    void setEstadoReserva(QString estadoReserva);
    void setCliente(Cliente *cliente);
    void setHabitacion(Habitacion *habitacion);

    float getImporte();
    vector <pair <QString, float> > getDesgloseGastos(){return this->desgloseGastos;}

    void registarEntrada();
    void registarSalida();

    void AniadirGasto(QString nombreServicio, float coste);

private:
    long long numeroConfirmacion;
    QString estadoReserva;
    vector < pair <QString, float> > desgloseGastos;
    float importe;
    time_t fechaInicio;
    time_t fechaFin;
    Cliente *cliente;
    Habitacion *habitacion;
};

#endif // RESERVA_H

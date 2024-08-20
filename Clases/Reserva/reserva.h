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
    Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString estadoReserva = "Pendiente");
    Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, Habitacion *habitacion, QString estadoReserva = "Pendiente");
    Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, int fechaInicio, int fechaFin,
            QString desgloseGastos, float importe, QString estadoReserva, Habitacion *habitacion = nullptr);

    void setNumeroConfiramcion(int numeroConfirmacion);
    void setCantidadNoches(int cantidadNoches);
    void setEstadoReserva(QString estadoReserva);
    void setCliente(Cliente *cliente);
    void setHabitacion(Habitacion *habitacion);

    int getNumeroConfirmacion(){return this->numeroConfirmacion;}
    int getFechaInicio(){return this->fechaInicio;}
    int getFechaFin(){return this->fechaFin;}
    float getImporte();
    vector <pair <QString, float> > getDesgloseGastos(){return this->desgloseGastos;}

    void registarEntrada();
    void registarSalida();

    void AniadirGasto(QString nombreServicio, float coste);

private:
    int numeroConfirmacion;
    QString estadoReserva;
    vector < pair <QString, float> > desgloseGastos;
    float importe;
    int cantidadNoches;
    time_t fechaInicio;
    time_t fechaFin;
    Cliente *cliente;
    Habitacion *habitacion;
};

#endif // RESERVA_H

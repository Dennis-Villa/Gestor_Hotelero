#ifndef RESERVA_H
#define RESERVA_H

#include <QString>
#include <QDate>
#include <vector>

#include "stdexcept"
#include "Archivos_Auxiliares/exception_reserva_vencida.h"
#include "Archivos_Auxiliares\Funciones_Auxiliares\Funciones_Auxiliares.h"
#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"

using namespace std;

class Reserva
{
public:
    Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString estadoReserva = "Pendiente");
    Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, Habitacion *habitacion, QString estadoReserva = "Pendiente");
    Reserva(int numeroConfirmacion, Cliente *cliente, QDate fechaInicio, QDate fechaFin, int cantidadNoches,
            float importe, QString estadoReserva, Habitacion *habitacion = nullptr);
    Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QDate fechaInicio, QDate fechaFin,
            QString desgloseGastos, float importe, QString estadoReserva, Habitacion *habitacion = nullptr);
    Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString fechaInicio, QString fechaFin,
            QString desgloseGastos, float importe, QString estadoReserva, Habitacion *habitacion = nullptr);

    void setNumeroConfiramcion(int numeroConfirmacion);
    void setCantidadNoches(int cantidadNoches);
    void setEstadoReserva(QString estadoReserva);
    void setCliente(Cliente *cliente);
    void setHabitacion(Habitacion *habitacion);

    int getNumeroConfirmacion(){return this->numeroConfirmacion;}
    QString getEstadoReserva(){return this->estadoReserva;}
    QDate getFechaInicio(){return this->fechaInicio;}
    QString getFechaInicioString();
    QString getFechaFinString();
    QDate getFechaFin(){return this->fechaFin;}
    int getCantidadNoches(){return this->cantidadNoches;}
    int getClienteID(){return this->cliente->getIdentificador();}
    QString getClienteNombre(){return this->cliente->getNombre();}
    Cliente *getCliente(){return this->cliente;}
    int getNumeroHabitacion();
    int getPisoHabitacion();
    Habitacion *getHabitacion();
    float getImporte();
    vector <pair <QString, float> > getDesgloseGastos(){return this->desgloseGastos;}
    QString getDesgloseGastosString();

    bool tieneHabitacion(){return (this->habitacion == nullptr ? false : true);}

    void registarEntrada();
    void registarSalida();

    void aniadirGasto(QString nombreServicio, float coste);
    void modificarGastoHabitacion(float gasto);
    QString convertirGastosATexto();

private:
    int numeroConfirmacion;
    QString estadoReserva;
    vector < pair <QString, float> > desgloseGastos;
    float importe;
    int cantidadNoches;
    QDate fechaInicio;
    QDate fechaFin;
    Cliente *cliente;
    Habitacion *habitacion;
};

#endif // RESERVA_H

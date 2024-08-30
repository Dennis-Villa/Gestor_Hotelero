#ifndef CONTROLADORBD_H
#define CONTROLADORBD_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QDate>
#include <QSqlError>
#include <vector>

#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"
#include "Clases/Reserva/reserva.h"

class ControladorBD
{
public:
    ControladorBD();
    ~ControladorBD();

    bool abreBD();

    Cliente* crearCliente(QString nombre, QString email, QString telefono, QString nacionalidad);
    Cliente* buscarCliente(int identificadorCliente);
    vector <Cliente> getClientes();
    Cliente* aniadirEstancia(Cliente *clienteAAniadir);
    void eliminarCliente(int identificadorCliente);


    Habitacion* crearHabitacion(int numero, QString tipo, int tamanio,
                                int numeroCamas, float costeNoche);
    Habitacion* buscarHabitacion(int numero);
    vector <Habitacion> getHabitaciones();
    Habitacion* cambiarEstadoHabitacion(Habitacion *habitacion);
    Habitacion* cambiarDisponibilidadHabitacion(int numero, bool disponible);
    Habitacion* cambiarEnArreglosHabitacion(int numero, bool enArreglos);
    void eliminarHabitacion(int numero);


    Reserva* crearReserva(QString estado, QDate inicio, QDate fin, int noches, int cliente,
                          float importe, int habitacion = -1);
    Reserva* buscarReserva(int numeroConfirmacion);
    vector <Reserva> getReservas();
    Reserva* cambiarEstadoReserva(int numeroConfirmacion, QString estado);
    Reserva* cambiarEstadoReserva(Reserva *reservaACambiar, QString estado);
    Reserva* aniadirGasto(int numeroConfirmacion, QString gasto, float importe);
    void eliminarReserva(int numeroConfirmacion);

private:
    QSqlDatabase bd;
};

#endif // CONTROLADORBD_H

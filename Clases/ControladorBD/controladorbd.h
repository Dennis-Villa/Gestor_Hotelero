#ifndef CONTROLADORBD_H
#define CONTROLADORBD_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
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
    Cliente* aniadirEstancia(int identificadorCliente);
    void eliminarCliente(int identificadorCliente);


    Habitacion* crearHabitacion(int numero, QString tipo, int tamanio,
                                int numeroCamas, float costeNoche);
    Habitacion* buscarHabitacion(int numero);
    vector <Habitacion> getHabitaciones();
    Habitacion* cambiarDisponibilidadHabitacion(int numero, bool disponible);
    Habitacion* cambiarEnArreglosHabitacion(int numero, bool enArreglos);
    void eliminarHabitacion(int numero);


    Reserva* crearReserva(QString estado, int noches, int cliente,
                                int habitacion = NULL);
    Reserva* buscarReserva(long long numeroConfirmacion);
    vector <Reserva> getReservas();
    Reserva* cambiarEstadoReserva(long long numeroConfirmacion, QString estado);
    void eliminarReserva(long long numeroConfirmacion);

private:
    QSqlDatabase bd;
};

#endif // CONTROLADORBD_H

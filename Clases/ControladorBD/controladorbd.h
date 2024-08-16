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

    Cliente* crearCliente(QString nombre, QString email, QString nacionalidad, QString telefono = "");
    Cliente* buscarCliente(int identificadorCliente);
    vector <Cliente> getClientes();
    Cliente* aniadirEstancia(int identificadorCliente);
    void eliminarCliente(int identificadorCliente);
    //void borrarCliente();






    // void limpiar_tabla_mercado();

private:
    QSqlDatabase bd;
};

#endif // CONTROLADORBD_H
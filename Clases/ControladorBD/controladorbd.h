#ifndef CONTROLADORBD_H
#define CONTROLADORBD_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <vector>
#include <stdexcept>

#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"
#include "Clases/Reserva/reserva.h"

class ControladorBD
{
public:
    ControladorBD();
    ~ControladorBD();

    bool abreBD();

    Cliente* crearCliente(QString nombre, QString nacionalidad);
    Cliente* buscarCliente(int identificadorCliente);
    vector <Cliente> getClientes();
    Cliente* aniadirEstancia(int identificadorCliente);
    //void borrarCliente();






    // void limpiar_tabla_mercado();

private:
    QSqlDatabase bd;
};

#endif // CONTROLADORBD_H

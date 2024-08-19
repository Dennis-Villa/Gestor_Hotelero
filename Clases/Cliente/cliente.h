#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

using namespace std;

class Cliente
{
public:
    Cliente(long long identificador, QString nombre, QString email, QString nacionalidad, QString telefono = NULL);
    Cliente(long long identificador, QString nombre, QString email, QString nacionalidad, int cantidadEstancias, QString telefono = NULL);

    void setIdentificador(long long identificador);
    void setNombre(QString nombre);
    void setEmail(QString email);
    void setNacionalidad(QString nacionalidad);
    void setCantidadEstancias(int cantidadEstancias);
    void setTelefono(QString telefono);

    long long  getIdentificador(){return this->identificador;}
    QString getNombre(){return this->nombre;}
    QString getEmail(){return this->email;}
    QString getNacionalidad(){return this->nacionalidad;}
    int getCanidadEstancias(){return this->cantidadEstancias;}
    QString getTelefono(){return this->telefono;}

    void aniadirEstancia(){this->cantidadEstancias++;}

private:
    long long identificador;
    QString nombre;
    QString email;
    QString nacionalidad;
    int cantidadEstancias;
    QString telefono;
};

#endif // CLIENTE_H

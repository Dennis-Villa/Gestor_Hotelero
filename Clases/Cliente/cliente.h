#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

using namespace std;

class Cliente
{
public:
    Cliente(long long identificador, QString nombre, QString email, QString nacionalidad, QString telefono = "", int cantidadEstancias = 0);

    void setIdentificador(long long identificador);
    void setNombre(QString nombre);
    void setEmail(QString email);
    void setTelefono(QString telefono);
    void setNacionalidad(QString nacionalidad);
    void setCantidadEstancias(int cantidadEstancias);

    long long  getIdentificador(){return this->identificador;}
    QString getNombre(){return this->nombre;}
    QString getEmail(){return this->email;}
    QString getTelefono(){return this->telefono;}
    int getCanidadEstancias(){return this->cantidadEstancias;}

    void aniadirEstancia(){this->cantidadEstancias++;}

private:
    long long identificador;
    QString nombre;
    QString email;
    QString telefono;
    QString nacionalidad;
    int cantidadEstancias;
};

#endif // CLIENTE_H

#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include <vector>
#include <stdexcept>
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

using namespace std;

class Cliente
{
public:
    Cliente(long long identificador, QString nombre, QString nacionalidad, int cantidadEstancias = 0);

    void setNombre(QString nombre);
    void setIdentificador(long long identificador);
    void setNacionalidad(QString nacionalidad);
    void setCantidadEstancias(int cantidadEstancias);

    QString getNombre(){return this->nombre;}
    long long  getIdentificador(){return this->identificador;}
    int getCanidadEstancias(){return this->cantidadEstancias;}

    void aniadirEstancia(){this->cantidadEstancias++;}

private:
    long long identificador;
    QString nombre;
    QString nacionalidad;
    int cantidadEstancias;
};

#endif // CLIENTE_H

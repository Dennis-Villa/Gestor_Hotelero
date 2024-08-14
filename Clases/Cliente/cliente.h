#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

using namespace std;

class Cliente
{
public:
    Cliente(long long identificador, string nombre, string nacionalidad);

    void setNombre(string nombre);
    void setIdentificador(long long identificador);
    void setNacionalidad(string nacionalidad);

    string getNombre(){return this->nombre;}
    long long  getIdentificador(){return this->identificador;}
    int getCanidadEstancias(){return this->cantidadEstancias;}

    void aniadirEstancia(){this->cantidadEstancias++;}

private:
    long long identificador;
    string nombre;
    string nacionalidad;
    int cantidadEstancias;
};

#endif // CLIENTE_H

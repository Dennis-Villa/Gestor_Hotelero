#include "cliente.h"
#include <stdexcept>
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

Cliente::Cliente(long long identificador, string nombre, string nacionalidad)
{
    this->setIdentificador(identificador);
    this->setNombre(nombre);
    this->setNacionalidad(nacionalidad);

    this->cantidadEstancias = 0;
}

void Cliente::setNombre(string nombre)
{
    if (nombre.empty())
        throw invalid_argument("El nombre no puede estar vacío.");

    if (!soloLetras(nombre))
        throw invalid_argument("El nombre solo puede contener letras y espacios.");

    vector <string> nombreSeparado = stringSplit(nombre, ' ');

    if (nombreSeparado.size() == 1)
        throw invalid_argument("Se necesita al menos un apellido.");

    this->nombre = nombre;
}

void Cliente::setIdentificador(long long identificador)
{
    if (identificador < 0)
        throw invalid_argument("El identificador no puede ser negativo.");

    this->identificador = identificador;
}

void Cliente::setNacionalidad(string nacionalidad)
{
    if (nacionalidad.empty())
        throw invalid_argument("La nacionalidad no puede estar vacía.");

    this->nacionalidad = nacionalidad;
}

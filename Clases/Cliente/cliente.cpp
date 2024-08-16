#include "cliente.h"

#include <vector>
#include <stdexcept>

#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

Cliente::Cliente(long long identificador, QString nombre, QString email, QString nacionalidad, QString telefono, int cantidadEstancias)
{
    this->setIdentificador(identificador);
    this->setNombre(nombre);
    this->setEmail(email);
    this->setTelefono(telefono);
    this->setNacionalidad(nacionalidad);
    this->setCantidadEstancias(cantidadEstancias);
}

void Cliente::setNombre(QString nombre)
{
    if (nombre.isEmpty())
        throw invalid_argument("El nombre no puede estar vacío.");

    if (!soloLetras(nombre))
        throw invalid_argument("El nombre solo puede contener letras y espacios.");

    vector <QString> nombreSeparado = stringSplit(nombre, ' ');

    if (nombreSeparado.size() == 1)
        throw invalid_argument("Se necesita al menos un apellido.");

    this->nombre = nombre;
}

void Cliente::setEmail(QString email)
{
    if (email.isEmpty())
        throw invalid_argument("El email no puede estar vacío.");

    if (!email.contains('@') || !email.contains('.'))
        throw invalid_argument("El email no tiene un formato correcto.");

    this->email = email;
}

void Cliente::setTelefono(QString telefono)
{
    if (telefono.length() != 0 && contarDigitosTelefono(telefono) != 9)
        throw invalid_argument("El teléfono debe tener 9 digitos.");

    this->telefono = telefono;
}

void Cliente::setIdentificador(long long identificador)
{
    if (identificador < 0)
        throw invalid_argument("El identificador no puede ser negativo.");

    this->identificador = identificador;
}

void Cliente::setNacionalidad(QString nacionalidad)
{
    if (nacionalidad.isEmpty())
        throw invalid_argument("La nacionalidad no puede estar vacía.");

    this->nacionalidad = nacionalidad;
}

void Cliente::setCantidadEstancias(int cantidadEstancias)
{
    if (cantidadEstancias < 0)
        throw invalid_argument("La cantidad de estancias no puede ser negativa.");

    this->cantidadEstancias = cantidadEstancias;
}

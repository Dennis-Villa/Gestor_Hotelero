#include "habitacion.h"

Habitacion::Habitacion(QString numeroHabitacion, QString tipoHabitacion, int tamanioM2, int numeroCamas, float costePorNoche)
{
    this->setNumeroHabitacion(numeroHabitacion);
    this->setTipoHabitacion(tipoHabitacion);
    this->setTamanioM2(tamanioM2);
    this->setNumeroCamas(numeroCamas);
    this->setCostePorNoche(costePorNoche);

    this->disponible = true;
    this->enArreglos = false;

    this->piso = this->numeroHabitacion[0].digitValue();
}

void Habitacion::setNumeroHabitacion(QString numeroHabitacion)
{
    if (numeroHabitacion.length() == 0)
        throw invalid_argument("El numero de la habitacion no puede estar vacío.");

    this->numeroHabitacion = numeroHabitacion;
    this->piso = this->numeroHabitacion[0].digitValue();
}

void Habitacion::setTipoHabitacion(QString tipoHabitacion)
{
    if (tipoHabitacion.length() == 0)
        throw invalid_argument("El tipo de la habitacion no puede estar vacío.");

    if (!tipoHabitacionValido(tipoHabitacion))
        throw invalid_argument("El tipo de la habitación no es un tipo válido.");

    this->tipoHabitacion = tipoHabitacion;
}

void Habitacion::setTamanioM2(int tamanioM2)
{
    if (tamanioM2 <= 0)
        throw invalid_argument("El tamaño de la habitación debe ser positivo.");

    this->tamanioM2 = tamanioM2;
}

void Habitacion::setNumeroCamas(int numeroCamas)
{
    if (numeroCamas <= 0)
        throw invalid_argument("El número de camas de la habitación debe ser positivo.");

    this->numeroCamas = numeroCamas;
}

void Habitacion::setCostePorNoche(float costePorNoche)
{
    if (costePorNoche < 0)
        throw invalid_argument("El coste por noche de la habitación no puede ser negativo.");

    this->costePorNoche = costePorNoche;
}

void Habitacion::setDisponible(bool disponible)
{
    if (disponible && this->enArreglos)
        throw logic_error("No puede ponerse como disponible una habitación en arreglo.");

    this->disponible = disponible;
}

void Habitacion::setEnArreglos(bool enArreglos)
{
    if (enArreglos)
        this->disponible = false;

    this->enArreglos = enArreglos;
}

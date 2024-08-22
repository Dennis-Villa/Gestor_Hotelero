#include "habitacion.h"

Habitacion::Habitacion(int numeroHabitacion, QString tipoHabitacion, int tamanioM2, int numeroCamas, float costePorNoche)
{
    this->setNumeroHabitacion(numeroHabitacion);
    this->setTipoHabitacion(tipoHabitacion);
    this->setTamanioM2(tamanioM2);
    this->setNumeroCamas(numeroCamas);
    this->setCostePorNoche(costePorNoche);
    this->setEnArreglos(false);
    this->setDisponible(true);

    this->piso = this->numeroHabitacion / 100;
    this->numero = this->numeroHabitacion % 100;
}

Habitacion::Habitacion(int numeroHabitacion, QString tipoHabitacion, int tamanioM2, int numeroCamas, float costePorNoche, bool disponible, bool enArreglos)
{
    this->setNumeroHabitacion(numeroHabitacion);
    this->setTipoHabitacion(tipoHabitacion);
    this->setTamanioM2(tamanioM2);
    this->setNumeroCamas(numeroCamas);
    this->setCostePorNoche(costePorNoche);
    this->setEnArreglos(enArreglos);
    this->setDisponible(disponible);

    this->piso = this->numeroHabitacion / 100;
    this->numero = this->numeroHabitacion % 100;
}

void Habitacion::setNumeroHabitacion(int numeroHabitacion)
{
    if (numeroHabitacion < 0)
        throw invalid_argument("El numero de la habitación no puede ser negativo.");

    if (numeroHabitacion < 100)
        throw invalid_argument("La habitación debe estar al menos en el primer piso.");

    this->numeroHabitacion = numeroHabitacion;
    this->piso = this->numeroHabitacion / 100;
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

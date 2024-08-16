#include "reserva.h"

Reserva::Reserva(long long numeroConfirmacion, Cliente *cliente, QString estadoReserva)
{
    this->setNumeroConfiramcion(numeroConfirmacion);
    this->setEstadoReserva(estadoReserva);
    this->setCliente(cliente);
    this->habitacion = nullptr;

    this->fechaInicio = 0;
    this->fechaFin = 0;
}

Reserva::Reserva(long long numeroConfirmacion, Cliente *cliente, Habitacion *habitacion, QString estadoReserva)
{
    this->setNumeroConfiramcion(numeroConfirmacion);
    this->setEstadoReserva(estadoReserva);
    this->setCliente(cliente);
    this->setHabitacion(habitacion);

    this->fechaInicio = 0;
    this->fechaFin = 0;
}

void Reserva::setNumeroConfiramcion(long long numeroConfirmacion)
{
    if (numeroConfirmacion <= 0)
        throw invalid_argument("El número de confirmación debe ser positivo");

    if ((numeroConfirmacion < 10000000000ll) || (numeroConfirmacion > 99999999999ll))
        throw invalid_argument("El número de confirmación debe ser de 11 cifras");

    this->numeroConfirmacion = numeroConfirmacion;
}

void Reserva::setEstadoReserva(QString estadoReserva)
{
    if (estadoReserva.isEmpty())
        throw invalid_argument("El estado de la reserva no puede estar vacío");

    if (!estadoReservaValido(estadoReserva))
        throw invalid_argument("El estado de la reserva no es un estado válido");

    this->estadoReserva = estadoReserva;
}

void Reserva::setCliente(Cliente *cliente)
{
    if (cliente == nullptr)
        throw invalid_argument("El cliente no puede ser un puntero nulo.");

    this->cliente = cliente;
}

void Reserva::setHabitacion(Habitacion *habitacion)
{
    if (habitacion == nullptr)
        throw invalid_argument("La habitación no puede ser un puntero nulo.");

    if (!habitacion->getDisponible())
        throw logic_error("La habitación no está disponible.");

    this->habitacion = habitacion;
    this->habitacion->setDisponible(false);
}

float Reserva::getImporte()
{
    float gastoTotal = 0;

    for (int i = 0; i < (int)this->desgloseGastos.size(); i++)
    {
        gastoTotal += this->desgloseGastos[i].second;
    }

    if (this->importe != gastoTotal)
        throw logic_error("El importe no coincide con el total de gastos.");

    return this->importe;
}

void Reserva::registarEntrada()
{
    this->setEstadoReserva("En Estadía");
    this->cliente->aniadirEstancia();

    this->fechaInicio = time(0);
}

void Reserva::registarSalida()
{
    this->setEstadoReserva("Estancia Finalizada");
    this->fechaFin = time(0);
}

void Reserva::AniadirGasto(QString nombreServicio, float coste)
{
    if (nombreServicio.isEmpty())
        throw invalid_argument("El nombre del servicio no puede estar vacío");

    if (coste < 0)
        throw invalid_argument("El coste del servicio no puede ser negativo");

    float costeDosDecimales = importeMaximoDecimales(coste);

    this->desgloseGastos.push_back({nombreServicio, costeDosDecimales});
    this->importe += costeDosDecimales;
}

#include "reserva.h"

Reserva::Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString estadoReserva)
{
    this->setNumeroConfiramcion(numeroConfirmacion);
    this->setCliente(cliente);
    this->setCantidadNoches(cantidadNoches);

    this->fechaInicio.setDate(1970, 1, 1);
    this->fechaFin.setDate(1970, 1, 1);

    this->setEstadoReserva(estadoReserva);
    this->setHabitacion(nullptr);
}

Reserva::Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, Habitacion *habitacion, QString estadoReserva)
{
    this->setNumeroConfiramcion(numeroConfirmacion);
    this->setCliente(cliente);
    this->setCantidadNoches(cantidadNoches);

    this->fechaInicio.setDate(1970, 1, 1);
    this->fechaFin.setDate(1970, 1, 1);

    this->setEstadoReserva(estadoReserva);
    this->setHabitacion(habitacion);
}

Reserva::Reserva(int numeroConfirmacion, Cliente *cliente, QDate fechaInicio, QDate fechaFin, int cantidadNoches, float importe, QString estadoReserva, Habitacion *habitacion)
{
    this->setNumeroConfiramcion(numeroConfirmacion);
    this->setCliente(cliente);
    this->setCantidadNoches(cantidadNoches);

    this->fechaInicio = fechaInicio;
    this->fechaFin = fechaFin;

    this->setEstadoReserva(estadoReserva);
    this->setHabitacion(habitacion);

    this->AniadirGasto("Reserva",importe);
}

Reserva::Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QDate fechaInicio, QDate fechaFin, QString desgloseGastos, float importe, QString estadoReserva, Habitacion *habitacion)
{
    this->setNumeroConfiramcion(numeroConfirmacion);
    this->setCliente(cliente);
    this->setCantidadNoches(cantidadNoches);

    this->fechaInicio = fechaInicio;
    this->fechaFin = fechaFin;

    this->setEstadoReserva(estadoReserva);
    this->setHabitacion(habitacion);

    this->desgloseGastos = stringGastosToVector(desgloseGastos);
    this->importe = importe;
}

Reserva::Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString fechaInicio, QString fechaFin, QString desgloseGastos, float importe, QString estadoReserva, Habitacion *habitacion)
{
    this->setNumeroConfiramcion(numeroConfirmacion);
    this->setCliente(cliente);
    this->setCantidadNoches(cantidadNoches);

    this->fechaInicio = QDate::fromString(fechaInicio);
    this->fechaFin = QDate::fromString(fechaFin);

    this->setEstadoReserva(estadoReserva);
    this->setHabitacion(habitacion);

    this->desgloseGastos = stringGastosToVector(desgloseGastos);
    this->importe = importe;
}

void Reserva::setNumeroConfiramcion(int numeroConfirmacion)
{
    if (numeroConfirmacion <= 0)
        throw invalid_argument("El número de confirmación debe ser positivo");

    this->numeroConfirmacion = numeroConfirmacion;
}

void Reserva::setCantidadNoches(int cantidadNoches)
{
    if (cantidadNoches < 1)
        throw invalid_argument("La cantidad de noches debe ser positiva.");

    this->cantidadNoches = cantidadNoches;
}

void Reserva::setEstadoReserva(QString estadoReserva)
{
    if (estadoReserva.isEmpty())
        throw invalid_argument("El estado de la reserva no puede estar vacío.");

    if (!estadoReservaValido(estadoReserva))
        throw invalid_argument("El estado de la reserva no es un estado válido.");

    if (estadoReserva == "Confirmado")
    {
        if(this->fechaInicio.year() == 1970)
            throw invalid_argument("La reserva confirmada debe tener una fecha de inicio.");

        if(this->fechaInicio < QDate::currentDate())
            throw invalid_argument("La reserva confirmada no puede tener una fecha de inicio pasada.");
    }

    if (estadoReserva == "En Estadía")
        this->registarEntrada();

    if (estadoReserva == "Estancia Finalizada")
        this->registarSalida();

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
    if(this->estadoReserva == "En Estadía" || this->estadoReserva == "Estancia Finalizada")
    {
        if (habitacion == nullptr)
            throw invalid_argument("La habitación no puede ser un puntero nulo.");

        this->habitacion = habitacion;
        this->habitacion->setDisponible(false);
    }

    else if (habitacion != nullptr)
    {
        if (this->estadoReserva == "En estadía" && !habitacion->getDisponible())
            throw logic_error("La habitación no está disponible.");

        this->habitacion = habitacion;
        this->habitacion->setDisponible(false);
    }

    else
        this->habitacion = nullptr;
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
    this->fechaInicio = QDate::currentDate();
    this->fechaFin = this->fechaInicio.addDays(this->cantidadNoches);
}

void Reserva::registarSalida()
{
    this->cliente->aniadirEstancia();
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

QString Reserva::convertirGastosAString()
{
    QString gastosString = "";

    for (pair <QString, float> gasto: this->desgloseGastos)
    {
        gastosString += "{" + gasto.first + ",";
        gastosString += QString::number(gasto.second) + "}" + ",";
    }

    return gastosString;
}

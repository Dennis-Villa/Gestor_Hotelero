#include "cliente.h"
#include <stdexcept>
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

Cliente::Cliente(string nombre, int numeroConfirmacion)
{
    this->setNombre(nombre);
    this->setNumeroConfiramcion(numeroConfirmacion);

    this->habitacion = "N/A";
    this->estadoReserva = "Pendiente";
    this->importe = 0;
}

void Cliente::setNombre(string nombre)
{
    if (nombre.empty())
        throw invalid_argument("El nombre no puede estar vacío");

    if (!soloLetras(nombre))
        throw invalid_argument("El nombre solo puede contener letras y espacios");

    vector <string> nombreSeparado = stringSplit(nombre, ' ');

    if (nombreSeparado.size() == 1)
        throw invalid_argument("Se necesita al menos un apellido");

    this->nombre = nombre;
}

void Cliente::setNumeroConfiramcion(long long numeroConfirmacion)
{
    if (numeroConfirmacion <= 0)
        throw invalid_argument("El número de confirmación debe ser positivo");

    if ((numeroConfirmacion < 10000000000ll) || (numeroConfirmacion > 99999999999ll))
        throw invalid_argument("El número de confirmación debe ser de 11 cifras");

    this->numeroConfirmacion = numeroConfirmacion;
}

void Cliente::setHabitacion(string habitacion)
{
    if (habitacion.empty())
        throw invalid_argument("La habitación no puede ser una cadena vacía");

    this->habitacion = habitacion;
}

void Cliente::setEstadoReserva(string estadoReserva)
{
    if (estadoReserva.empty())
        throw invalid_argument("El estado de la reserva no puede estar vacío");

    if (!estadoReservaValido(estadoReserva))
        throw invalid_argument("El estado de la reserva no es un estado válido");

    this->estadoReserva = estadoReserva;
}

float Cliente::getImporte()
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

void Cliente::AniadirGasto(string nombreServicio, float coste)
{
    if (nombreServicio.empty())
        throw invalid_argument("El nombre del servicio no puede estar vacío");

    if (coste < 0)
        throw invalid_argument("El coste del servicio no puede ser negativo");

    float costeDosDecimales = importeMaximoDecimales(coste);

    this->desgloseGastos.push_back({nombreServicio, costeDosDecimales});
    this->importe += costeDosDecimales;
}

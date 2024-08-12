#include "cliente.h"
#include <stdexcept>
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

Cliente::Cliente(string nombre, int numeroConfirmacion)
{
    this->setNombre(nombre);
    this->setNumeroConfiramcion(numeroConfirmacion);

    this->habitacion = "N/A";
    this->estadoReserva = "Pending";
    this->importe = 0;
}

void Cliente::setNombre(string nombre)
{
    if (nombre.empty())
    {
        throw invalid_argument("El nombre no puede estar vacío");
    }

    //string nombreSeparado[] = ;
}

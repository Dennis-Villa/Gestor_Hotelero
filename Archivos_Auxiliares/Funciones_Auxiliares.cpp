#include "Funciones_Auxiliares.h"

vector <string> stringSplit(string cadena, char separador)
{
    vector <string> subCadenas;
    int posicionInicio = 0;

    for (int i = 0; i < (int)cadena.length(); i++)
    {
        if (cadena[i] == separador)
        {
            string subCadena = cadena.substr(posicionInicio, i - posicionInicio);

            if (!subCadena.empty())
                subCadenas.push_back(subCadena);

            posicionInicio = i + 1;
        }

        else if (i == (int)cadena.length() - 1)
        {
            subCadenas.push_back(cadena.substr(posicionInicio, i + 1 - posicionInicio));
        }
    }

    return subCadenas;
}


bool soloLetras(string cadena)
{
    for (char letra: cadena)
    {
        bool esMinuscula = (letra >= 'a' && letra <= 'z');
        bool esMayuscula = (letra >= 'A' && letra <= 'Z');

        if (letra != ' ' && !esMinuscula && !esMayuscula)
            return false;
    }

    return true;
}

bool estadoReservaValido(string estadoReserva)
{
    string estadosValidos[] = {"Pendiente", "Confirmado",
                               "En Estadía", "Estancia Finalizada"};

    for (string estado: estadosValidos)
    {
        if (estadoReserva == estado)
            return true;
    }

    return false;
}

float importeMaximoDecimales(float importe)
{
    float importeDosDecimales = (int)(importe * 100);

    return (float)importeDosDecimales / 100.0;
}

bool tipoHabitacionValido(string tipoHabitacion)
{
    string tiposValidos[] = {"Estandar", "Premium", "Suit"};

    for (string tipo: tiposValidos)
    {
        if (tipoHabitacion == tipo)
            return true;
    }

    return false;
}

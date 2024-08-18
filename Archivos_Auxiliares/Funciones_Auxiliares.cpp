#include "Funciones_Auxiliares.h"

vector <QString> stringSplit(QString cadena, char separador)
{
    vector <QString> subCadenas;
    int posicionInicio = 0;

    for (int i = 0; i < (int)cadena.length(); i++)
    {
        if (cadena[i] == separador)
        {
            QString subCadena = cadena.mid(posicionInicio, i - posicionInicio);

            if (!subCadena.length() == 0)
                subCadenas.push_back(subCadena);

            posicionInicio = i + 1;
        }

        else if (i == (int)cadena.length() - 1)
        {
            subCadenas.push_back(cadena.mid(posicionInicio, i + 1 - posicionInicio));
        }
    }

    return subCadenas;
}


bool soloLetras(QString cadena)
{
    for (QChar letra: cadena)
    {
        bool esMinuscula = (letra >= 'a' && letra <= 'z');
        bool esMayuscula = (letra >= 'A' && letra <= 'Z');

        if (letra != ' ' && !esMinuscula && !esMayuscula)
            return false;
    }

    return true;
}

bool estadoReservaValido(QString estadoReserva)
{
    QString estadosValidos[] = {"Pendiente", "Confirmado",
                               "En Estadía", "Estancia Finalizada"};

    for (QString estado: estadosValidos)
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

bool tipoHabitacionValido(QString tipoHabitacion)
{
    QString tiposValidos[] = {"Estandar", "Premium", "Suit"};

    for (QString tipo: tiposValidos)
    {
        if (tipoHabitacion == tipo)
            return true;
    }

    return false;
}

int contarDigitos(QString cadenaAlfanumerica)
{
    int cantidadDigitos = 0;

    for (QChar caracter: cadenaAlfanumerica)
    {
        if (caracter >= '0' && caracter <= '9')
            cantidadDigitos++;
    }

    return cantidadDigitos;
}

vector<pair<QString, float> > stringGastosToVector(QString desgloseGastos)
{
    vector<pair<QString, float> > vectorGastos;

    if (desgloseGastos.isEmpty())
        return vectorGastos;

    int posicionInicial = 0;
    int posicionApertura = desgloseGastos.indexOf('{', posicionInicial);
    int posicionCierre = desgloseGastos.indexOf('}', posicionInicial);

    do
    {
        QString cadenaPar = desgloseGastos.mid(posicionApertura + 1, posicionCierre - posicionApertura - 1);
        QStringList par = cadenaPar.split(',');

        vectorGastos.push_back({par[0], par[1].toFloat()});

        posicionInicial = posicionCierre + 1;
        posicionApertura = desgloseGastos.indexOf('{', posicionInicial);
        posicionCierre = desgloseGastos.indexOf('}', posicionInicial);
    }
    while (posicionApertura != -1);

    return vectorGastos;
}

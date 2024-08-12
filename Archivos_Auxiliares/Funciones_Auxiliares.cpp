#include "Funciones_Auxiliares.h"

vector <string> stringSplit(string cadena, string separador)
{
    vector <string> subCadenas;
    int posicionInicio = 0;

    for (int i = 0; i < (int)cadena.length(); i++)
    {
        for (int j = 0; j < (int)separador.length(); j++)
        {
            if (cadena[i+j] != separador[j])
                break;

            if (j == (int)separador.length() -1 && i > posicionInicio)
            {
                subCadenas.push_back(cadena.substr(posicionInicio, i));
                posicionInicio = i + j + 1;
                i = i + j;
            }
        }
    }

    return subCadenas;
}

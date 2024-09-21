#ifndef FUNCIONES_AUXILIARES_H
#define FUNCIONES_AUXILIARES_H

#include <QString>
#include <QStringList>
#include <vector>

using namespace std;

vector <QString> stringSplit(QString cadena, char separador);
bool soloLetras(QString cadena);
bool estadoReservaValido(QString estadoReserva);
float importeMaximoDecimales(float importe);
bool tipoHabitacionValido(QString tipoHabitacion);
int contarDigitos(QString cadenaAlfanumerica);
vector < pair <QString, float> > stringGastosToVector(QString desgloseGastos);

#endif FUNCIONES_AUXILIARES_H

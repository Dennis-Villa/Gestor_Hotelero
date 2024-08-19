#ifndef HABITACION_H
#define HABITACION_H

#include <QString>
#include <stdexcept>
#include "Archivos_Auxiliares/Funciones_Auxiliares.h"

using namespace std;

class Habitacion
{
public:
    Habitacion(int numeroHabitacion, QString tipoHabitacion,
               int tamanioM2, int numeroCamas, float costePorNoche);
    Habitacion(int numeroHabitacion, QString tipoHabitacion, int tamanioM2,
               int numeroCamas, float costePorNoche, bool disponible, bool enArreglos);

    void setNumeroHabitacion(int numeroHabitacion);
    void setTipoHabitacion(QString tipoHabitacion);
    void setTamanioM2(int tamanioM2);
    void setNumeroCamas(int numeroCamas);
    void setCostePorNoche(float costePorNoche);
    void setDisponible(bool disponible);
    void setEnArreglos(bool enArreglos);

    int getNumeroHabitacion(){return this->numeroHabitacion;}
    QString getTipoHabitacion(){return this->tipoHabitacion;}
    int getPiso(){return this->piso;}
    int getTamanioM2(){return this->tamanioM2;}
    int getNumeroCamas(){return this->numeroCamas;}
    float getCostePorNoche(){return this->costePorNoche;}
    bool getDisponible(){return this->disponible;}
    bool getEnArreglos(){return this->enArreglos;}

private:
    int numeroHabitacion;
    QString tipoHabitacion;
    int piso;
    int tamanioM2;
    int numeroCamas;
    float costePorNoche;
    bool disponible;
    bool enArreglos;
};

#endif // HABITACION_H

#ifndef HABITACION_H
#define HABITACION_H

#include <string>

using namespace std;

class Habitacion
{
public:
    Habitacion(string numeroHabitacion, string tipoHabitacion,
               int tamanioM2, int numeroCamas, float costePorNoche);

    void setNumeroHabitacion(string numeroHabitacion);
    void setTipoHabitacion(string tipoHabitacion);
    void setTamanioM2(int tamanioM2);
    void setNumeroCamas(int numeroCamas);
    void setCostePorNoche(float costePorNoche);
    void setDisponible(bool disponible);
    void setEnArreglos(bool enArreglos);

    string getNumeroHabitacion(){return this->numeroHabitacion;}
    string getTipoHabitacion(){return this->tipoHabitacion;}
    int getPiso(){return this->piso;}
    int getTamanioM2(){return this->tamanioM2;}
    int getNumeroCamas(){return this->numeroCamas;}
    float getCostePorNoche(){return this->costePorNoche;}
    bool getDisponible(){return this->disponible;}
    bool getEnArreglos(){return this->enArreglos;}

private:
    string numeroHabitacion;
    string tipoHabitacion;
    int piso;
    int tamanioM2;
    int numeroCamas;
    float costePorNoche;
    bool disponible;
    bool enArreglos;
};

#endif // HABITACION_H

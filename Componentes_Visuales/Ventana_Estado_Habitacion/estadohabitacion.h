#ifndef ESTADOHABITACION_H
#define ESTADOHABITACION_H

#include <QDialog>
#include <QMessageBox>
#include <vector>

#include "Clases/Habitacion/habitacion.h"
#include "Clases/ControladorBD/controladorbd.h"

namespace Ui {
class EstadoHabitacion;
}

class EstadoHabitacion : public QDialog
{
    Q_OBJECT

public:
    explicit EstadoHabitacion(vector<Habitacion> *habitaciones, ControladorBD *controladorBD, QWidget *parent = nullptr);
    ~EstadoHabitacion();

    void setHabitacion(int numeroHabitacion);

    void mostrar();
    void limpiar();

public slots:
    void cerrar();
    void modificar();

private:
    Ui::EstadoHabitacion *ui;

    vector<Habitacion> *habitaciones;
    int numeroHabitacion;
    ControladorBD *controladorBD;
};

#endif // ESTADOHABITACION_H

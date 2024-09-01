#ifndef ESTADOHABITACION_H
#define ESTADOHABITACION_H

#include <QDialog>
#include <QMessageBox>

#include "Clases/Habitacion/habitacion.h"
#include "Clases/ControladorBD/controladorbd.h"

namespace Ui {
class EstadoHabitacion;
}

class EstadoHabitacion : public QDialog
{
    Q_OBJECT

public:
    explicit EstadoHabitacion(ControladorBD *controladorBD, QWidget *parent = nullptr);
    ~EstadoHabitacion();

    void setHabitacion(Habitacion *habitacion);

    void mostrar();
    void limpiar();

signals:
    void actualizar(bool = false);

public slots:
    void cerrar();
    void modificar();

private:
    Ui::EstadoHabitacion *ui;

    Habitacion *habitacion;
    ControladorBD *controladorBD;
};

#endif // ESTADOHABITACION_H

#ifndef ANIADIRHABITACION_H
#define ANIADIRHABITACION_H

#include <QDialog>
#include <QString>
#include <vector>

#include <QMessageBox>
#include "Clases/Habitacion/habitacion.h"
#include "Clases/ControladorBD/controladorbd.h"

namespace Ui {
class AniadirHabitacion;
}

class AniadirHabitacion : public QDialog
{
    Q_OBJECT

public:
    explicit AniadirHabitacion(vector<Habitacion> *habitaciones, QWidget *parent = nullptr, ControladorBD  *controladorBD = nullptr);
    ~AniadirHabitacion();

    void abrirVentana();
    void limpiarVentana();

signals:
    void cerrarVentana(bool cerrar = false);
    void aniadido(bool actualizar = false);

private slots:
    void aniadirHabitacion();

    void cerrar();

private:
    Ui::AniadirHabitacion *ui;

    vector<Habitacion> *habitaciones;
    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // ANIADIRHABITACION_H

#ifndef ANIADIRRESERVA_H
#define ANIADIRRESERVA_H

#include <QDialog>
#include <QMessageBox>
#include <vector>

#include "Clases/ControladorBD/controladorbd.h"

namespace Ui {
class AniadirReserva;
}

class AniadirReserva : public QDialog
{
    Q_OBJECT

public:
    explicit AniadirReserva(vector<Reserva> *reservas, QWidget *parent = nullptr, ControladorBD *controladorBD = nullptr);
    ~AniadirReserva();

    void abrirVentana();
    void limpiarVentana();

signals:
    void cerrarVentana(bool cerrar = false);

private slots:
    void cerrar();

    void on_pushButtonAniadir_clicked();

    void on_checkBoxHabitacion_stateChanged(int arg1);

private:
    Ui::AniadirReserva *ui;

    vector<Reserva> *reservas;
    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // ANIADIRRESERVA_H

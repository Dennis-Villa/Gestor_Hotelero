#ifndef ANIADIRGASTO_H
#define ANIADIRGASTO_H

#include <QDialog>
#include <QMessageBox>

#include "Clases/Reserva/reserva.h"
#include "Clases/ControladorBD/controladorbd.h"

namespace Ui {
class AniadirGasto;
}

class AniadirGasto : public QDialog
{
    Q_OBJECT

public:
    explicit AniadirGasto(ControladorBD *controladorBD, QWidget *parent = nullptr);
    ~AniadirGasto();

    void setReserva(Reserva *reserva){this->reserva = reserva;}

    void mostrar();
    void limpiar();

signals:
    void actualizar(bool actualizar = false);

public slots:
    void cerrar();
    void aniadir();

private:
    Ui::AniadirGasto *ui;

    ControladorBD *controladorBD;
    Reserva *reserva;
};

#endif // ANIADIRGASTO_H

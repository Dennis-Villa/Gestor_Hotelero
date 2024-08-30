#ifndef INFORESERVA_H
#define INFORESERVA_H

#include <QDialog>

#include "Clases/Reserva/reserva.h"

namespace Ui {
class InfoReserva;
}

class InfoReserva : public QDialog
{
    Q_OBJECT

public:
    explicit InfoReserva(QWidget *parent = nullptr);
    ~InfoReserva();

    void setReserva(Reserva *reserva){this->reserva = reserva;}

    void mostrar();
    void limpiar();

public slots:
    void cerrar();

private:
    Ui::InfoReserva *ui;

    Reserva *reserva;
};

#endif // INFORESERVA_H

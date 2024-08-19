#ifndef ANIADIRRESERVA_H
#define ANIADIRRESERVA_H

#include <QDialog>

#include "Clases/ControladorBD/controladorbd.h"

namespace Ui {
class AniadirReserva;
}

class AniadirReserva : public QDialog
{
    Q_OBJECT

public:
    explicit AniadirReserva(QWidget *parent = nullptr, ControladorBD *controladorBD = nullptr);
    ~AniadirReserva();

    void abrirVentana();
    void limpiarVentana();

signals:
    void cerrarVentana(bool cerrar = false);

private slots:
    void cerrar();

    void on_pushButtonAniadir_clicked();

private:
    Ui::AniadirReserva *ui;

    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // ANIADIRRESERVA_H

#ifndef ANIADIRCLIENTE_H
#define ANIADIRCLIENTE_H

#include <QDialog>
#include <QString>

#include <QMessageBox>
#include "Clases/Cliente/cliente.h"
#include "Clases/ControladorBD/controladorbd.h"

namespace Ui {
class AniadirCliente;
}

class AniadirCliente : public QDialog
{
    Q_OBJECT

public:
    explicit AniadirCliente(QWidget *parent = nullptr, ControladorBD *controladorBD = nullptr);
    ~AniadirCliente();

    void abrirVentana();
    void limpiarVentana();

signals:
    void cerrarVentana(bool cerrar = false);

private slots:
    void aniadirCliente();

    void cerrar();

private:
    Ui::AniadirCliente *ui;

    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // ANIADIRCLIENTE_H

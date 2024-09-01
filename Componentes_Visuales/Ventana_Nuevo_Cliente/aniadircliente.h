#ifndef ANIADIRCLIENTE_H
#define ANIADIRCLIENTE_H

#include <QDialog>
#include <QString>
#include <vector>

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
    explicit AniadirCliente(vector<Cliente> *clientes, QWidget *parent = nullptr, ControladorBD *controladorBD = nullptr);
    ~AniadirCliente();

    void abrirVentana();
    void limpiarVentana();

signals:
    void cerrarVentana(bool cerrar = false);
    void aniadido(bool actualizar = false);

private slots:
    void aniadirCliente();

    void cerrar();

private:
    Ui::AniadirCliente *ui;

    vector<Cliente> *clientes;
    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // ANIADIRCLIENTE_H

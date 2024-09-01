#ifndef REGISTRARENTRADA_H
#define REGISTRARENTRADA_H

#include <QDialog>
#include <QDate>
#include <QMessageBox>
#include <set>

#include "Clases/ControladorBD/controladorbd.h"
#include "Clases/Reserva/reserva.h"

namespace Ui {
class RegistrarEntrada;
}

class RegistrarEntrada : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrarEntrada(vector<Reserva> *reservas, ControladorBD *controladorBD, QWidget *parent = nullptr);
    ~RegistrarEntrada();

    void abrirVentana();
    void limpiarVentana();
    void establecerCliente(QString cliente);

signals:
    void cerrarVentana(bool cerrar = false);
    void registrado(bool actualizar = false);

private slots:
    void cerrar();
    void rellenarComboBoxClientes();
    void rellenarComboBoxClientes(set<int> *clientesID);
    void buscarClientes(QString cliente = "");
    void rellenarInformacionReserva();
    void registrar();

private:
    Ui::RegistrarEntrada *ui;

    vector<Reserva> *reservas;
    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // REGISTRARENTRADA_H

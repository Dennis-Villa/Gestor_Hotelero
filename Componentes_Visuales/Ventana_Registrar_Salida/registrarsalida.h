#ifndef REGISTRARSALIDA_H
#define REGISTRARSALIDA_H

#include <QDialog>
#include <QDate>
#include <QMessageBox>
#include <set>

#include "Clases/ControladorBD/controladorbd.h"
#include "Clases/Reserva/reserva.h"

namespace Ui {
class RegistrarSalida;
}

class RegistrarSalida : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrarSalida(vector<Reserva> *reservas, ControladorBD *controladorBD, QWidget *parent = nullptr);
    ~RegistrarSalida();

    void abrirVentana();
    void limpiarVentana();
    void establecerCliente(QString cliente);

signals:
    void cerrarVentana(bool cerrar = false);

private slots:
    void cerrar();
    void rellenarComboBoxClientes();
    void rellenarComboBoxClientes(set<int> *clientesID);
    void buscarClientes(QString cliente = "");
    void rellenarInformacionReserva();
    void registrar();

private:
    Ui::RegistrarSalida *ui;

    vector<Reserva> *reservas;
    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // REGISTRARSALIDA_H

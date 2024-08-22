#ifndef ANIADIRRESERVA_H
#define ANIADIRRESERVA_H

#include <QDialog>
#include <QMessageBox>
#include <vector>
#include <set>

#include "Clases/ControladorBD/controladorbd.h"
#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"
#include "Clases/Reserva/reserva.h"

namespace Ui {
class AniadirReserva;
}

class AniadirReserva : public QDialog
{
    Q_OBJECT

public:
    explicit AniadirReserva(vector<Cliente> *clientes, vector<Habitacion> *habitaciones,
                            vector<Reserva> *reservas, QWidget *parent = nullptr,
                            ControladorBD *controladorBD = nullptr);
    ~AniadirReserva();

    void abrirVentana();
    void limpiarVentana();

signals:
    void cerrarVentana(bool cerrar = false);

private slots:
    void cerrar();
    void actualizarCoste();

    void on_pushButtonAniadir_clicked();

    void on_checkBoxHabitacion_stateChanged(int arg1);

    void on_lineEditCliente_textChanged(const QString &arg1);

    void on_comboBoxPiso_currentTextChanged(const QString &arg1);

private:
    void rellenarComboBoxClientes();
    void rellenarComboBoxClientes(set<int> *clientesID);
    void rellenarPisosHabitaciones();

    Ui::AniadirReserva *ui;

    vector<Cliente> *clientes;
    vector<Habitacion> *habitaciones;
    vector<Reserva> *reservas;
    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // ANIADIRRESERVA_H

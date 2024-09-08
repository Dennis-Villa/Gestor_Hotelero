#ifndef ANIADIRRESERVA_H
#define ANIADIRRESERVA_H

#include <QDialog>
#include <QDate>
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
    void abrirVentana(Reserva *reserva);
    void limpiarVentana();
    bool verificarDisponibilidadHabitacion(int numeroHabitacion, QDate inicio, int dias);

signals:
    void cerrarVentana(bool cerrar = false);
    void aniadido(bool actualizar = false);

private slots:
    void cerrar();
    void actualizarCoste();
    void actualizarNumerosHabitaciones();
    void activarSeleccionFecha();
    void modificarReserva();
    void aniadir();
    void habilitarHabitacion(int arg1);
    void actualizarClientes(const QString &arg1);

private:
    void rellenarComboBoxClientes();
    void rellenarComboBoxClientes(set<int> *clientesID);
    void rellenarPisosHabitaciones();

    Ui::AniadirReserva *ui;

    vector<Cliente> *clientes;
    vector<Habitacion> *habitaciones;
    vector<Reserva> *reservas;
    Reserva *reserva;
    ControladorBD *controladorBD;
    bool ventanaAbierta;
};

#endif // ANIADIRRESERVA_H

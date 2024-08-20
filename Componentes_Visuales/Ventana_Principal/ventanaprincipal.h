#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QDateTime>
#include <vector>

#include "Clases/ControladorBD/controladorbd.h"
#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"
#include "Clases/Reserva/reserva.h"
#include "Componentes_Visuales/Ventana_Nuevo_Cliente/aniadircliente.h"
#include "Componentes_Visuales/Ventana_Nueva_Habitacion/aniadirhabitacion.h"
#include "Componentes_Visuales/Ventana_Nueva_Reserva/aniadirreserva.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class VentanaPrincipal;
}
QT_END_NAMESPACE

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

private slots:
    void on_actionCliente_triggered();

    void on_actionHabitacion_triggered();

    void crearNuevaReserva();

    void cerrarNuevoCliente(bool cerrar = false);
    void cerrarNuevaHabitacion(bool cerrar = false);
    void cerrarNuevaReserva(bool cerrar = false);

    void on_pushButtonDebug_clicked();

private:
    Ui::VentanaPrincipal *ui;
    QDate fechaActual = QDate::currentDate();

    ControladorBD *controladorBD = new ControladorBD();

    vector<Cliente> clientes;
    vector<Habitacion> habitaciones;
    vector<Reserva> reservas;

    AniadirCliente *ventanaNuevoCliente = new AniadirCliente(&clientes, this, controladorBD);
    AniadirHabitacion *ventanaNuevaHabitacion = new AniadirHabitacion(&habitaciones, this, controladorBD);
    AniadirReserva *ventanaNuevaReserva = new AniadirReserva(&reservas, this, controladorBD);
};
#endif // VENTANAPRINCIPAL_H

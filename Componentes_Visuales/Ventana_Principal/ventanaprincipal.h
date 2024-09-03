#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QDateTime>
#include <QTableWidget>
#include <QBoxLayout>
#include <vector>

#include "Archivos_Auxiliares/Boton_Posicion_Fila/botonposicionfila.h"
#include "Clases/ControladorBD/controladorbd.h"
#include "Clases/Cliente/cliente.h"
#include "Clases/Habitacion/habitacion.h"
#include "Clases/Reserva/reserva.h"
#include "Componentes_Visuales/Ventana_Nuevo_Cliente/aniadircliente.h"
#include "Componentes_Visuales/Ventana_Nueva_Habitacion/aniadirhabitacion.h"
#include "Componentes_Visuales/Ventana_Nueva_Reserva/aniadirreserva.h"
#include "Componentes_Visuales/Ventana_Registrar_Entrada/registrarentrada.h"
#include "Componentes_Visuales/Ventana_Registrar_Salida/registrarsalida.h"
#include "Componentes_Visuales/Ventana_Info_Reserva/inforeserva.h"
#include "Componentes_Visuales/Ventana_Estado_Habitacion/estadohabitacion.h"
#include "Componentes_Visuales/Ventana_Nuevo_Gasto/aniadirgasto.h"

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

    void iniciarVentana();
    void llenarTablaReserva(QDate fechaComparacion, QDate fechaActual, Reserva reserva,
                            QTableWidget *tableWidget, int *fila);
    void llenarTablaOcupacion(Reserva reserva, QDate fechaActual, int *fila);

    // Funciones para llenar la informacion de todos los clientes
    void llenarInfoDatos();
    void limpiarTabla(QTableWidget *tabla);
    void aniadirLineaInfoCliente(Cliente cliente);
    void aniadirLineaInfoHabitacion(Habitacion habitacion);
    void aniadirLineaInfoReserva(Reserva reserva);

private slots:
    void nuevoCliente();
    void nuevaHabitacion();
    void crearNuevaReserva();

    void cerrarNuevoCliente(bool cerrar = false);
    void cerrarNuevaHabitacion(bool cerrar = false);
    void cerrarNuevaReserva(bool cerrar = false);
    void cerrarRegistrarEntrada(bool cerrar = false);
    void cerrarRegistrarSalida(bool cerrar = false);

    void registrarNuevaEntrada(int fila = -1, int columna = -1);
    void registrarNuevaSalida(int fila = -1, int columna = -1);

    void eliminarCliente(int clienteID = -1);
    void modificarEstadoHabitacion(int numeroHabitacion = -1);
    void mostrarInfoReserva(int numeroReserva = -1);
    void modificarReserva(int numeroReserva = -1);
    void aniadirGasto(int numeroReserva = -1);

    // Funciones para actualizar los componentes con datos cuando cambian los vectores
    void actualizarVectores(bool actualizar = false);

    void on_pushButtonDebug_clicked();

public slots:
    void llenarInfoReservas();

private:
    void conecciones();

    Ui::VentanaPrincipal *ui;
    QDate fechaActual = QDate::currentDate();

    ControladorBD *controladorBD = nullptr;

    vector<Cliente> clientes;
    vector<Habitacion> habitaciones;
    vector<Reserva> reservas;

    AniadirCliente *ventanaNuevoCliente = nullptr;
    AniadirHabitacion *ventanaNuevaHabitacion = nullptr;
    AniadirReserva *ventanaNuevaReserva = nullptr;
    RegistrarEntrada *ventanaRegistrarEntrada = nullptr;
    RegistrarSalida *ventanaRegistrarSalida = nullptr;
    InfoReserva *ventanaInfoReserva = nullptr;
    EstadoHabitacion *ventanaEstadoHabitacion = nullptr;
    AniadirGasto *ventanaNuevoGasto = nullptr;
};
#endif // VENTANAPRINCIPAL_H

#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    ui->dateEditActual->setDate(this->fechaActual);

    this->clientes = this->controladorBD->getClientes();
    this->habitaciones = this->controladorBD->getHabitaciones();
    this->reservas = this->controladorBD->getReservas();

    this->ventanaNuevoCliente = new AniadirCliente(&this->clientes, this, this->controladorBD);
    this->ventanaNuevaHabitacion = new AniadirHabitacion(&this->habitaciones, this, this->controladorBD);
    this->ventanaNuevaReserva = new AniadirReserva(&this->clientes, &this->habitaciones,
                                                   &this->reservas, this, this->controladorBD);

    connect(this->ventanaNuevoCliente, &AniadirCliente::cerrarVentana, this, &VentanaPrincipal::cerrarNuevoCliente);
    connect(this->ventanaNuevaHabitacion, &AniadirHabitacion::cerrarVentana, this, &VentanaPrincipal::cerrarNuevaHabitacion);
    connect(this->ventanaNuevaReserva, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarNuevaReserva(bool)));
    connect(ui->pushButtonNuevaReserva, SIGNAL(clicked()), this, SLOT(crearNuevaReserva()));
    connect(ui->actionReserva, SIGNAL(triggered()), this, SLOT(crearNuevaReserva()));
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::cerrarNuevoCliente(bool cerrar)
{
    if (cerrar)
    {
        this->ventanaNuevoCliente->close();
        ui->centralwidget->setDisabled(false);
    }
}

void VentanaPrincipal::cerrarNuevaHabitacion(bool cerrar)
{
    if (cerrar)
    {
        this->ventanaNuevaHabitacion->close();
        ui->centralwidget->setDisabled(false);
    }
}

void VentanaPrincipal::cerrarNuevaReserva(bool cerrar)
{
    if (cerrar)
    {
        this->ventanaNuevaReserva->close();
        ui->centralwidget->setDisabled(false);
    }
}

void VentanaPrincipal::on_actionCliente_triggered()
{
    ui->centralwidget->setDisabled(true);
    this->ventanaNuevoCliente->show();
    this->ventanaNuevoCliente->abrirVentana();
}


void VentanaPrincipal::on_actionHabitacion_triggered()
{
    ui->centralwidget->setDisabled(true);
    this->ventanaNuevaHabitacion->show();
    this->ventanaNuevaHabitacion->abrirVentana();
}

void VentanaPrincipal::crearNuevaReserva()
{
    ui->centralwidget->setDisabled(true);
    this->ventanaNuevaReserva->show();
    this->ventanaNuevaReserva->abrirVentana();
}


void VentanaPrincipal::on_pushButtonDebug_clicked()
{
    QString mensaje = "Cantidad de clientes: ";
    mensaje += QString::number(this->clientes.size());

    mensaje += "\nCantidad de habitaciones: ";
    mensaje += QString::number(this->habitaciones.size());

    mensaje += "\nCantidad de reservas: ";
    mensaje += QString::number(this->reservas.size());

    QMessageBox::information(this, "Conteo", mensaje);
}


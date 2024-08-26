#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    this->iniciarVentana();

    connect(this->ventanaNuevoCliente, &AniadirCliente::cerrarVentana, this, &VentanaPrincipal::cerrarNuevoCliente);
    connect(this->ventanaNuevaHabitacion, &AniadirHabitacion::cerrarVentana, this, &VentanaPrincipal::cerrarNuevaHabitacion);
    connect(this->ventanaNuevaReserva, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarNuevaReserva(bool)));
    connect(ui->pushButtonNuevaReserva, SIGNAL(clicked()), this, SLOT(crearNuevaReserva()));
    connect(ui->actionReserva, SIGNAL(triggered()), this, SLOT(crearNuevaReserva()));
    connect(ui->dateEditActual, SIGNAL(userDateChanged(QDate)), this, SLOT(llenarLlegadasHoy()));
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::iniciarVentana()
{
    ui->dateEditActual->setDate(this->fechaActual);

    try{
        this->clientes = this->controladorBD->getClientes();
        this->habitaciones = this->controladorBD->getHabitaciones();
        this->reservas = this->controladorBD->getReservas();
    }
    catch(exception &ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }

    this->ventanaNuevoCliente = new AniadirCliente(&this->clientes, this, this->controladorBD);
    this->ventanaNuevaHabitacion = new AniadirHabitacion(&this->habitaciones, this, this->controladorBD);
    this->ventanaNuevaReserva = new AniadirReserva(&this->clientes, &this->habitaciones,
                                                   &this->reservas, this, this->controladorBD);

    this->llenarLlegadasHoy();
}

void VentanaPrincipal::llenarTablaReserva(QDate fechaComparacion, QTableWidget *tableWidget)
{
    tableWidget->setRowCount(0);
    int fila = 0;

    for (Reserva reserva: this->reservas)
    {
        if(reserva.getFechaInicio() == fechaComparacion)
        {
            tableWidget->insertRow(fila);

            QTableWidgetItem *clienteItem = new QTableWidgetItem(tr("%1").arg(reserva.getClienteNombre()));
            QTableWidgetItem *confirmacionItem = new QTableWidgetItem(tr("%1").arg(reserva.getNumeroConfirmacion()));
            QTableWidgetItem *habitacionItem = new QTableWidgetItem(tr("%1").arg(reserva.getNumeroHabitacion()));

            tableWidget->setItem(fila, 0, clienteItem);
            tableWidget->setItem(fila, 1, confirmacionItem);
            tableWidget->setItem(fila, 2, habitacionItem);

            fila++;
        }
    }
}

void VentanaPrincipal::llenarLlegadasHoy()
{
    this->llenarTablaReserva(ui->dateEditActual->date(), ui->tableWidgetLlegadasHoy);

    // ui->tableWidgetLlegadasHoy->setRowCount(0);
    // int fila = 0;

    // for (Reserva reserva: this->reservas)
    // {
    //     if(reserva.getFechaInicio() == ui->dateEditActual->date())
    //     {
    //         ui->tableWidgetLlegadasHoy->insertRow(fila);

    //         // int numeroConfirmacion = reserva.getNumeroConfirmacion();
    //         // int habitacion = reserva.getNumeroHabitacion();

    //         QTableWidgetItem *clienteItem = new QTableWidgetItem(tr("%1").arg(reserva.getClienteNombre()));
    //         QTableWidgetItem *confirmacionItem = new QTableWidgetItem(tr("%1").arg(reserva.getNumeroConfirmacion()));
    //         QTableWidgetItem *habitacionItem = new QTableWidgetItem(tr("%1").arg(reserva.getNumeroHabitacion()));

    //         ui->tableWidgetLlegadasHoy->setItem(fila, 0, clienteItem);
    //         ui->tableWidgetLlegadasHoy->setItem(fila, 1, confirmacionItem);
    //         ui->tableWidgetLlegadasHoy->setItem(fila, 2, habitacionItem);

    //         fila++;
    //     }
    // }
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


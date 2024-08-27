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
    connect(ui->dateEditActual, SIGNAL(userDateChanged(QDate)), this, SLOT(llenarInfoReservas()));
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

    this->llenarInfoReservas();
}

void VentanaPrincipal::llenarTablaReserva(QDate fechaComparacion, QDate fechaActual, Reserva reserva, QTableWidget *tableWidget, int *fila)
{
    if(fechaActual == fechaComparacion)
    {
        tableWidget->insertRow(*fila);

        QTableWidgetItem *clienteItem = new QTableWidgetItem(tr("%1").arg(reserva.getClienteNombre()));
        QTableWidgetItem *confirmacionItem = new QTableWidgetItem(tr("%1").arg(reserva.getNumeroConfirmacion()));
        QTableWidgetItem *habitacionItem = new QTableWidgetItem(tr("%1").arg(reserva.getNumeroHabitacion()));

        tableWidget->setItem(*fila, 0, clienteItem);
        tableWidget->setItem(*fila, 1, confirmacionItem);
        tableWidget->setItem(*fila, 2, habitacionItem);

        *fila += 1;
    }
}

void VentanaPrincipal::llenarTablaOcupacion(Reserva reserva, QDate fechaActual, int *fila)
{
    if((fechaActual >= reserva.getFechaInicio()) && (fechaActual < reserva.getFechaFin()))
    {
        ui->tableWidgetOcupacion->insertRow(*fila);

        QTableWidgetItem *habitacionItem = new QTableWidgetItem(tr("%1").arg(reserva.getNumeroHabitacion()));
        QTableWidgetItem *clienteItem = new QTableWidgetItem(tr("%1").arg(reserva.getClienteNombre()));
        QTableWidgetItem *fechaFinItem = new QTableWidgetItem(tr("%1").arg(reserva.getFechaFin().toString()));
        QTableWidgetItem *importeItem = new QTableWidgetItem(tr("%1").arg(reserva.getImporte()));

        ui->tableWidgetOcupacion->setItem(*fila, 0, habitacionItem);
        ui->tableWidgetOcupacion->setItem(*fila, 1, clienteItem);
        ui->tableWidgetOcupacion->setItem(*fila, 2, fechaFinItem);
        ui->tableWidgetOcupacion->setItem(*fila, 3, importeItem);

        ui->tableWidgetOcupacion->sortItems(0);

        *fila += 1;
    }
}

void VentanaPrincipal::llenarInfoReservas()
{
    QDate fechaHoy = ui->dateEditActual->date();
    QDate fechaManiana = fechaHoy.addDays(1);

    QTableWidget *llegadasHoy = ui->tableWidgetLlegadasHoy;
    QTableWidget *llegadasManiana = ui->tableWidgetLlegadasManiana;
    QTableWidget *salidasHoy = ui->tableWidgetSalidasHoy;
    QTableWidget *salidasManiana = ui->tableWidgetSalidasManiana;

    llegadasHoy->setRowCount(0);
    llegadasManiana->setRowCount(0);
    salidasHoy->setRowCount(0);
    salidasManiana->setRowCount(0);
    ui->tableWidgetOcupacion->setRowCount(0);

    int filasLlegadasHoy = 0;
    int filasLlegadasManiana = 0;
    int filasSalidasHoy = 0;
    int filasSalidasManiana = 0;
    int filasOcupacion = 0;

    for (Reserva reserva: this->reservas)
    {
        this->llenarTablaReserva(reserva.getFechaInicio(), fechaHoy, reserva, llegadasHoy, &filasLlegadasHoy);
        this->llenarTablaReserva(reserva.getFechaInicio(), fechaManiana, reserva, llegadasManiana, &filasLlegadasManiana);
        this->llenarTablaReserva(reserva.getFechaFin(), fechaHoy, reserva, salidasHoy, &filasSalidasHoy);
        this->llenarTablaReserva(reserva.getFechaFin(), fechaManiana, reserva, salidasManiana, &filasSalidasManiana);

        this->llenarTablaOcupacion(reserva, fechaHoy, &filasOcupacion);
    }
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


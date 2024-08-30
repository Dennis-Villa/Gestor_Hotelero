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
    connect(this->ventanaRegistrarEntrada, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarRegistrarEntrada(bool)));
    connect(this->ventanaRegistrarSalida, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarRegistrarSalida(bool)));

    connect(ui->actionReserva, SIGNAL(triggered()), this, SLOT(crearNuevaReserva()));
    connect(ui->actionEntrada, SIGNAL(triggered()), this, SLOT(registrarNuevaEntrada()));
    connect(ui->actionSalida, SIGNAL(triggered()), this, SLOT(registrarNuevaSalida()));

    connect(ui->pushButtonNuevaReserva, SIGNAL(clicked()), this, SLOT(crearNuevaReserva()));
    connect(ui->dateEditActual, SIGNAL(userDateChanged(QDate)), this, SLOT(llenarInfoReservas()));
    connect(ui->tableWidgetLlegadasHoy, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(registrarNuevaEntrada(int,int)));
    connect(ui->tableWidgetSalidasHoy, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(registrarNuevaSalida(int,int)));
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
    this->ventanaRegistrarEntrada = new RegistrarEntrada(&this->reservas, this->controladorBD, this);
    this->ventanaRegistrarSalida = new RegistrarSalida(&this->reservas, this->controladorBD, this);
    this->ventanaInfoReserva = new InfoReserva(this);
    this->ventanaEstadoHabitacion = new EstadoHabitacion(&this->habitaciones, this->controladorBD, this);

    this->actualizarVectores();
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

void VentanaPrincipal::actualizarVectores()
{
    this->llenarInfoDatos();
    this->llenarInfoReservas();
}

void VentanaPrincipal::llenarInfoDatos()
{
    for (Cliente cliente: this->clientes)
    {
        this->aniadirLineaInfoCliente(cliente);
    }

    for (Reserva reserva: this->reservas)
    {
        this->aniadirLineaInfoReserva(reserva);
    }

    for (Habitacion habitacion: this->habitaciones)
    {
        this->aniadirLineaInfoHabitacion(habitacion);
    }

    QSpacerItem *spacer = new QSpacerItem(12, 1024);
    ui->verticalLayoutInfoClientes->addSpacerItem(spacer);
    ui->verticalLayoutInfoHabitaciones->addSpacerItem(spacer);
    ui->verticalLayoutInfoReservas->addSpacerItem(spacer);
}

void VentanaPrincipal::aniadirLineaInfoCliente(Cliente cliente)
{
    QHBoxLayout *layoutInfoCliente = new QHBoxLayout(ui->tabInformacionClientes);

    int clienteID = cliente.getIdentificador();

    QLabel *labelID = new QLabel(QString::number(clienteID));
    QLabel *labelNombre = new QLabel(cliente.getNombre());
    QLabel *labelEmail = new QLabel(cliente.getEmail());
    QLabel *labelTelefono = new QLabel(cliente.getTelefono());
    QLabel *labelNacionalidad = new QLabel(cliente.getNacionalidad());
    QLabel *labelCantidadEstancias = new QLabel(QString::number(cliente.getCanidadEstancias()));

    BotonPosicionFila *eliminar = new BotonPosicionFila("Eliminar", clienteID);

    layoutInfoCliente->addWidget(labelID);
    layoutInfoCliente->addWidget(labelNombre);
    layoutInfoCliente->addWidget(labelEmail);
    layoutInfoCliente->addWidget(labelTelefono);
    layoutInfoCliente->addWidget(labelNacionalidad);
    layoutInfoCliente->addWidget(labelCantidadEstancias);

    layoutInfoCliente->addWidget(eliminar);

    ui->verticalLayoutInfoClientes->addLayout(layoutInfoCliente);

    connect(eliminar, SIGNAL(clicked(int)), this, SLOT(eliminarCliente(int)));
}

void VentanaPrincipal::aniadirLineaInfoHabitacion(Habitacion habitacion)
{
    QHBoxLayout *layoutInfoHabitacion = new QHBoxLayout(ui->tabInformacionHabitaciones);

    int numeroHabitacion = habitacion.getNumeroHabitacion();

    QLabel *labelNumero = new QLabel(QString::number(numeroHabitacion));
    QLabel *labelTipo = new QLabel(habitacion.getTipoHabitacion());
    QLabel *labelTamanio = new QLabel(QString::number(habitacion.getTamanioM2()));
    QLabel *labelCamas = new QLabel(QString::number(habitacion.getNumeroCamas()));
    QLabel *labelCoste = new QLabel(QString::number(habitacion.getCostePorNoche()));
    QLabel *labelDisponible = new QLabel(QString::number(habitacion.getDisponible()));
    QLabel *labelEnArreglos = new QLabel(QString::number(habitacion.getEnArreglos()));

    BotonPosicionFila *info = new BotonPosicionFila("Información", numeroHabitacion);

    layoutInfoHabitacion->addWidget(labelNumero);
    layoutInfoHabitacion->addWidget(labelTipo);
    layoutInfoHabitacion->addWidget(labelTamanio);
    layoutInfoHabitacion->addWidget(labelCamas);
    layoutInfoHabitacion->addWidget(labelCoste);
    layoutInfoHabitacion->addWidget(labelDisponible);
    layoutInfoHabitacion->addWidget(labelEnArreglos);

    layoutInfoHabitacion->addWidget(info);

    ui->verticalLayoutInfoHabitaciones->addLayout(layoutInfoHabitacion);

    connect(info, SIGNAL(clicked(int)), this, SLOT(modificarEstadoHabitacion(int)));
}

void VentanaPrincipal::aniadirLineaInfoReserva(Reserva reserva)
{
    QHBoxLayout *layoutInfoReserva = new QHBoxLayout(ui->tabInformacionReservas);

    int numeroConfirmacion = reserva.getNumeroConfirmacion();
    QString habitacion = (reserva.getNumeroHabitacion() == -1
                            ? ""
                            : QString::number(reserva.getNumeroHabitacion()));

    QLabel *labelID = new QLabel(QString::number(numeroConfirmacion));
    QLabel *labelCliente = new QLabel(reserva.getClienteNombre());
    QLabel *labelHabitacion = new QLabel(habitacion);
    QLabel *labelEstado = new QLabel(reserva.getEstadoReserva());
    QLabel *labelInicio = new QLabel(reserva.getFechaInicioString());

    BotonPosicionFila *info = new BotonPosicionFila("Información", numeroConfirmacion);

    layoutInfoReserva->addWidget(labelID);
    layoutInfoReserva->addWidget(labelCliente);
    layoutInfoReserva->addWidget(labelHabitacion);
    layoutInfoReserva->addWidget(labelEstado);
    layoutInfoReserva->addWidget(labelInicio);

    layoutInfoReserva->addWidget(info);

    ui->verticalLayoutInfoReservas->addLayout(layoutInfoReserva);

    connect(info, SIGNAL(clicked(int)), this, SLOT(mostrarInfoReserva(int)));
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

void VentanaPrincipal::cerrarRegistrarEntrada(bool cerrar)
{
    if (cerrar)
    {
        this->ventanaRegistrarEntrada->close();
        ui->centralwidget->setDisabled(false);
    }
}

void VentanaPrincipal::cerrarRegistrarSalida(bool cerrar)
{
    if (cerrar)
    {
        this->ventanaRegistrarSalida->close();
        ui->centralwidget->setDisabled(false);
    }
}

void VentanaPrincipal::registrarNuevaEntrada(int fila, int columna)
{
    if((ui->dateEditActual->date() == QDate::currentDate()) && (fila != -1) && (columna != -1))
    {
        QString cliente = ui->tableWidgetLlegadasHoy->item(fila, 0)->text();

        this->ventanaRegistrarEntrada->establecerCliente(cliente);
    }

    ui->centralwidget->setDisabled(true);
    this->ventanaRegistrarEntrada->show();
    this->ventanaRegistrarEntrada->abrirVentana();
}

void VentanaPrincipal::registrarNuevaSalida(int fila, int columna)
{
    if((ui->dateEditActual->date() == QDate::currentDate()) && (fila != -1) && (columna != -1))
    {
        QString cliente = ui->tableWidgetSalidasHoy->item(fila, 0)->text();

        this->ventanaRegistrarSalida->establecerCliente(cliente);
    }

    ui->centralwidget->setDisabled(true);
    this->ventanaRegistrarSalida->show();
    this->ventanaRegistrarSalida->abrirVentana();
}

void VentanaPrincipal::eliminarCliente(int clienteID)
{
    if(clienteID != -1)
    {
        QString mensaje = "¿Seguro que desea eliminar al cliente con id " + QString::number(clienteID) + "?";

        int respuesta = QMessageBox::warning(this, "Eliminación de cliente", mensaje, (QMessageBox::Yes | QMessageBox::No));

        if (respuesta == QMessageBox::Yes)
        {
            this->controladorBD->eliminarCliente(clienteID);

            for (int i = 0; i < (int)this->clientes.size(); i++)
            {
                if(this->clientes.at(i).getIdentificador() == clienteID)
                {
                    this->clientes.erase(this->clientes.begin() + i);
                }
            }

            for (int i = 0; i < (int)this->reservas.size(); i++)
            {
                Reserva reserva = this->reservas.at(i);

                if(reserva.getClienteID() == clienteID)
                {
                    this->controladorBD->eliminarReserva(reserva.getNumeroConfirmacion());

                    this->reservas.erase(this->reservas.begin() + i);
                }
            }

            QMessageBox::information(this, "Exito", "Cliente eliminado de la base de datos");

            this->actualizarVectores();
        }
    }
}

void VentanaPrincipal::modificarEstadoHabitacion(int numeroHabitacion)
{
    if (numeroHabitacion != -1)
    {
        for (Habitacion habitacion: this->habitaciones)
        {
            if (habitacion.getNumeroHabitacion() == numeroHabitacion)
            {
                this->ventanaEstadoHabitacion->setHabitacion(habitacion.getNumeroHabitacion());
                this->ventanaEstadoHabitacion->mostrar();

                break;
            }
        }
    }
}

void VentanaPrincipal::mostrarInfoReserva(int numeroReserva)
{
    if (numeroReserva != -1)
    {
        for (Reserva reserva: this->reservas)
        {
            if (reserva.getNumeroConfirmacion() == numeroReserva)
            {
                this->ventanaInfoReserva->setReserva(&reserva);
                this->ventanaInfoReserva->mostrar();
            }
        }
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


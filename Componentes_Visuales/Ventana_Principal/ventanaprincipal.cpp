#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    this->iniciarVentana();

    this->conecciones();
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
    this->ventanaEstadoHabitacion = new EstadoHabitacion(this->controladorBD, this);
    this->ventanaNuevoGasto = new AniadirGasto(this->controladorBD, this);

    this->actualizarVectores(true);
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

        QTableWidgetItem *habitacionItem = new QTableWidgetItem();
        habitacionItem->setData(Qt::DisplayRole, reserva.getNumeroHabitacion());

        QTableWidgetItem *clienteItem = new QTableWidgetItem(tr("%1").arg(reserva.getClienteNombre()));
        QTableWidgetItem *fechaFinItem = new QTableWidgetItem(tr("%1").arg(reserva.getFechaFinString()));

        QTableWidgetItem *importeItem = new QTableWidgetItem();
        importeItem->setData(Qt::DisplayRole, reserva.getImporte());

        BotonPosicionFila *gasto = new BotonPosicionFila("Añadir Gasto", reserva.getNumeroConfirmacion());
        gasto->setFlat(true);

        ui->tableWidgetOcupacion->setItem(*fila, 0, habitacionItem);
        ui->tableWidgetOcupacion->setItem(*fila, 1, clienteItem);
        ui->tableWidgetOcupacion->setItem(*fila, 2, fechaFinItem);
        ui->tableWidgetOcupacion->setItem(*fila, 3, importeItem);

        ui->tableWidgetOcupacion->setCellWidget(*fila, 4, gasto);
        connect(gasto, SIGNAL(clicked(int)), this, SLOT(aniadirGasto(int)));

        *fila += 1;
    }

    ui->tableWidgetOcupacion->sortItems(0);
}

void VentanaPrincipal::llenarInfoDatos()
{
    this->limpiarTabla(ui->tableWidgetClientes);
    for (Cliente cliente: this->clientes)
    {
        this->aniadirLineaInfoCliente(cliente);
    }
    ui->tableWidgetClientes->sortItems(0);

    this->limpiarTabla(ui->tableWidgetHabitaciones);
    for (Habitacion habitacion: this->habitaciones)
    {
        this->aniadirLineaInfoHabitacion(habitacion);
    }
    ui->tableWidgetHabitaciones->sortItems(0);

    this->limpiarTabla(ui->tableWidgetReservas);
    for (Reserva reserva: this->reservas)
    {
        this->aniadirLineaInfoReserva(reserva);
    }
    ui->tableWidgetReservas->sortItems(0);
}

void VentanaPrincipal::limpiarTabla(QTableWidget *tabla)
{
    tabla->setRowCount(0);
}

void VentanaPrincipal::aniadirLineaInfoCliente(Cliente cliente)
{
    int fila = ui->tableWidgetClientes->rowCount();
    ui->tableWidgetClientes->insertRow(fila);

    int clienteID = cliente.getIdentificador();

    QTableWidgetItem *idItem = new QTableWidgetItem();
    idItem->setData(Qt::DisplayRole, clienteID);

    QTableWidgetItem *nombreItem = new QTableWidgetItem(tr("%1").arg(cliente.getNombre()));
    QTableWidgetItem *emailItem = new QTableWidgetItem(tr("%1").arg(cliente.getEmail()));
    QTableWidgetItem *telefonoItem = new QTableWidgetItem(tr("%1").arg(cliente.getTelefono()));
    QTableWidgetItem *nacionalidadItem = new QTableWidgetItem(tr("%1").arg(cliente.getNacionalidad()));

    int estancias = cliente.getCanidadEstancias();
    QTableWidgetItem *cantidadEstanciasItem = new QTableWidgetItem();
    cantidadEstanciasItem->setData(Qt::DisplayRole, estancias);

    BotonPosicionFila *eliminar = new BotonPosicionFila("Eliminar", clienteID);
    eliminar->setFlat(true);

    ui->tableWidgetClientes->setItem(fila, 0, idItem);
    ui->tableWidgetClientes->setItem(fila, 1, nombreItem);
    ui->tableWidgetClientes->setItem(fila, 2, emailItem);
    ui->tableWidgetClientes->setItem(fila, 3, telefonoItem);
    ui->tableWidgetClientes->setItem(fila, 4, nacionalidadItem);
    ui->tableWidgetClientes->setItem(fila, 5, cantidadEstanciasItem);

    ui->tableWidgetClientes->setCellWidget(fila, 6, eliminar);
    connect(eliminar, SIGNAL(clicked(int)), this, SLOT(eliminarCliente(int)));
}

void VentanaPrincipal::aniadirLineaInfoHabitacion(Habitacion habitacion)
{
    int fila = ui->tableWidgetHabitaciones->rowCount();
    ui->tableWidgetHabitaciones->insertRow(fila);

    int numeroHabitacion = habitacion.getNumeroHabitacion();
    BotonPosicionFila *info = new BotonPosicionFila("Información", numeroHabitacion);
    info->setFlat(true);

    QTableWidgetItem *numeroItem = new QTableWidgetItem();
    numeroItem->setData(Qt::DisplayRole, numeroHabitacion);

    QTableWidgetItem *tipoItem = new QTableWidgetItem(tr("%1").arg(habitacion.getTipoHabitacion()));

    int tamanio = habitacion.getTamanioM2();
    QTableWidgetItem *tamanioFinItem = new QTableWidgetItem();
    tamanioFinItem->setData(Qt::DisplayRole, tamanio);

    int camas = habitacion.getNumeroCamas();
    QTableWidgetItem *camasItem = new QTableWidgetItem();
    camasItem->setData(Qt::DisplayRole, camas);

    int coste = habitacion.getCostePorNoche();
    QTableWidgetItem *costeItem = new QTableWidgetItem();
    costeItem->setData(Qt::DisplayRole, coste);

    QTableWidgetItem *disponibleItem = new QTableWidgetItem(tr("%1").arg(habitacion.getDisponible()));
    QTableWidgetItem *arreglosItem = new QTableWidgetItem(tr("%1").arg(habitacion.getEnArreglos()));

    ui->tableWidgetHabitaciones->setItem(fila, 0, numeroItem);
    ui->tableWidgetHabitaciones->setItem(fila, 1, tipoItem);
    ui->tableWidgetHabitaciones->setItem(fila, 2, tamanioFinItem);
    ui->tableWidgetHabitaciones->setItem(fila, 3, camasItem);
    ui->tableWidgetHabitaciones->setItem(fila, 4, costeItem);
    ui->tableWidgetHabitaciones->setItem(fila, 5, disponibleItem);
    ui->tableWidgetHabitaciones->setItem(fila, 6, arreglosItem);

    ui->tableWidgetHabitaciones->setCellWidget(fila, 7, info);
    connect(info, SIGNAL(clicked(int)), this, SLOT(modificarEstadoHabitacion(int)));
}

void VentanaPrincipal::aniadirLineaInfoReserva(Reserva reserva)
{
    int fila = ui->tableWidgetReservas->rowCount();
    ui->tableWidgetReservas->insertRow(fila);

    int numeroConfirmacion = reserva.getNumeroConfirmacion();
    QString habitacion = (reserva.getNumeroHabitacion() == -1
                              ? ""
                              : QString::number(reserva.getNumeroHabitacion()));

    BotonPosicionFila *info = new BotonPosicionFila("Información", numeroConfirmacion);
    info->setFlat(true);

    BotonPosicionFila *modificar = new BotonPosicionFila("Modificar", numeroConfirmacion);
    modificar->setFlat(true);

    QTableWidgetItem *idItem = new QTableWidgetItem();
    idItem->setData(Qt::DisplayRole, numeroConfirmacion);

    QTableWidgetItem *clienteItem = new QTableWidgetItem(tr("%1").arg(reserva.getClienteNombre()));
    QTableWidgetItem *habitacionFinItem = new QTableWidgetItem(tr("%1").arg(habitacion));
    QTableWidgetItem *inicioItem = new QTableWidgetItem(tr("%1").arg(reserva.getFechaInicioString()));

    QString estado = reserva.getEstadoReserva();
    QTableWidgetItem *estadoItem = new QTableWidgetItem(tr("%1").arg(estado));

    if (estado == "En Estadía" || estado == "Estancia Finalizada" || estado == "Vencida")
        modificar->setDisabled(true);

    ui->tableWidgetReservas->setItem(fila, 0, idItem);
    ui->tableWidgetReservas->setItem(fila, 1, clienteItem);
    ui->tableWidgetReservas->setItem(fila, 2, habitacionFinItem);
    ui->tableWidgetReservas->setItem(fila, 3, estadoItem);
    ui->tableWidgetReservas->setItem(fila, 4, inicioItem);

    ui->tableWidgetReservas->setCellWidget(fila, 5, info);
    ui->tableWidgetReservas->setCellWidget(fila, 6, modificar);

    connect(info, SIGNAL(clicked(int)), this, SLOT(mostrarInfoReserva(int)));
    connect(modificar, SIGNAL(clicked(int)), this, SLOT(modificarReserva(int)));
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

void VentanaPrincipal::conecciones()
{
    connect(ui->actionCliente, SIGNAL(triggered(bool)), this, SLOT(nuevoCliente()));
    connect(ui->pushButtonNuevoCliente, SIGNAL(clicked(bool)), this, SLOT(nuevoCliente()));
    connect(ui->actionHabitacion, SIGNAL(triggered(bool)), this, SLOT(nuevaHabitacion()));
    connect(ui->pushButtonNuevaHabitacion, SIGNAL(clicked(bool)), this, SLOT(nuevaHabitacion()));
    connect(ui->actionReserva, SIGNAL(triggered()), this, SLOT(crearNuevaReserva()));
    connect(ui->pushButtonNuevaReserva, SIGNAL(clicked()), this, SLOT(crearNuevaReserva()));
    connect(ui->actionEntrada, SIGNAL(triggered()), this, SLOT(registrarNuevaEntrada()));
    connect(ui->actionSalida, SIGNAL(triggered()), this, SLOT(registrarNuevaSalida()));

    connect(this->ventanaNuevoCliente, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarNuevoCliente(bool)));
    connect(this->ventanaNuevaHabitacion, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarNuevaHabitacion(bool)));
    connect(this->ventanaNuevaReserva, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarNuevaReserva(bool)));
    connect(this->ventanaRegistrarEntrada, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarRegistrarEntrada(bool)));
    connect(this->ventanaRegistrarSalida, SIGNAL(cerrarVentana(bool)), this, SLOT(cerrarRegistrarSalida(bool)));

    connect(ui->dateEditActual, SIGNAL(userDateChanged(QDate)), this, SLOT(llenarInfoReservas()));
    connect(ui->tableWidgetLlegadasHoy, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(registrarNuevaEntrada(int,int)));
    connect(ui->tableWidgetSalidasHoy, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(registrarNuevaSalida(int,int)));

    connect(this->ventanaEstadoHabitacion, SIGNAL(actualizar(bool)), this, SLOT(actualizarVectores(bool)));
    connect(this->ventanaNuevoGasto, SIGNAL(actualizar(bool)), this, SLOT(actualizarVectores(bool)));
    connect(this->ventanaNuevoCliente, SIGNAL(aniadido(bool)), this, SLOT(actualizarVectores(bool)));
    connect(this->ventanaNuevaHabitacion, SIGNAL(aniadido(bool)), this, SLOT(actualizarVectores(bool)));
    connect(this->ventanaNuevaReserva, SIGNAL(aniadido(bool)), this, SLOT(actualizarVectores(bool)));
    connect(this->ventanaRegistrarEntrada, SIGNAL(registrado(bool)), this, SLOT(actualizarVectores(bool)));
    connect(this->ventanaRegistrarSalida, SIGNAL(registrado(bool)), this, SLOT(actualizarVectores(bool)));
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
            this->actualizarVectores(true);

            QMessageBox::information(this, "Exito", "Cliente eliminado de la base de datos");
        }
    }
}

void VentanaPrincipal::modificarEstadoHabitacion(int numeroHabitacion)
{
    if (numeroHabitacion != -1)
    {
        for (int i = 0; i < (int)this->habitaciones.size(); i++)
        {
            Habitacion *habitacion = &this->habitaciones.at(i);

            if (habitacion->getNumeroHabitacion() == numeroHabitacion)
            {
                this->ventanaEstadoHabitacion->setHabitacion(habitacion);
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
        for (int i = 0; i < (int)this->reservas.size(); i++)
        {
            Reserva *reserva = &this->reservas.at(i);

            if (reserva->getNumeroConfirmacion() == numeroReserva)
            {
                this->ventanaInfoReserva->setReserva(reserva);
                this->ventanaInfoReserva->mostrar();
            }
        }
    }
}

void VentanaPrincipal::modificarReserva(int numeroReserva)
{
    ui->centralwidget->setDisabled(true);

    for (int i = 0; i < (int)this->reservas.size(); i++)
    {
        Reserva *reserva = &this->reservas.at(i);
        if (reserva->getNumeroConfirmacion() == numeroReserva)
        {
            this->ventanaNuevaReserva->abrirVentana(reserva);
            break;
        }
    }

    this->ventanaNuevaReserva->show();
}

void VentanaPrincipal::aniadirGasto(int numeroReserva)
{
    for (int i = 0; i < (int)this->reservas.size(); i++)
    {
        Reserva *reserva = &this->reservas.at(i);
        if (reserva->getNumeroConfirmacion() == numeroReserva)
        {
            this->ventanaNuevoGasto->setReserva(reserva);
            this->ventanaNuevoGasto->mostrar();
            break;
        }
    }
}

void VentanaPrincipal::nuevoCliente()
{
    ui->centralwidget->setDisabled(true);
    this->ventanaNuevoCliente->show();
    this->ventanaNuevoCliente->abrirVentana();
}


void VentanaPrincipal::nuevaHabitacion()
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


void VentanaPrincipal::actualizarVectores(bool actualizar)
{
    if (actualizar)
    {
        this->llenarInfoDatos();
        this->llenarInfoReservas();
    }
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


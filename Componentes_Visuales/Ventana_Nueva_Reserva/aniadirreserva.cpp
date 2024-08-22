#include "aniadirreserva.h"
#include "ui_aniadirreserva.h"

AniadirReserva::AniadirReserva(vector<Cliente> *clientes, vector<Habitacion> *habitaciones,
                               vector<Reserva> *reservas, QWidget *parent, ControladorBD *controladorBD)
    : QDialog(parent)
    , ui(new Ui::AniadirReserva)
{
    ui->setupUi(this);

    this->clientes = clientes;
    this->habitaciones = habitaciones;
    this->reservas = reservas;
    this->controladorBD = controladorBD;
    this->ventanaAbierta = false;

    connect(ui->pushButtonCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(this, SIGNAL(rejected()), this, SLOT(cerrar()));
    connect(ui->checkBoxHabitacion, SIGNAL(stateChanged(int)), this, SLOT(actualizarCoste()));
    connect(ui->comboBoxNumero, SIGNAL(currentTextChanged(QString)), this, SLOT(actualizarCoste()));
    connect(ui->spinBoxNoches, SIGNAL(valueChanged(int)), this, SLOT(actualizarCoste()));
    connect(ui->comboBoxPiso, SIGNAL(currentTextChanged(QString)), this, SLOT(actualizarNumerosHabitaciones()));
    connect(ui->comboBoxEstado, SIGNAL(currentTextChanged(QString)), this, SLOT(actualizarNumerosHabitaciones()));
    connect(ui->dateEditInicio, SIGNAL(dateChanged(QDate)), this, SLOT(actualizarNumerosHabitaciones()));
    connect(ui->spinBoxNoches, SIGNAL(valueChanged(int)), this, SLOT(actualizarNumerosHabitaciones()));
    connect(ui->comboBoxEstado, SIGNAL(currentTextChanged(QString)), this, SLOT(activarSeleccionFecha()));
}

AniadirReserva::~AniadirReserva()
{
    delete ui;
}

void AniadirReserva::abrirVentana()
{
    this->rellenarComboBoxClientes();
    this->rellenarPisosHabitaciones();

    ui->dateEditInicio->setDate(QDate::currentDate());

    this->ventanaAbierta = true;
}

void AniadirReserva::limpiarVentana()
{
    ui->comboBoxEstado->setCurrentIndex(0);
    ui->lineEditCliente->clear();
    ui->comboBoxCliente->setCurrentIndex(0);
    ui->checkBoxHabitacion->setChecked(false);
    ui->spinBoxNoches->setValue(ui->spinBoxNoches->minimum());
    ui->lineEditCoste->setText("0,00 €");

    this->rellenarPisosHabitaciones();
}

bool AniadirReserva::verificarDisponibilidadHabitacion(int numeroHabitacion, QDate inicio, int dias)
{
    for (Reserva reserva: *this->reservas)
    {
        if (reserva.tieneHabitacion() && reserva.getNumeroHabitacion() == numeroHabitacion)
        {
            if(reserva.getEstadoReserva() == "En Estadía")
            {
                if (reserva.getFechaFin() > inicio)
                    return false;
            }

            else if (reserva.getEstadoReserva() == "Confirmado")
            {
                if (reserva.getFechaInicio() <= inicio && reserva.getFechaFin() > inicio)
                    return false;

                if (reserva.getFechaInicio() >= inicio && reserva.getFechaInicio() < inicio.addDays(dias))
                    return false;
            }
        }
    }

    return true;
}

void AniadirReserva::cerrar()
{
    if (this->ventanaAbierta)
    {
        this->limpiarVentana();
        this->ventanaAbierta = false;
        emit this->cerrarVentana(true);
    }
}

void AniadirReserva::actualizarCoste()
{
    QString valor = "0,00";

    if (ui->checkBoxHabitacion->isChecked())
    {
        int numeroHabitacion = ui->comboBoxNumero->currentText().toInt();
        int cantidadNoches = ui->spinBoxNoches->value();

        for (Habitacion habitacion: *this->habitaciones)
        {
            if (habitacion.getNumeroHabitacion() == numeroHabitacion)
            {
                int costePorNoche = habitacion.getCostePorNoche();

                valor = QString::number((costePorNoche * cantidadNoches));
            }
        }
    }

    ui->lineEditCoste->setText((valor+" €"));
}

void AniadirReserva::on_pushButtonAniadir_clicked()
{
    QString estado = ui->comboBoxEstado->currentText();
    int noches = ui->spinBoxNoches->value();
    int coste = ui->lineEditCoste->text().split(" ")[0].toFloat();

    QDate inicio;
    if (ui->comboBoxEstado->currentText() == "Confirmado")
        inicio = ui->dateEditInicio->date();
    else if (ui->comboBoxEstado->currentText() == "En Estadía")
        inicio = QDate::currentDate();
    else
        inicio.setDate(1970, 1, 1);

    QDate fin;
    if (inicio.year() != 1970)
        fin = inicio.addYears(noches);
    else
        fin.setDate(1970, 1, 1);

    QString cliente = ui->comboBoxCliente->currentText();
    int clienteID = cliente.split(' ')[0].toInt();

    int habitacion = -1;
    if (ui->checkBoxHabitacion->isChecked())
        habitacion = ui->comboBoxNumero->currentText().toInt();

    Reserva *nuevaReserva = nullptr;

    try{
        nuevaReserva = this->controladorBD->crearReserva(estado, inicio, fin, noches, clienteID, coste, habitacion);
    }
    catch(exception &ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }

    if (nuevaReserva != nullptr)
    {
        this->limpiarVentana();
        this->reservas->push_back(*nuevaReserva);
        QMessageBox::information(this, "Exito", "Nueva reserva añadida");
    }
}

void AniadirReserva::on_checkBoxHabitacion_stateChanged(int arg1)
{
    qDebug() << arg1;

    if(arg1)
        ui->frameHabitacion->setEnabled(true);

    else
        ui->frameHabitacion->setEnabled(false);
}

void AniadirReserva::rellenarComboBoxClientes()
{
    int sizeComboBox = ui->comboBoxCliente->count();

    for (int i = 0; i < (int)this->clientes->size(); i++)
    {
        Cliente cliente = this->clientes->at(i);

        int clienteID = cliente.getIdentificador();
        QString clienteNombre = cliente.getNombre();

        QString mensaje = QString::number(clienteID) + " - " + clienteNombre;

        if (i < sizeComboBox)
        {
            if (ui->comboBoxCliente->itemText(i) != mensaje)
                ui->comboBoxCliente->setItemText(i, mensaje);
        }
        else
            ui->comboBoxCliente->insertItem(i, mensaje);
    }
}

void AniadirReserva::rellenarComboBoxClientes(set<int> *clientesID)
{
    ui->comboBoxCliente->clear();

    for (Cliente cliente: *this->clientes)
    {
        int id = cliente.getIdentificador();

        if(clientesID->count(id) == 1)
        {
            QString clienteNombre = cliente.getNombre();

            QString mensaje = QString::number(id) + " - " + clienteNombre;

            ui->comboBoxCliente->addItem(mensaje);
        }
    }
}

void AniadirReserva::rellenarPisosHabitaciones()
{
    ui->comboBoxPiso->clear();

    set <int> pisos;

    for (Habitacion habitacion: *this->habitaciones)
    {
        int pisoHabitacion = habitacion.getPiso();

        if(pisos.count(pisoHabitacion) == 0)
            ui->comboBoxPiso->addItem(QString::number(pisoHabitacion));

        pisos.insert(pisoHabitacion);
    }
}


void AniadirReserva::on_lineEditCliente_textChanged(const QString &arg1)
{
    QString busquedaClientes = arg1.trimmed();

    if (busquedaClientes.isEmpty())
        this->rellenarComboBoxClientes();

    else
    {
        set <int> clientesID;

        bool esEntero;
        int numeroCliente = busquedaClientes.toInt(&esEntero);

        if (esEntero)
        {
            QString numeroString = QString::number(numeroCliente);

            for (Cliente cliente: *this->clientes)
            {
                QString clienteStringID = QString::number(cliente.getIdentificador());

                if (clienteStringID.startsWith(numeroString))
                    clientesID.insert(cliente.getIdentificador());
            }
        }

        else
        {
            for (Cliente cliente: *this->clientes)
            {
                QString clienteNombre = cliente.getNombre();

                if (clienteNombre.contains(busquedaClientes))
                    clientesID.insert(cliente.getIdentificador());
            }
        }

        this->rellenarComboBoxClientes(&clientesID);
    }
}

void AniadirReserva::actualizarNumerosHabitaciones()
{
    ui->comboBoxNumero->clear();

    int piso = ui->comboBoxPiso->currentText().toInt();

    for (Habitacion habitacion: *this->habitaciones)
    {
        if ((habitacion.getPiso() == piso) && !habitacion.getEnArreglos())
        {
            if (ui->comboBoxEstado->currentText() == "En Estadía")
            {
                    if (!this->verificarDisponibilidadHabitacion(habitacion.getNumeroHabitacion(), QDate::currentDate(),
                                                                ui->spinBoxNoches->value()))
                        continue;
            }

            else if (ui->comboBoxEstado->currentText() == "Confirmado")
            {
                if (!this->verificarDisponibilidadHabitacion(habitacion.getNumeroHabitacion(), ui->dateEditInicio->date(),
                                                             ui->spinBoxNoches->value()))
                    continue;
            }

            ui->comboBoxNumero->addItem(QString::number(habitacion.getNumeroHabitacion()));
        }
    }
}

void AniadirReserva::activarSeleccionFecha()
{
    if (ui->comboBoxEstado->currentText() == "Confirmado")
        ui->dateEditInicio->setEnabled(true);

    else
        ui->dateEditInicio->setEnabled(false);
}


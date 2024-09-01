#include "registrarsalida.h"
#include "ui_registrarsalida.h"

RegistrarSalida::RegistrarSalida(vector<Reserva> *reservas, ControladorBD *controladorBD, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistrarSalida)
{
    ui->setupUi(this);

    this->reservas = reservas;
    this->controladorBD = controladorBD;

    this->buscarClientes();
    this->rellenarInformacionReserva();

    connect(ui->pushButtonRegistrar, SIGNAL(clicked(bool)), this, SLOT(registrar()));
    connect(ui->pushButtonCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(this, SIGNAL(rejected()), this, SLOT(cerrar()));
    connect(ui->lineEditCliente, SIGNAL(textChanged(QString)), this, SLOT(buscarClientes(QString)));
    connect(ui->comboBoxCliente, SIGNAL(currentTextChanged(QString)), this, SLOT(rellenarInformacionReserva()));
}

RegistrarSalida::~RegistrarSalida()
{
    delete ui;
}

void RegistrarSalida::abrirVentana()
{
    this->ventanaAbierta = true;
}

void RegistrarSalida::limpiarVentana()
{
    ui->lineEditCliente->clear();
    ui->comboBoxCliente->setCurrentIndex(0);
}

void RegistrarSalida::establecerCliente(QString cliente)
{
    ui->lineEditCliente->setText(cliente);
}

void RegistrarSalida::cerrar()
{
    if (this->ventanaAbierta)
    {
        this->limpiarVentana();
        this->ventanaAbierta = false;
        emit this->cerrarVentana(true);
    }
}

void RegistrarSalida::rellenarComboBoxClientes()
{
    ui->comboBoxCliente->clear();

    for (Reserva reserva: *this->reservas)
    {
        if((reserva.getEstadoReserva() == "En Estadía") && (reserva.getFechaFin() == QDate::currentDate()))
        {
            int clienteID = reserva.getClienteID();
            QString clienteNombre = reserva.getClienteNombre();

            QString mensaje = QString::number(clienteID) + " - " + clienteNombre;


            ui->comboBoxCliente->addItem(mensaje);
        }
    }
}

void RegistrarSalida::rellenarComboBoxClientes(set<int> *clientesID)
{
    ui->comboBoxCliente->clear();

    for (Reserva reserva: *this->reservas)
    {
        int id = reserva.getClienteID();

        if(clientesID->count(id) == 1)
        {
            QString clienteNombre = reserva.getClienteNombre();

            QString mensaje = QString::number(id) + " - " + clienteNombre;

            ui->comboBoxCliente->addItem(mensaje);
        }
    }
}

void RegistrarSalida::buscarClientes(QString cliente)
{
    QString busquedaClientes = cliente.trimmed();

    if (busquedaClientes.isEmpty())
        this->rellenarComboBoxClientes();

    else
    {
        set<int> clientesID;

        bool esEntero;
        int numeroCliente = busquedaClientes.toInt(&esEntero);

        if (esEntero)
        {
            QString numeroString = QString::number(numeroCliente);

            for (Reserva reserva: *this->reservas)
            {
                if((reserva.getEstadoReserva() == "En Estadía") && (reserva.getFechaFin() == QDate::currentDate()))
                {
                    QString clienteStringID = QString::number(reserva.getClienteID());

                    if (clienteStringID.startsWith(numeroString))
                        clientesID.insert(reserva.getClienteID());
                }
            }
        }

        else
        {
            for (Reserva reserva: *this->reservas)
            {
                if((reserva.getEstadoReserva() == "En Estadía") && (reserva.getFechaFin() == QDate::currentDate()))
                {
                    QString clienteNombre = reserva.getClienteNombre();

                    if (clienteNombre.contains(busquedaClientes))
                        clientesID.insert(reserva.getClienteID());
                }
            }
        }

        this->rellenarComboBoxClientes(&clientesID);
    }
}

void RegistrarSalida::rellenarInformacionReserva()
{
    int clienteID = ui->comboBoxCliente->currentText().split(" ")[0].toInt();
    QString informacion = "";

    for (Reserva reserva: *this->reservas)
    {
        if((reserva.getEstadoReserva() == "En Estadía") && (reserva.getClienteID() == clienteID) && (reserva.getFechaFin() == QDate::currentDate()))
        {
            informacion += "Número de Confirmación: ";
            informacion += QString::number(reserva.getNumeroConfirmacion());
            informacion += '\n';

            informacion += "Cliente: ";
            informacion += reserva.getClienteNombre();
            informacion += '\n';

            informacion += "Número de Habitación: ";
            informacion += QString::number(reserva.getNumeroHabitacion());
            informacion += '\n';

            informacion += "Cantidad de noches: ";
            informacion += QString::number(reserva.getCantidadNoches());
            informacion += '\n';

            informacion += "Fecha de inicio: ";
            informacion += reserva.getFechaInicio().toString();
            informacion += '\n';

            informacion += "\nDesglose de Gastos: \n";
            for (pair <QString, float> gasto: reserva.getDesgloseGastos())
            {
                informacion += "- ";
                informacion += gasto.first;
                informacion += ": ";
                informacion += QString::number(gasto.second);
                informacion += " € \n";
            }
            informacion += '\n';

            informacion += "Costo Total: ";
            informacion += QString::number(reserva.getImporte());
            informacion += '\n';
        }
    }

    ui->textEditInformacion->setText(informacion);
}

void RegistrarSalida::registrar()
{
    if (ui->comboBoxCliente->currentText().trimmed() == "")
        QMessageBox::warning(this, "Error", "Es necesario seleccionar un cliente correcto.");

    QString primeraLineaText = ui->textEditInformacion->toPlainText().split('\n')[0];
    int numeroConfirmacion = primeraLineaText.split(": ")[1].toInt();

    Reserva *reserva = nullptr;
    for (int i = 0; i < (int)this->reservas->size(); i++)
    {
        if (this->reservas->at(i).getNumeroConfirmacion() == numeroConfirmacion)
        {
            reserva = &this->reservas->at(i);
            break;
        }
    }

    try{
        *reserva = *this->controladorBD->cambiarEstadoReserva(
            numeroConfirmacion,
            "Estancia Finalizada"
            );

        emit registrado(true);
        QMessageBox::information(this, "Exito", "Salida registrada.");
    }
    catch (exception &ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }
}

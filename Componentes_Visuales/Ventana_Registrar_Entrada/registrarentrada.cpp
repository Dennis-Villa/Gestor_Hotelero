#include "registrarentrada.h"
#include "ui_registrarentrada.h"

RegistrarEntrada::RegistrarEntrada(vector<Reserva> *reservas, ControladorBD *controladorBD, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistrarEntrada)
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

RegistrarEntrada::~RegistrarEntrada()
{
    delete ui;
}

void RegistrarEntrada::abrirVentana()
{
    this->ventanaAbierta = true;
}

void RegistrarEntrada::limpiarVentana()
{
    ui->lineEditCliente->clear();
    ui->comboBoxCliente->setCurrentIndex(0);
}

void RegistrarEntrada::establecerCliente(QString cliente)
{
    ui->lineEditCliente->setText(cliente);
}

void RegistrarEntrada::cerrar()
{
    if (this->ventanaAbierta)
    {
        this->limpiarVentana();
        this->ventanaAbierta = false;
        emit this->cerrarVentana(true);
    }
}

void RegistrarEntrada::rellenarComboBoxClientes()
{
    ui->comboBoxCliente->clear();

    for (Reserva reserva: *this->reservas)
    {
        if((reserva.getEstadoReserva() == "Confirmado") &&  (reserva.getFechaInicio() == QDate::currentDate()))
        {
            int clienteID = reserva.getClienteID();
            QString clienteNombre = reserva.getClienteNombre();

            QString mensaje = QString::number(clienteID) + " - " + clienteNombre;


            ui->comboBoxCliente->addItem(mensaje);
        }
    }
}

void RegistrarEntrada::rellenarComboBoxClientes(set<int> *clientesID)
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

void RegistrarEntrada::buscarClientes(QString cliente)
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
                if((reserva.getEstadoReserva() == "Confirmado") &&  (reserva.getFechaInicio() == QDate::currentDate()))
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
                if((reserva.getEstadoReserva() == "Confirmado") &&  (reserva.getFechaInicio() == QDate::currentDate()))
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

void RegistrarEntrada::rellenarInformacionReserva()
{
    int clienteID = ui->comboBoxCliente->currentText().split(" ")[0].toInt();
    QString informacion = "";

    for (Reserva reserva: *this->reservas)
    {
        if((reserva.getClienteID() == clienteID) && (reserva.getFechaInicio() == QDate::currentDate()))
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

            informacion += "Fecha de finalizacion: ";
            informacion += reserva.getFechaFin().toString();
            informacion += '\n';

            informacion += "Costo de Estancia: ";
            informacion += QString::number(reserva.getImporte());
            informacion += '\n';
        }
    }

    ui->textEditInformacion->setText(informacion);
}

void RegistrarEntrada::registrar()
{
    if (ui->comboBoxCliente->currentText().trimmed() == "")
        QMessageBox::warning(this, "Error", "Es necesario seleccionar un cliente correcto.");

    QString primeraLineaText = ui->textEditInformacion->toPlainText().split('\n')[0];
    int numeroConfirmacion = primeraLineaText.split(": ")[1].toInt();

    Reserva *reserva = nullptr;
    for (int i = 0; i < (int)this->reservas->size(); i++)
    {
        if (this->reservas->at(i).getNumeroConfirmacion() == numeroConfirmacion)
            reserva = &this->reservas->at(i);
    }

    try{
        *reserva = *this->controladorBD->cambiarEstadoReserva(
            numeroConfirmacion,
            "En Estadía"
        );

        emit registrado(true);
        QMessageBox::information(this, "Exito", "Entrada registrada.");
    }
    catch (exception &ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }
}

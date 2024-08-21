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
}

AniadirReserva::~AniadirReserva()
{
    delete ui;
}

void AniadirReserva::abrirVentana()
{
    this->rellenarComboBoxClientes();
    this->ventanaAbierta = true;
}

void AniadirReserva::limpiarVentana()
{
    ui->comboBoxEstado->setCurrentIndex(0);
    ui->lineEditCliente->clear();
    ui->comboBoxCliente->setCurrentIndex(0);
    ui->spinBoxPiso->setValue(ui->spinBoxPiso->minimum());
    ui->spinBoxNumero->setValue(ui->spinBoxNumero->minimum());
    ui->checkBoxHabitacion->setChecked(false);
    ui->spinBoxNoches->setValue(ui->spinBoxNoches->minimum());
    ui->lineEditCoste->setText("0,00 €");
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

void AniadirReserva::on_pushButtonAniadir_clicked()
{
    QString estado = ui->comboBoxEstado->currentText();
    int noches = ui->spinBoxNoches->value();

    QString cliente = ui->lineEditCliente->text();
    int clienteID = cliente.toInt();

    int habitacion = -1;
    if (ui->checkBoxHabitacion->isChecked())
    {
        int piso = ui->spinBoxPiso->value();
        int numero = ui->spinBoxNumero->value();
        habitacion = piso * 100 + numero;
    }

    Reserva *nuevaReserva = nullptr;

    try{
        nuevaReserva = this->controladorBD->crearReserva(estado, noches, clienteID, habitacion);
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
        QString numeroString = QString::number(numeroCliente);

        if (esEntero)
        {
            for (Cliente cliente: *this->clientes)
            {
                QString clienteStringID = QString::number(cliente.getIdentificador());

                if (clienteStringID.startsWith(numeroString))
                    clientesID.insert(cliente.getIdentificador());
            }
        }

        this->rellenarComboBoxClientes(&clientesID);
    }
}


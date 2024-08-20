#include "aniadirreserva.h"
#include "ui_aniadirreserva.h"

AniadirReserva::AniadirReserva(vector<Reserva> *reservas, QWidget *parent, ControladorBD *controladorBD)
    : QDialog(parent)
    , ui(new Ui::AniadirReserva)
{
    ui->setupUi(this);

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


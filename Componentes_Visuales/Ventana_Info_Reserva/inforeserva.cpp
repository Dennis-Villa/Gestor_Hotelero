#include "inforeserva.h"
#include "ui_inforeserva.h"

InfoReserva::InfoReserva(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoReserva)
{
    ui->setupUi(this);

    this->limpiar();

    connect(ui->pushButtonCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
}

InfoReserva::~InfoReserva()
{
    delete ui;
}

void InfoReserva::mostrar()
{
    ui->lineEditNumeroConfirmacion->setText(QString::number(this->reserva->getNumeroConfirmacion()));
    ui->lineEditEstado->setText(this->reserva->getEstadoReserva());
    ui->lineEditCliente->setText(this->reserva->getClienteNombre());
    ui->lineEditNoches->setText(QString::number(this->reserva->getCantidadNoches()));
    ui->lineEditImporte->setText(QString::number(this->reserva->getImporte()) + " €");

    if (this->reserva->getFechaInicio().year() == 1970)
        ui->dateEditInicio->setDisabled(true);
    else
    {
        ui->dateEditInicio->setDisabled(false);
        ui->dateEditInicio->setDate(this->reserva->getFechaInicio());
    }

    if (this->reserva->getFechaFin().year() == 1970)
        ui->dateEditFin->setDisabled(true);
    else
    {
        ui->dateEditFin->setDisabled(false);
        ui->dateEditFin->setDate(this->reserva->getFechaFin());
    }

    int numeroHabitacion = this->reserva->getNumeroHabitacion();

    if (numeroHabitacion == -1)
        ui->lineEditHabitacion->setText("");
    else
        ui->lineEditHabitacion->setText(QString::number(numeroHabitacion));

    QString gastosStr = "";
    for (pair<QString, float> gasto: this->reserva->getDesgloseGastos())
    {
        gastosStr += "- ";
        gastosStr += gasto.first;
        gastosStr += ": ";
        gastosStr += QString::number(gasto.second);
        gastosStr += " €\n";
    }
    ui->textEditGastos->setText(gastosStr);

    this->show();
}

void InfoReserva::cerrar()
{
    this->limpiar();
    this->close();
}

void InfoReserva::limpiar()
{
    ui->lineEditNumeroConfirmacion->clear();
    ui->lineEditEstado->clear();
    ui->lineEditCliente->clear();
    ui->lineEditHabitacion->clear();
    ui->dateEditInicio->setDate(QDate::currentDate());
    ui->dateEditFin->setDate(QDate::currentDate());
    ui->lineEditImporte->clear();
    ui->lineEditNoches->clear();
    ui->textEditGastos->clear();
}

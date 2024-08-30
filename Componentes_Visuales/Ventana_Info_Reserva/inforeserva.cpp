#include "inforeserva.h"
#include "ui_inforeserva.h"

InfoReserva::InfoReserva(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoReserva)
{
    ui->setupUi(this);

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
    ui->lineEditHabitacion->setText(QString::number(this->reserva->getNumeroHabitacion()));
    ui->lineEditInicio->setText(this->reserva->getFechaInicioString());
    ui->lineEditFin->setText(this->reserva->getFechaFinString());
    ui->lineEditNoches->setText(QString::number(this->reserva->getCantidadNoches()));
    ui->lineEditImporte->setText(QString::number(this->reserva->getImporte()));

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
    ui->lineEditInicio->clear();
    ui->lineEditFin->clear();
    ui->lineEditImporte->clear();
    ui->lineEditNoches->clear();
    ui->textEditGastos->clear();
}

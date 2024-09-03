#include "aniadirgasto.h"
#include "ui_aniadirgasto.h"

AniadirGasto::AniadirGasto(ControladorBD *controladorBD, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AniadirGasto)
{
    ui->setupUi(this);

    this->controladorBD = controladorBD;
    this->reserva = nullptr;

    connect(ui->pushButtonCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->pushButtonAniadir, SIGNAL(clicked(bool)), this, SLOT(aniadir()));
}

AniadirGasto::~AniadirGasto()
{
    delete ui;
}

void AniadirGasto::mostrar()
{
    if (this->reserva != nullptr)
    {
        QString mensajeLabel = ("Nuevo gasto para la habitación "
                                + QString::number(reserva->getNumeroHabitacion()));
        ui->labelHabitacion->setText(mensajeLabel);

        ui->textEditDesglose->setText(reserva->convertirGastosATexto());
    }

    this->open();
}

void AniadirGasto::limpiar()
{
    ui->labelHabitacion->clear();
    ui->lineEditDescripcion->clear();
    ui->spinBoxCoste->setValue(0);
    ui->textEditDesglose->clear();

    this->reserva = nullptr;
}

void AniadirGasto::cerrar()
{
    this->limpiar();
    this->close();
}

void AniadirGasto::aniadir()
{
    if (this->reserva != nullptr)
    {
        QString gasto = ui->lineEditDescripcion->text();
        int coste = ui->spinBoxCoste->value();

        try
        {
            *this->reserva = *this->controladorBD->aniadirGasto(reserva->getNumeroConfirmacion(), gasto, coste);

            emit actualizar(true);
            QMessageBox::information(this, "Exito", "Gasto añadido correctamente");
        }
        catch(exception &ex)
        {
            QMessageBox::critical(this, "Error", ex.what());
        }
    }

    ui->lineEditDescripcion->clear();
    ui->spinBoxCoste->setValue(0);
    this->mostrar();
}

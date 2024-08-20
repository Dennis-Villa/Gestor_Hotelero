#include "aniadirreserva.h"
#include "ui_aniadirreserva.h"

AniadirReserva::AniadirReserva(QWidget *parent, ControladorBD *controladorBD)
    : QDialog(parent)
    , ui(new Ui::AniadirReserva)
{
    ui->setupUi(this);

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

void AniadirReserva::cerrar()
{
    if (this->ventanaAbierta)
    {
        //this->limpiarVentana();
        this->ventanaAbierta = false;
        emit this->cerrarVentana(true);
    }
}

void AniadirReserva::on_pushButtonAniadir_clicked()
{
    QString estado = ui->comboBoxEstado->currentText();
    QString cliente = ui->lineEditCliente->text();
    int piso = ui->spinBoxPiso->value();
    int numero = ui->spinBoxNumero->value();
    int noches = ui->spinBoxNoches->value();

    int clienteID = cliente.toInt();
    int habitacion = piso * 100 + numero;

    try{
        this->controladorBD->crearReserva(estado, noches, clienteID, habitacion);

        QMessageBox::information(this, "Exito", "Reserva añadida a la base de datos");
    }
    catch(exception &ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }
}


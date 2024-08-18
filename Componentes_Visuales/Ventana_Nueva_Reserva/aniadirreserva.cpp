#include "aniadirreserva.h"
#include "ui_aniadirreserva.h"

AniadirReserva::AniadirReserva(QWidget *parent, ControladorBD *controladorBD)
    : QDialog(parent)
    , ui(new Ui::AniadirReserva)
{
    ui->setupUi(this);

    this->controladorBD = controladorBD;
    this->ventanaAbierta = false;

    connect(ui->pushButtonCerrar, SIGNAL(clicked()), this, SLOT(cerrar()));
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

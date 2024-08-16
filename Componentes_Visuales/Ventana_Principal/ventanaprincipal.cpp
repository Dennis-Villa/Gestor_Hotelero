#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    ui->dateEditActual->setDate(this->fechaActual);

    connect(this->ventanaNuevoCliente, &AniadirCliente::cerrarAniadirClientes, this, &VentanaPrincipal::cerrarNuevoCliente);
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::cerrarNuevoCliente(bool cerrar)
{
    if (cerrar)
    {
        this->ventanaNuevoCliente->close();
        ui->centralwidget->setDisabled(false);
    }
}

void VentanaPrincipal::on_actionCliente_triggered()
{
    ui->centralwidget->setDisabled(true);
    this->ventanaNuevoCliente->show();
    this->ventanaNuevoCliente->abrirVentana();
}


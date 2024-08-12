#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    ui->dateEditActual->setDate(this->fechaActual);
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

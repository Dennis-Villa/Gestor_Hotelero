#include "aniadircliente.h"
#include "ui_aniadircliente.h"

AniadirCliente::AniadirCliente(QWidget *parent, ControladorBD *controladorBD)
    : QDialog(parent)
    , ui(new Ui::AniadirCliente)
{
    ui->setupUi(this);

    this->controladorBD = controladorBD;
    this->ventanaAbierta = false;

    connect(ui->pushButtonAniadir, SIGNAL(clicked(bool)), this, SLOT(aniadirCliente()));
    connect(ui->pushButtonCerrar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(this, SIGNAL(rejected()), this, SLOT(cerrar()));
}

AniadirCliente::~AniadirCliente()
{
    delete ui;
}

void AniadirCliente::abrirVentana()
{
    this->ventanaAbierta = true;
}

void AniadirCliente::limpiarVentana()
{
    ui->lineEditNombre->clear();
    ui->lineEditEmail->clear();
    ui->lineEditTelefono->clear();
    ui->lineEditNacionalidad->clear();
}

void AniadirCliente::aniadirCliente()
{
    QString nombre = ui->lineEditNombre->text();
    QString email = ui->lineEditEmail->text();
    QString telefono = ui->lineEditTelefono->text();
    QString nacionalidad = ui->lineEditNacionalidad->text();

    Cliente *nuevoCliente = nullptr;

    try {
        nuevoCliente = controladorBD->crearCliente(nombre, email, telefono, nacionalidad);
    }
    catch (exception &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }

    if (nuevoCliente != nullptr)
    {
        this->limpiarVentana();
        QMessageBox::information(this, "Exito", "Nuevo cliente añadido.");
    }
}


void AniadirCliente::cerrar()
{
    if (this->ventanaAbierta)
    {
        this->limpiarVentana();
        this->ventanaAbierta = false;
        emit this->cerrarVentana(true);
    }
}


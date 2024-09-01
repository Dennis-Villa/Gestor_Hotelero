#include "aniadirhabitacion.h"
#include "ui_aniadirhabitacion.h"

AniadirHabitacion::AniadirHabitacion(vector<Habitacion> *habitaciones, QWidget *parent, ControladorBD *controladorBD)
    : QDialog(parent)
    , ui(new Ui::AniadirHabitacion)
{
    ui->setupUi(this);

    this->habitaciones = habitaciones;
    this->controladorBD = controladorBD;
    this->ventanaAbierta = false;

    connect(ui->pushButtonAniadir, SIGNAL(clicked()), this, SLOT(aniadirHabitacion()));
    connect(ui->pushButtonCerrar, SIGNAL(clicked()), this, SLOT(cerrar()));
    connect(this, SIGNAL(rejected()), this, SLOT(cerrar()));
}

AniadirHabitacion::~AniadirHabitacion()
{
    delete ui;
}

void AniadirHabitacion::abrirVentana()
{
    this->ventanaAbierta = true;
}

void AniadirHabitacion::limpiarVentana()
{
    ui->spinBoxPiso->setValue(ui->spinBoxPiso->minimum());
    ui->spinBoxNumero->setValue(ui->spinBoxNumero->minimum());
    ui->comboBoxTipo->setCurrentIndex(0);
    ui->spinBoxTamanio->setValue(ui->spinBoxTamanio->minimum());
    ui->spinBoxCamas->setValue(ui->spinBoxCamas->minimum());
    ui->doubleSpinBoxCoste->setValue(ui->doubleSpinBoxCoste->minimum());
}

void AniadirHabitacion::aniadirHabitacion()
{
    int piso = ui->spinBoxPiso->value();
    int numero = ui->spinBoxNumero->value();
    QString tipo = ui->comboBoxTipo->currentText();
    int tamanio = ui->spinBoxTamanio->value();
    int camas = ui->spinBoxCamas->value();
    double coste = ui->doubleSpinBoxCoste->value();

    int numeroHabitacion = piso * 100 + numero;

    Habitacion *nuevaHabitacion = nullptr;

    try {
        nuevaHabitacion = controladorBD->crearHabitacion(numeroHabitacion, tipo,
                                                        tamanio, camas, coste);
    }
    catch (exception &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }

    if (nuevaHabitacion != nullptr)
    {
        this->limpiarVentana();
        this->habitaciones->push_back(*nuevaHabitacion);
        emit aniadido(true);
        QMessageBox::information(this, "Exito", "Nueva Habitación añadida.");
    }
}

void AniadirHabitacion::cerrar()
{
    if (this->ventanaAbierta)
    {
        this->limpiarVentana();
        this->ventanaAbierta = false;
        emit this->cerrarVentana(true);
    }
}

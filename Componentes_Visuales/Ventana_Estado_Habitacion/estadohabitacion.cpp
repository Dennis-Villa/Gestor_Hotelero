#include "estadohabitacion.h"
#include "ui_estadohabitacion.h"

EstadoHabitacion::EstadoHabitacion(ControladorBD *controladorBD, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EstadoHabitacion)
{
    ui->setupUi(this);

    this->controladorBD = controladorBD;

    connect(ui->pushButtonCancelar, SIGNAL(clicked(bool)), this, SLOT(cerrar()));
    connect(ui->pushButtonModificar, SIGNAL(clicked(bool)), this, SLOT(modificar()));
}

EstadoHabitacion::~EstadoHabitacion()
{
    delete ui;
}

void EstadoHabitacion::setHabitacion(Habitacion *habitacion)
{
    this->habitacion = habitacion;
}

void EstadoHabitacion::mostrar()
{
    Habitacion *habitacionActual = this->habitacion;

    if (habitacionActual != nullptr)
    {
        ui->labelNumeroHabitacion->setText(QString::number(habitacionActual->getNumeroHabitacion()));
        ui->spinBoxCamas->setValue(habitacionActual->getNumeroCamas());
        ui->doubleSpinBoxCoste->setValue(habitacionActual->getCostePorNoche());

        ui->checkBoxDisponible->setChecked(habitacionActual->getDisponible());
        ui->checkBoxEnArreglos->setChecked(habitacionActual->getEnArreglos());

        int indiceTipo = ui->comboBoxTipo->findText(habitacionActual->getTipoHabitacion());
        ui->comboBoxTipo->setCurrentIndex(indiceTipo);
    }

    this->open();

    // Habitacion *habitacionActual = nullptr;

    // ui->labelNumeroHabitacion->setText(QString::number(habitacionActual->getNumeroHabitacion()));
    // ui->spinBoxCamas->setValue(habitacionActual->getNumeroCamas());
    // ui->doubleSpinBoxCoste->setValue(habitacionActual->getCostePorNoche());

    // ui->checkBoxDisponible->setChecked(habitacionActual->getDisponible());
    // ui->checkBoxEnArreglos->setChecked(habitacionActual->getEnArreglos());

    // this->open();
}

void EstadoHabitacion::limpiar()
{
    ui->labelNumeroHabitacion->setText("");
    ui->checkBoxDisponible->setChecked(false);
    ui->checkBoxEnArreglos->setChecked(false);
    ui->spinBoxCamas->setValue(1);
    ui->doubleSpinBoxCoste->setValue(0.00);
}

void EstadoHabitacion::cerrar()
{
    this->limpiar();
    this->close();
}

void EstadoHabitacion::modificar()
{
    Habitacion *habitacion = this->habitacion;

    try
    {
        this->habitacion->setTipoHabitacion(ui->comboBoxTipo->currentText());
        this->habitacion->setNumeroCamas(ui->spinBoxCamas->value());
        this->habitacion->setCostePorNoche(ui->doubleSpinBoxCoste->value());

        habitacion->setEnArreglos(ui->checkBoxEnArreglos->isChecked());
        habitacion->setDisponible(ui->checkBoxDisponible->isChecked());

        *habitacion = *this->controladorBD->cambiarEstadoHabitacion(habitacion);

        emit actualizar(true);

        QMessageBox::information(this, "Exito", "Habitación modificada exitosamente.");
    }
    catch (exception &ex)
    {
        QMessageBox::critical(this, "Error", ex.what());
    }




    // Habitacion *habitacionActual = nullptr;

    // for (int i = 0; i < (int)this->habitaciones->size(); i++)
    // {
    //     if (this->habitaciones->at(i).getNumeroHabitacion() == this->numeroHabitacion)
    //     {
    //         habitacionActual = &this->habitaciones->at(i);
    //         break;
    //     }
    // }

    // try
    // {
    //     habitacionActual->setTipoHabitacion(ui->comboBoxTipo->currentText());
    //     habitacionActual->setNumeroCamas(ui->spinBoxCamas->value());
    //     habitacionActual->setCostePorNoche(ui->doubleSpinBoxCoste->value());

    //     habitacionActual->setEnArreglos(ui->checkBoxEnArreglos->isChecked());
    //     habitacionActual->setDisponible(ui->checkBoxDisponible->isChecked());

    //     *habitacionActual = *this->controladorBD->cambiarEstadoHabitacion(habitacionActual);

    //     emit actualizar(true);

    //     QMessageBox::information(this, "Exito", "Habitación modificada exitosamente.");
    // }
    // catch (exception &ex)
    // {
    //     QMessageBox::critical(this, "Error", ex.what());
    // }
}

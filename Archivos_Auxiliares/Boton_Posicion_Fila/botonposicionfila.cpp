#include "botonposicionfila.h"

BotonPosicionFila::BotonPosicionFila(QWidget *parent)
    : QPushButton(parent)
{}

BotonPosicionFila::BotonPosicionFila(QString texto, QWidget *parent)
    : QPushButton(texto, parent)
{}

BotonPosicionFila::BotonPosicionFila(int id, QWidget *parent)
    : QPushButton(parent)
{
    this->setID(id);
}

BotonPosicionFila::BotonPosicionFila(QString texto, int id, QWidget *parent)
    : QPushButton(texto, parent)
{
    this->setID(id);
}

void BotonPosicionFila::setID(int ID)
{
    this->id = ID;

    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick()));
}

void BotonPosicionFila::handleClick()
{
    emit clicked(this->id);
}

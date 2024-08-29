#include "botoneliminarfila.h"

BotonEliminarFila::BotonEliminarFila(QWidget *parent)
    : QPushButton(parent)
{}

BotonEliminarFila::BotonEliminarFila(QString texto, QWidget *parent)
    : QPushButton(texto, parent)
{}

BotonEliminarFila::BotonEliminarFila(int id, QWidget *parent)
    : QPushButton(parent)
{
    this->setID(id);
}

BotonEliminarFila::BotonEliminarFila(QString texto, int id, QWidget *parent)
    : QPushButton(texto, parent)
{
    this->setID(id);
}

void BotonEliminarFila::setID(int ID)
{
    this->id = ID;

    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleClick()));
}

void BotonEliminarFila::handleClick()
{
    emit clicked(this->id);
}

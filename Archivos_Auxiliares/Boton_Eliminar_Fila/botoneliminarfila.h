#ifndef BOTONELIMINARFILA_H
#define BOTONELIMINARFILA_H

#include <QPushButton>

class BotonEliminarFila : public QPushButton
{
    Q_OBJECT

public:
    explicit BotonEliminarFila(QWidget *parent = nullptr);
    explicit BotonEliminarFila(QString texto, QWidget *parent = nullptr);
    explicit BotonEliminarFila(int id, QWidget *parent = nullptr);
    explicit BotonEliminarFila(QString texto, int id, QWidget *parent = nullptr);

    void setID(int ID);

signals:
    void clicked(int);

private slots:
    void handleClick();

private:
    int id;
};

#endif // BOTONELIMINARFILA_H

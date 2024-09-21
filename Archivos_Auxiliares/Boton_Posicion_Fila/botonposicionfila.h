#ifndef BOTONPOSICIONFILA_H
#define BOTONPOSICIONFILA_H

#include <QPushButton>

class BotonPosicionFila : public QPushButton
{
    Q_OBJECT

public:
    explicit BotonPosicionFila(QWidget *parent = nullptr);
    explicit BotonPosicionFila(QString texto, QWidget *parent = nullptr);
    explicit BotonPosicionFila(int id, QWidget *parent = nullptr);
    explicit BotonPosicionFila(QString texto, int id, QWidget *parent = nullptr);

    void setID(int ID = -1);

signals:
    void clicked(int);

private slots:
    void handleClick();

private:
    int id;
};

#endif // BOTONPOSICIONFILA_H

#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QDateTime>

#include "Clases/ControladorBD/controladorbd.h"
#include "Componentes_Visuales/Ventana_Nuevo_Cliente/aniadircliente.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class VentanaPrincipal;
}
QT_END_NAMESPACE

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

    void cerrarNuevoCliente(bool cerrar = false);

private slots:
    void on_actionCliente_triggered();

private:
    Ui::VentanaPrincipal *ui;
    QDate fechaActual = QDate::currentDate();

    ControladorBD *controladorBD = new ControladorBD();
    AniadirCliente *ventanaNuevoCliente = new AniadirCliente(this, controladorBD);
};
#endif // VENTANAPRINCIPAL_H

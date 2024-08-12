#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QDateTime>

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

private:
    Ui::VentanaPrincipal *ui;
    QDate fechaActual = QDate::currentDate();
};
#endif // VENTANAPRINCIPAL_H

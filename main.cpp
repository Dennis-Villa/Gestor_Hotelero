#include "Componentes_Visuales\Ventana_Principal\ventanaprincipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaPrincipal w;
    w.setWindowState(Qt::WindowMaximized);

    w.show();
    return a.exec();
}

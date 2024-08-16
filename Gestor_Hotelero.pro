QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Archivos_Auxiliares\Funciones_Auxiliares.cpp \
    Clases\Cliente\cliente.cpp \
    Clases\Habitacion\habitacion.cpp \
    Clases\ControladorBD\controladorbd.cpp \
    main.cpp \
    Componentes_Visuales\Ventana_Principal\ventanaprincipal.cpp \
    Clases\Reserva\reserva.cpp

HEADERS += \
    Archivos_Auxiliares\Funciones_Auxiliares.h \
    Componentes_Visuales\Ventana_Principal\ventanaprincipal.h \
    Clases\Cliente\cliente.h \
    Clases\Habitacion\habitacion.h \
    Clases\Reserva\reserva.h \
    Clases\ControladorBD\controladorbd.h

FORMS += \
    Componentes_Visuales\Ventana_Principal\ventanaprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

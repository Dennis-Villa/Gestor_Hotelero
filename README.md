# Gestor_Hotelero

Un gestor basado en Qt y C++ para funciones de hostelería.

![Imagen de muestra](./Imagenes/Captura_Pantalla_Principal.PNG)

## Capacidades de Gestión

- Habitaciones del Hotel.
- Clientes Registrados.
- Historial de Reservas.

## Detalles Técnicos

Este proyecto fue desarrollado utilizando:

- Qt Creator 14.0.1 (Community)
- Qt 6.7.2
- C++ 17
- SQLite 3.46.0

## Descripción de Componentes

### Clases

En este directorio se encuentran los archivos que controlan la lógica basada en Programación Orientada a Objetos de la aplicación. Las clases que se gestionan aquí son:

- [Habitación](./Clases/Habitacion)
- [Cliente](./Clases/Cliente)
- [Reserva](./Clases/Reserva)
- [Controlador de Base de Datos](./Clases/ControladorBD)

### Componentes Visuales

En este directorio se encuentran los ficheros que controlan la parte visual de la aplicación y las interacciones entre varios componentes. Las ventanas que incluye el proyecto son:

- [Ventana Principal](./Componentes_Visuales/Ventana_Principal)
- [Nueva Habitación](./Componentes_Visuales/Ventana_Nueva_Habitacion)
- [Nuevo Cliente](./Componentes_Visuales/Ventana_Nuevo_Cliente)
- [Nueva Reserva](./Componentes_Visuales/Ventana_Nueva_Reserva)
- [Registrar Entrada](./Componentes_Visuales/Ventana_Registrar_Entrada)
- [Registrar Salida](./Componentes_Visuales/Ventana_Registrar_Salida)
- [Registrar Gasto](./Componentes_Visuales/Ventana_Nuevo_Gasto)
- [Estado de Habitación](./Componentes_Visuales/Ventana_Estado_Habitacion)
- [Información de Reserva](./Componentes_Visuales/Ventana_Info_Reserva)

### Archivos Auxiliares

En este directorio se encuentran ficheros que aportan funcionalidades de uso general a varios componentes de la aplicación. Los elementos que incluye son:
  
- [Botón con Posición de Fila](./Archivos_Auxiliares/Boton_Posicion_Fila)
- [Funciones Auxiliares](./Archivos_Auxiliares/Funciones_Auxiliares)
- Excepción de Reserva Vencida

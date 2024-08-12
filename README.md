# Gestor_Hotelero

Un gestor basado en Qt y C++ para funciones de hostelería.

## Capacidades previstas:

1. Llenado de habitaciones.
2. Diferenciar entre tipos de cliente (con servicios prepagados, etc).
3. Manejar importe del cliente:
    - Coste de estadía.
    - Minivar.
    - Servicios especiales de la habitación.
4. Manejar reservas.
5. Llevar balance de cuentas.
6. Gestionar habitaciones fuera de servicio.
7. Manejar características especiales de habitaciones:
    - Tamaño.
    - Numero y tamaño de camas.
    - Localización espacial.
    - Vistas.

## Posibles capacidades extra:

1. Gestionar personal del hotel.

## Desglose por pantallas:

### Pantalla Principal:

![Imagen de muestra](./Imagenes/img_dash@2x-1.png)

1. Sector Superior
    - Fecha.
    - Nueva reserva.
    - Resumen de eventos y ocupacion del dia.
    - Habitaciones fuera de servicio.

2. Sector inferior.
    - Informacion detallada:
        - Toda la informacion para el dia actual y el siguiente.
        - Llegadas.
        - Salidas.
        - Ocupacion

    - Actividad del dia:
        - Clientes registrados.
        - Ingresos totales.
        - Cancelaciones.

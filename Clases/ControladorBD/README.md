# Clase ControladorBD

Esta clase busca gestionar, utilizando Programación Orientada a Objetos, las propiedades y métodos necesarios para controlar una Base de Datos SQLite en función de las necesidades de una entidad hotelera.

## Elementos de la clase

### Atributos de la clase

|||
|---|---|
|QSqlDatabase|[bd](#bd-qsqldatabase)|

***

### Métodos Públicos

|Retorno|Método|
|---|---|
||[ControladorBD](#controladorbd)()|
||[~ControladorBD](#controladorbd-1)()|
|QSqlDatabase|[getBD](#bd-qsqldatabase)()|
|bool|[abreBD](#bool-abrebd)()|
|Cliente*|[crearCliente](#cliente-crearclienteqstring-nombre-qstring-email-qstring-telefono-qstring-nacionalidad)(QString nombre, QString email, QString telefono, QString nacionalidad)|
|Cliente*|[buscarCliente](#cliente-buscarclienteint-identificador)(int identificador)|
|vector<Cliente>|[getClientes](#vector-getclientes)()|
|Cliente*|[aniadirEstancia](#cliente-aniadirestanciacliente-cliente)(Cliente* cliente)|
|void|[eliminarCliente](#void-eliminarclienteint-identificador)(int identificador)|
|Habitacion*|[crearHabitacion](#habitacion-crearhabitacionint-numero-qstring-tipo-int-tamanio-int-camas-float-coste)(int numero, QString tipo, int tamanio, int camas, float coste)|
|Habitacion*|[buscarHabitacion](#habitacion-buscarhabitacionint-numero)(int numero)|
|void|[getHabitaciones](#vector-gethabitaciones)()|
|Habitacion*|[cambiarEstadoHabitacion](#habitacion-cambiarestadohabitacionhabitacion-habitacion)(Habitacion* habitacion)|
|Habitacion*|[cambiarDisponibilidadHabitacion](#habitacion-cambiardisponibilidadhabitacionint-numero-bool-disponible)(int numero, bool disponible)|
|Habitacion*|[cambiarEnArreglosHabitacion](#habitacion-cambiarenarregloshabitacionint-numero-bool-enarreglos)(int numero, bool enArreglos)|
|void|[eliminarHabitacion](#void-eliminarhabitacionint-numero)(int numero)|
|Reserva*|[crearReserva](#reserva-crearreservaqstring-estado-qdate-inicio-qdate-fin-int-noches-int-cliente-float-importe-int-habitacion---1)(QString estado, QDate inicio, QDate fin, int noches, int cliente, float importe, int habitacion = -1)|
|Reserva*|[buscarReserva](#reserva-buscarreservaint-numeroconfirmacion)(int numeroConfirmacion)|
|void|[getReservas](#vector-getreservas)()|
|Reserva*|[cambiarEstadoReserva](#reserva-cambiarestadoreservaint-numeroconfirmacion-qstring-estado)(int numeroConfirmacion, QString estado)|
|Reserva*|[cambiarEstadoReserva](#reserva-cambiarestadoreservareserva-reservaacambiar-qstring-estado)(Reserva* reservaACambiar, QString estado)|
|Reserva*|[aniadirGasto](#reserva-aniadirgastoint-numeroconfirmacion-qstring-gasto-float-importe)(int numeroConfirmacion, QString gasto, float importe)|
|void|[modificarReserva](#void-modificarreservareserva-reserva)(Reserva* reserva)|
|void|[eliminarReserva](#void-eliminarreservaint-numeroconfirmacion)(int numeroConfirmacion)|

## Descripción Detallada

### bd: QSqlDatabase

Este atributo continene la interfaz para conectar con la Base de Datos SQLite.
A través de él se realizan todas las consultas a la Base de Datos.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QSqlDatabase|getBD()|

***

### ControladorBD()

Construye un objeto de tipo ControladorBD con una conexión establecida a la base de datos SQLite del hotel y llama al método [abreBD](#bool-abrebd)().

***

### ~ControladorBD()

Destruye el objeto de tipo ControladorBD y cierra la base de datos asociada a él.

***

### bool abreBD()

Verifica que sea posible abrir la base de datos referenciada por [bd](#bd-qsqldatabase) y devuelve `true` en ese caso.

***

### Cliente* crearCliente(QString nombre, QString email, QString telefono, QString nacionalidad)

Inserta un nuevo cliente en la Base de Datos y devuelve la referencia a un objeto de tipo [Cliente](../Cliente) creado con el atributo [identificador](../Cliente/README.md#identificador-int) devuelto por la Base de Datos.

***

### Cliente* buscarCliente(int identificador)

Busca al cliente con el identificador correspondiente en la Base de Datos.

***

### vector<Cliente> getClientes()

Devuelve un vector de objetos de tipo [Cliente](../Cliente) con los datos de todos los clientes en la Base de Datos.

***

### Cliente* aniadirEstancia([Cliente](../Cliente)* cliente)

Modifica al cliente correspondiente en la Base de Datos, aumentando en 1 el valor de su cantidad de estancias. Llama al método [aniadirEstancia](../Cliente/README.md#void-aniadirestancia) del objeto pasado como argumento.

***

### void eliminarCliente(int identificador)

Elimina al cliente con el identificador correspondiente de la Base de Datos.

***

### Habitacion* crearHabitacion(int numero, QString tipo, int tamanio, int camas, float coste)

Inserta una nueva habitación en la Base de Datos.

***

### Habitacion* buscarHabitacion(int numero)

Busca la habitación con el número correspondiente en la Base de Datos.

***

### vector<Habitacion> getHabitaciones()

Devuelve un vector de objetos de tipo [Habitacion](../Habitacion) con los datos de todas las habitaciones en la Base de Datos.

***

### Habitacion* cambiarEstadoHabitacion([Habitacion](../Habitacion)* habitacion)

Modifica los datos de la habitación en la Base de Datos según los de la referencia pasada como argumento.

***

### Habitacion* cambiarDisponibilidadHabitacion(int numero, bool disponible)

Modifica el valor de [disponible](../Habitacion/README.md#disponible-bool) de la habitación en la Base de Datos con número coincidente, según el valor de disponible pasado como atributo.  
No puede establecerse en `true` si el valor de [enArreglos](../Habitacion/README.md#enarreglos-bool) es también `true`.

***

### Habitacion* cambiarEnArreglosHabitacion(int numero, bool enArreglos)

Modifica el valor de [enArreglos](../Habitacion/README.md#enarreglos-bool) de la habitación en la Base de Datos con número coincidente, según el valor de enArreglos pasado como atributo.  
Si se establece en `true`, establece el valor de [disponible](../Habitacion/README.md#disponible-bool) en `false`.

***

### void eliminarHabitacion(int numero)

Elimina la habitación con el identificador correspondiente de la Base de Datos.

***

### Reserva* crearReserva(QString estado, QDate inicio, QDate fin, int noches, int cliente, float importe, int habitacion = -1)

Inserta una nueva reserva en la Base de Datos.  
Llama a los métodos [cambiarEstadoReserva](#reserva-cambiarestadoreservaint-numeroconfirmacion-qstring-estado) y [aniadirGasto](#reserva-aniadirgastoint-numeroconfirmacion-qstring-gasto-float-importe) para establecer datos adicionales necesarios en la Base de Datos.  
Devuelve la referencia a un objeto de tipo [Reserva](../Reserva) creado con el atributo [numeroConfirmacion](../Reserva/README.md#numeroconfirmacion-int) devuelto por la Base de Datos.

***

### Reserva* buscarReserva(int numeroConfirmacion)

Busca la reserva con el número correspondiente en la Base de Datos.

***

### vector<Reserva> getReservas()

Devuelve un vector de objetos de tipo [Reserva](../Reserva) con los datos de todas las reservas en la Base de Datos.

***

### Reserva* cambiarEstadoReserva(int numeroConfirmacion, QString estado)

Cambia el estado de la reserva con el número correspondiente en la Base de Datos.

***

### Reserva* cambiarEstadoReserva([Reserva](../Reserva)* reservaACambiar, QString estado)

Cambia el estado de la reserva correspondiente en la Base de Datos.

***

### Reserva* aniadirGasto(int numeroConfirmacion, QString gasto, float importe)

Cambia el valor de [desgloseGastos](../Reserva/README.md#desglosegastos-vectorpairqstringfloat) e [importe](../Reserva/README.md#importe-float), añadiendo un nuevo gasto, a la reserva con el número correspondiente en la Base de Datos.

***

### void modificarReserva([Reserva](../Reserva)* reserva)

Modifica los datos de la reserva en la Base de Datos según los de la referencia pasada como argumento.

***

### void eliminarReserva(int numeroConfirmacion)

Elimina la reserva con el numero de confirmación correspondiente de la Base de Datos.
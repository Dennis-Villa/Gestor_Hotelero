# Clase Reserva

Esta clase busca gestionar, utilizando Programación Orientada a Objetos, las propiedades y métodos necesarios para establecer la funcionalidad de gestionar una reserva en un servicio hotelero.

## Elementos de la clase

### Atributos de la clase

|||
|---|---|
|int|[numeroConfirmacion](#numeroconfirmacion-int)|
|QString|[estadoReserva](#estadoreserva-qstring)|
|vector<pair<QString,float> >|[desgloseGastos](#desglosegastos-vectorpairqstringfloat)|
|float|[importe](#importe-float)|
|int|[cantidadNoches](#cantidadnoches-int)|
|QDate|[fechaInicio](#fechainicio-qdate)|
|QDate|[fechaFin](#fechafin-qdate)|
|Cliente*|[cliente](#cliente-cliente)|
|Habitacion*|[habitacion](#habitacion-habitacion)|

***

### Métodos Públicos

|Retorno|Método|
|---|---|
||[Reserva](#reservaint-numeroconfirmacion-cliente-cliente-int-cantidadnoches-qstring-estadoreserva--pendiente)(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString estadoReserva = "Pendiente")|
||[Reserva](#reservaint-numeroconfirmacion-cliente-cliente-int-cantidadnoches-habitacion-habitacion-qstring-estadoreserva--pendiente)(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, Habitacion \*habitacion, QString estadoReserva = "Pendiente")|
||[Reserva](#reservaint-numeroconfirmacion-cliente-cliente-qdate-fechainicio-qdate-fechafin-int-cantidadnoches-float-importe-qstring-estadoreserva-habitacion-habitacion--nullptr)(int numeroConfirmacion, Cliente *cliente, QDate fechaInicio, QDate fechaFin, int cantidadNoches, float importe, QString estadoReserva, Habitacion \*habitacion = nullptr)|
||[Reserva](#reservaint-numeroconfirmacion-cliente-cliente-int-cantidadnoches-qdate-fechainicio-qdate-fechafin-qstring-desglosegastos-float-importe-qstring-estadoreserva-habitacion-habitacion--nullptr)(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QDate fechaInicio, QDate fechaFin, QString desgloseGastos, float importe, QString estadoReserva, Habitacion \*habitacion = nullptr)|
||[Reserva](#reservaint-numeroconfirmacion-cliente-cliente-int-cantidadnoches-qstring-fechainicio-qstring-fechafin-qstring-desglosegastos-float-importe-qstring-estadoreserva-habitacion-habitacion--nullptr)(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString fechaInicio, QString fechaFin, QString desgloseGastos, float importe, QString estadoReserva, Habitacion \*habitacion = nullptr)|
|int|[getNumeroConfirmacion](#numeroconfirmacion-int)()|
|void|[setNumeroConfiramcion](#numeroconfirmacion-int)(int numero)|
|QString|[getEstadoReserva](#estadoreserva-qstring)()|
|void|[setEstadoReserva](#estadoreserva-qstring)(QString estado)|
|vector<pair<QString,float>>|[getDesgloseGastos](#desglosegastos-vectorpairqstringfloat)()|
|QString|[getDesgloseGastosString](#desglosegastos-vectorpairqstringfloat)()|
|float|[getImporte](#importe-float)()|
|int|[getCantidadNoches](#cantidadnoches-int)()|
|void|[setCantidadNoches](#cantidadnoches-int)(int noches)|
|QDate|[getFechaInicio](#fechainicio-qdate)()|
|QString|[getFechaInicioString](#fechainicio-qdate)()|
|QDate|[getFechaFin](#fechafin-qdate)()|
|QString|[getFechaFinString](#fechafin-qdate)()|
|[Cliente](../Cliente)*|[getCliente](#cliente-cliente)()|
|void|[setCliente](#cliente-cliente)([Cliente](../Cliente)* cliente)|
|[Habitacion](../Habitacion)*|[getHabitacion](#habitacion-habitacion)()|
|void|[setHabitacion](#habitacion-habitacion)([Habitacion](../Habitacion)* habitacion)|
|int|[getClienteID](#int-getclienteid)()|
|QString|[getClienteNombre](#qstring-getclientenombre)()|
|int|[getNumeroHabitacion](#int-getnumerohabitacion)()|
|int|[getPisoHabitacion](#int-getpisohabitacion)()|
|bool|[tieneHabitacion](#bool-tienehabitacion)()|
|void|[registarEntrada](#void-registarentrada)()|
|void|[registarSalida](#void-registarsalida)()|
|void|[aniadirGasto](#void-aniadirgastoqstring-nombreservicio-float-coste)(QString nombreServicio, float coste)|
|void|[modificarGastoHabitacion](#void-modificargastohabitacionfloat-gasto)(float gasto)|
|QString|[convertirGastosATexto](#qstring-convertirgastosatexto)()|

## Descripción Detallada

### numeroConfirmacion: int

Esta propiedad almacena el número asignado a la reserva por la base de datos y actúa como su identificador único.  
Este valor es necesario al construir una instancia de la clase.  
No puede ser negativo.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|int|getNumeroConfirmacion()|
|Escritura|void|setNumeroConfiramcion(int numero)|

***

### estadoReserva: QString

Esta propiedad almacena el estado de la reserva, el cual puede seleccionarse solamente de los valores: *Pendiente*, *Confirmado*, *En Estadía*, *Estancia Finalizada* y *Vencida*.  
Este valor es necesario al construir una instancia de la clase.  
Una reserva en estado *Confirmado* debe tener una fecha de inicio establecida. Una reserva en estado *En Estadía* llama al método [registarEntrada](#void-registarentrada).
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QString|getEstadoReserva()|
|Escritura|void|setEstadoReserva(QString estado)|

***

### desgloseGastos: vector<pair<QString,float>>

Esta propiedad almacena los gastos de la reserva utilizando pares formados por una descripción del gasto y su importe correspondiente.  
Este valor puede ser indicado al crear una instancia, de lo contrario se establecerá como un vector vacío.
El importe total de los gastos debe coincidir con el atributo [importe](#importe-float) de la reserva.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|vector<pair<QString,float> >|getDesgloseGastos()|
|Lectura|QString|getDesgloseGastosString()|

***

### importe: float

Esta propiedad almacena el importe total de los gastos de la reserva.  
Este valor puede ser indicado al crear una instancia, de lo contrario se establecerá con valor 0.  
El valor debe coincidir con el total de gastos del atributo [desgloseGastos](#desglosegastos-vectorpairqstringfloat) de la reserva.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|float|getImporte()|

***

### cantidadNoches: int

Esta propiedad almacena la cantidad de noches de estancia de la reserva.  
Este valor es necesario al construir una instancia de la clase.  
Debe ser al menos 1 noche.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|int|getCantidadNoches()|
|Escritura|void|setCantidadNoches(int noches)|

***

### fechaInicio: QDate

Esta propiedad almacena la fecha de inicio de la estancia.  
Para reservas con [estadoReserva](#estadoreserva-qstring) en *Pendiente* se establecerá en el 1ro de Enero de 1970. Cualquier otro estado debe incluir la fecha de inicio al construir la instancia.  
Para reservas con [estadoReserva](#estadoreserva-qstring) en *Confirmado* fechaInicio debe ser mayor o igual a la fecha actual.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QDate|getFechaInicio()|
|Lectura|QString|getFechaInicioString()|

***

### fechaFin: QDate

Esta propiedad almacena la fecha de fin de la estancia.  
Para reservas con [estadoReserva](#estadoreserva-qstring) en *Pendiente* se establecerá en el 1ro de Enero de 1970. Para cualquier otro estado se calculará sumando [cantidadNoches](#cantidadnoches-int) a [fechaInicio](#fechainicio-qdate).  
Para reservas con [estadoReserva](#estadoreserva-qstring) en *Confirmado* o *En Estadía* fechaFin debe ser mayor o igual a la fecha actual.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QDate|getFechaFin()|
|Lectura|QString|getFechaFinString()|

***

### cliente: Cliente*

Esta propiedad almacena un puntero con la dirección de memoria del objeto [Cliente](../Cliente) que almacena los datos del cliente que hizo la reserva.  
Este valor es necesario al construir una instancia de la clase.  
No puede ser un puntero nulo.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|[Cliente](../Cliente)*|getCliente()|
|Escritura|void|setCliente([Cliente](../Cliente)* cliente)|

***

### habitacion: Habitacion*

Esta propiedad almacena un puntero con la dirección de memoria del objeto [Habitación](../Habitacion) que almacena los datos de la habitación que se registra en la reserva.  
Para reservas con [estadoReserva](#estadoreserva-qstring) en *Pendiente* no es necesario especificar habitación, en cuyo caso se establecerá como puntero nulo.  
Para cualquier otro estado se debe especificar.  
Para reservas con [estadoReserva](#estadoreserva-qstring) *En Estadía* se establecerá la propiedad [disponible](../Habitacion/README.md#disponible-bool) de la habitación en `false`.  
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|[Habitacion](../Habitacion)*|getHabitacion()|
|Escritura|void|setHabitacion([Habitacion](../Habitacion)* habitacion)|

***

### Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString estadoReserva = "Pendiente")

Construye un objeto de tipo cliente con los parámetros establecidos, estableciendo el valor de [cantidadEstancias](#cantidadestancias-int) por defecto en 0.

***

### Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, Habitacion \*habitacion, QString estadoReserva = "Pendiente")

Sobrecarga el constructor anterior.  
Establece el valor de [cantidadEstancias](#cantidadestancias-int).

***

### Reserva(int numeroConfirmacion, Cliente *cliente, QDate fechaInicio, QDate fechaFin, int cantidadNoches, float importe, QString estadoReserva, Habitacion \*habitacion = nullptr)

Sobrecarga el constructor anterior.  
Establece el valor de [cantidadEstancias](#cantidadestancias-int).

***

### Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QDate fechaInicio, QDate fechaFin, QString desgloseGastos, float importe, QString estadoReserva, Habitacion \*habitacion = nullptr)

Sobrecarga el constructor anterior.  
Establece el valor de [cantidadEstancias](#cantidadestancias-int).

***

### Reserva(int numeroConfirmacion, Cliente *cliente, int cantidadNoches, QString fechaInicio, QString fechaFin, QString desgloseGastos, float importe, QString estadoReserva, Habitacion \*habitacion = nullptr)

Sobrecarga el constructor anterior.  
Establece el valor de [cantidadEstancias](#cantidadestancias-int).

***

### int getClienteID()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### QString getClienteNombre()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### int getNumeroHabitacion()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### int getPisoHabitacion()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### bool tieneHabitacion()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### void registarEntrada()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### void registarSalida()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### void aniadirGasto(QString nombreServicio, float coste)

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### void modificarGastoHabitacion(float gasto)

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

***

### QString convertirGastosATexto()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.

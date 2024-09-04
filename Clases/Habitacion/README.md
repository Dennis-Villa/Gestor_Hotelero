# Clase Habitación

Esta clase busca gestionar, utilizando Programación Orientada a Objetos, las propiedades y métodos necesarios para establecer la funcionalidad de gestionar una habitación en un servicio hotelero.

### Atributos de la clase

|||
|---|---|
|int|[numeroHabitacion](#numerohabitacion-int)|
|QString|[tipoHabitacion](#tipohabitacion-qstring)|
|int|[piso](#piso-int)|
|int|[numero](#numero-int)|
|int|[tamanioM2](#tamaniom2-int)|
|int|[numeroCamas](#numerocamas-int)|
|float|[costePorNoche](#costepornoche-float)|
|bool|[disponible](#disponible-bool)|
|bool|[enArreglos](#enarreglos-bool)|

### Métodos Públicos

|Retorno|Método|
|---|---|
||[Habitacion](#habitacionint-numerohabitacion-qstring-tipohabitacion-int-tamaniom2-int-numerocamas-float-costepornoche)(int numeroHabitacion, QString tipoHabitacion, int tamanioM2, int numeroCamas, float costePorNoche)|
||[Habitacion](#habitacionint-numerohabitacion-qstring-tipohabitacion-int-tamaniom2-int-numerocamas-float-costepornoche-bool-disponible-bool-enarreglos)(int numeroHabitacion, QString tipoHabitacion, int tamanioM2, int numeroCamas, float costePorNoche, bool disponible, bool enArreglos)|
|int|[getNumeroHabitacion](#numerohabitacion-int)()|
|void|[setNumeroHabitacion](#numerohabitacion-int)(int numero)|
|QString|[getTipoHabitacion](#tipohabitacion-qstring)()|
|void|[setTipoHabitacion](#tipohabitacion-qstring)(QString tipo)|
|int|[getPiso](#piso-int)()|
|int|[getNumero](#numero-int)()|
|int|[getTamanioM2](#tamaniom2-int)()|
|void|[setTamanioM2](#tamaniom2-int)(int tamanio)|
|int|[getNumeroCamas](#numerocamas-int)()|
|void|[setNumeroCamas](#numerocamas-int)(int camas)|
|float|[getCostePorNoche](#costepornoche-float)()|
|void|[setCostePorNoche](#costepornoche-float)(float coste)|
|bool|[getDisponible](#disponible-bool)()|
|void|[setDisponible](#disponible-bool)(bool disponible)|
|bool|[getEnArreglos](#enarreglos-bool)()|
|void|[setEnArreglos](#enarreglos-bool)(bool enArreglos)|

## Descripción Detallada

### numeroHabitacion: int

Esta propiedad almacena el número asignado a la habitación y actua como su identificador único.  
Este valor es necesario al construir una instancia de la clase.  
No puede ser menor a 100.
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getNumeroHabitacion()|int|
|Escritura|setNumeroHabitacion(int numero)|void|



### tipoHabitacion: QString

Esta propiedad almacena el tipo de habitación, el cual puede seleccionarse solamente de los valores: *Estandar*, *Premium* y *Suit*.  
Este valor es necesario al construir una instancia de la clase.  
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getTipoHabitacion()|QString|
|Escritura|setTipoHabitacion(QString tipo)|void|



### piso: int

Esta propiedad almacena el piso de habitación en el edificio.  
El valor es calculado a partir del número de la habitación, correspondiendo a los primeros dígitos de este.
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getPiso()|int|



### numero: int

Esta propiedad almacena el número de habitación en su piso.  
El valor es calculado a partir del número de la habitación, correspondiendo a los 2 últimos dígitos de este.
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getNumero()|int|



### tamanioM2: int

Esta propiedad almacena el tamaño de la habitación en $m^2$.  
Este valor es necesario al construir una instancia de la clase.  
Debe ser mayor a 0.
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getTamanioM2()|int|
|Escritura|setTamanioM2(int tamanio)|void|



### numeroCamas: int

Esta propiedad almacena la cantidad de camas que tiene la habitación.  
Este valor es necesario al construir una instancia de la clase.  
Debe ser mayor a 0.

**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getNumeroCamas()|int|
|Escritura|setNumeroCamas(int camas)|void|



### costePorNoche: float

Esta propiedad almacena el coste de renta diario de la habitación.  
Este valor es necesario al construir una instancia de la clase y es formateado a dos lugares decimales.  
No puede ser negativo.
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getCostePorNoche()|float|
|Escritura|setCostePorNoche(float coste)|void|



### disponible: bool

Esta propiedad indica si la habitación se encuentra disponible para su uso.  
Este valor puede ser indicado al crear una instancia, de lo contrario se establecerá en `true`.  
Esta propiedad no puede coincidir como `true` con [enArreglos](#enarreglos-bool)
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getDisponible()|bool|
|Escritura|setDisponible(bool disponible)|void|



### enArreglos: bool

Esta propiedad indica si la habitación se encuentra en arreglos actualmente.  
Este valor puede ser indicado al crear una instancia, de lo contrario se establecerá en `false`.  
Al establecerce como `true` se establece automáticamente [disponible](#disponible-bool) en `false`.
  
**Funciones de acceso:**
  
|Tipo|Función|Retorno|
|---|---|---|
|Lectura|getEnArreglos()|bool|
|Escritura|setEnArreglos(bool enArreglos)|void|



### Habitacion(int numeroHabitacion, QString tipoHabitacion, int tamanioM2, int numeroCamas, float costePorNoche)

Construye un objeto de tipo habitacion con los parámetros establecidos, estableciendo el valor de [disponible](#disponible-bool) por defecto en `true` y de [enArreglos](#enarreglos-bool) en `false`.
  
### Habitacion(int numeroHabitacion, QString tipoHabitacion, int tamanioM2, int numeroCamas, float costePorNoche, bool disponible, bool enArreglos)

Sobrecarga el constructor anterior.  
Establece los valores de [disponible](#disponible-bool) y [enArreglos](#enarreglos-bool).
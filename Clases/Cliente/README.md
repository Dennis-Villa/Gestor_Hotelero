# Clase Habitación

Esta clase busca gestionar, utilizando Programación Orientada a Objetos, las propiedades y métodos necesarios para establecer la funcionalidad de gestionar un cliente en un servicio hotelero.

## Elementos de la clase

### Atributos de la clase

|||
|---|---|
|int|[identificador](#identificador-int)|
|QString|[nombre](#nombre-qstring)|
|QString|[email](#email-qstring)|
|QString|[nacionalidad](#nacionalidad-qstring)|
|int|[cantidadEstancias](#cantidadestancias-int)|
|QString|[telefono](#telefono-qstring)|

***

### Métodos Públicos

|Retorno|Método|
|---|---|
||[Cliente](#clientelong-long-identificador-qstring-nombre-qstring-email-qstring-nacionalidad-qstring-telefono--null)(long long identificador, QString nombre, QString email, QString nacionalidad, QString telefono = NULL)|
||[Cliente](#clientelong-long-identificador-qstring-nombre-qstring-email-qstring-nacionalidad-int-cantidadestancias-qstring-telefono--null)(long long identificador, QString nombre, QString email, QString nacionalidad, int cantidadEstancias, QString telefono = NULL)|
|int|[getIdentificador](#identificador-int)()|
|void|[setIdentificador](#identificador-int)(int identificador)|
|QString|[getNombre](#nombre-qstring)()|
|void|[setNombre](#nombre-qstring)(QString nombre)|
|QString|[getEmail](#email-qstring)()|
|void|[setEmail](#email-qstring)(QString email)|
|QString|[getNacionalidad](#nacionalidad-qstring)()|
|void|[setNacionalidad](#nacionalidad-qstring)(QString nacionalidad)|
|int|[getCanidadEstancias](#cantidadestancias-int)()|
|void|[setCantidadEstancias](#cantidadestancias-int)(int estancias)|
|QString|[getTelefono](#telefono-qstring)()|
|void|[setTelefono](#telefono-qstring)(QString telefono)|
|void|[aniadirEstancia](#void-aniadirestancia)()|

## Descripción Detallada

### identificador: int

Esta propiedad almacena el número asignado al cliente por la base de datos y actúa como su identificador único.  
Este valor es necesario al construir una instancia de la clase.  
No puede ser negativo.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|int|getIdentificador()|
|Escritura|void|setIdentificador(int identificador)|

***

### nombre: QString

Esta propiedad almacena el nombre del cliente.  
Este valor es necesario al construir una instancia de la clase.  
No puede estar vacío, solamente puede estar formado por letras y debe tener al menos un apellido.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QString|getNombre()|
|Escritura|void|setNombre(QString nombre)|

***

### email: QString

Esta propiedad almacena el email del cliente.  
Este valor es necesario al construir una instancia de la clase.  
No puede estar vacío y debe tener estructura de email.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QString|getEmail()|
|Escritura|void|setEmail(QString email)|

***

### nacionalidad: QString

Esta propiedad almacena el país de nacionalidad del cliente.  
Este valor es necesario al construir una instancia de la clase.  
No puede estar vacío.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QString|getNacionalidad()|
|Escritura|void|setNacionalidad(QString nacionalidad)|

***

### cantidadEstancias: int

Esta propiedad almacena la cantidad de estancias que ha tenido el cliente en el hotel.  
Este valor puede ser indicado al crear una instancia, de lo contrario se establecerá en 0.  
No puede ser negativo.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|int|getCanidadEstancias()|
|Escritura|void|setCantidadEstancias(int estancias)|

***

### telefono: QString

Esta propiedad almacena el teléfono del cliente.  
Este valor puede ser indicado al crear una instancia, de lo contrario se establecerá en `NULL`.  
Debe tener 9 dígitos.
  
**Funciones de acceso:**
  
|Tipo|Retorno|Función|
|---|---|---|
|Lectura|QString|getTelefono()|
|Escritura|void|setTelefono(QString telefono)|

***

### Cliente(long long identificador, QString nombre, QString email, QString nacionalidad, QString telefono = NULL)

Construye un objeto de tipo Cliente con los parámetros establecidos, estableciendo el valor de [cantidadEstancias](#cantidadestancias-int) por defecto en 0.

***

### Cliente(long long identificador, QString nombre, QString email, QString nacionalidad, int cantidadEstancias, QString telefono = NULL)

Sobrecarga el constructor anterior.  
Establece el valor de [cantidadEstancias](#cantidadestancias-int).

***

### void aniadirEstancia()

Aumenta en 1 el valor de [cantidadEstancias](#cantidadestancias-int) para el cliente.
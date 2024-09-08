# Ventana Añadir Cliente

Esta ventana y su clase correspondiente, manejan la lógica para añadir un cliente a la base de datos del hotel con los datos introducidos en la interfaz. Utiliza como base una ventana QDialog de Qt.

![Ventana Añadir Cliente](../../Imagenes/Captura_Ventana_Nuevo_Cliente.PNG)

## Elementos

### Atributos

|||
|---|---|
|Ui::AniadirCliente*|[ui](#ui-uianiadircliente)|
|vector\<[Cliente](../../Clases/Cliente)>*|[clientes](#clientes-vectorcliente)|
|[ControladorBD](../../Clases/ControladorBD)*|[controladorBD](#controladorbd-controladorbd)|
|bool|[ventanaAbierta](#ventanaabierta-bool)|

***

### Métodos Públicos

|Retorno|Método|
|---|---|
||[AniadirCliente](#aniadirclientevectorcliente-clientes-qwidget-parent--nullptr-controladorbd-controladorbd)(vector\<[Cliente](../../Clases/Cliente)>\* clientes, QWidget\* parent = nullptr, [ControladorBD](../../Clases/ControladorBD)* controladorBD)|
||~[AniadirCliente](#aniadircliente)()|
|void|[abrirVentana](#void-abrirventana)()|
|void|[limpiarVentana](#void-limpiarventana)()|

### Slots Privados

|Retorno|Slot|
|---|---|
|void|[aniadirCliente](#aniadidobool-actualizar--false)()|
|void|[cerrar](#void-cerrar)()|

### Señales

|Retorno|Señal|
|---|---|
|void|[cerrarVentana](#cerrarventanabool-cerrar--false)(bool cerrar = false)|
|void|[aniadido](#aniadidobool-actualizar--false)(bool actualizar = false)|

## Descripción Detallada

### ui: Ui::AniadirCliente*

Este atributo almacena una referencia a la interfaz del usuario para poder acceder a los elementos visuales incuidos en ella.

***

### clientes: vector\<[Cliente](../../Clases/Cliente)>*

Este atributo almacena una referencia a los clientes almacenadas en la memoria de la aplicación.  
Este valor debe ser indicado al crear una instancia.  

***

### controladorBD: [ControladorBD](../../Clases/ControladorBD)*

Este atributo almacena una referencia al objeto de tipo [ControladorBD](../../Clases/ControladorBD) que maneja las consultas a la base de datos del hotel.  
Este valor se inicializa como `nullptr` al crear una instancia.  

***

### ventanaAbierta: bool

Este atributo indica si esta ventana se encuentra visible para el usuario.  
Este valor se inicializa como `false` al crear una instancia.  

***

### AniadirCliente(vector\<[Cliente](../../Clases/Cliente)>\* clientes, QWidget\* parent = nullptr, [ControladorBD](../../Clases/ControladorBD)* controladorBD)

Construye un objeto de tipo AniadirCliente con los parámetros establecidos y lo conecta con su interfaz de usuario.  
Conecta la señal de click en el botón Aniadir con el SLOT [aniadirCliente](#void-aniadircliente)().  
Conecta la señal de click en el botón Cerrar con el SLOT [cerrar](#void-cerrar)().  
Conecta la señal de cerrar de la ventana con el SLOT [cerrar](#void-cerrar)().  

***

### ~AniadirCliente()

Elimina el atributo [ui](#ui-uianiadircliente).  

***

### void abrirVentana()

Establece el valor del atributo [ventanaAbierta](#ventanaabierta-bool) en `true`.

***

### void limpiarVentana()

Borra los datos guardados en los elementos de la interfaz de usuario.  

***

### void aniadirCliente()

Lee los datos en la interfaz de usuario y llama con ellos al método [crearCliente](../../Clases/ControladorBD/README.md#cliente-crearclienteqstring-nombre-qstring-email-qstring-telefono-qstring-nacionalidad) de la clase [ControladorBD](../../Clases/ControladorBD).  
Toma el objeto de tipo [Cliente](../../Clases/Cliente) devuelto por el método y lo añade al vector de clientes referenciado por el atributo [clientes](#clientes-vectorcliente).
Emite la señal [aniadido](#aniadidobool-actualizar--false)(`true`).

***

### void cerrar()

Llama al método [limpiarVentana](#void-limpiarventana)(), establece el atributo [ventanaAbierta](#ventanaabierta-bool) en `false` y emite la señal [cerrarVentana](#cerrarventanabool-cerrar--false)(`true`).

***

### cerrarVentana(bool cerrar = false)

Se emite cuando se deba cerrar la ventana.

***

### aniadido(bool actualizar = false)

Se emite cuando se añade un objeto de tipo [Cliente](../../Clases/Cliente) al vector referenciado por el atributo [clientes](#clientes-vectorcliente).

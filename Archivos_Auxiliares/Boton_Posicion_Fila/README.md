# Botón de Posición en Fila

Esta clase crea un componente personalizado de Qt que hereda de QPushButton y permite almacenar el identificador de un objeto y enviarlo en una señal de click.

## Elementos

### Atributos

|||
|---|---|
|int|[id](#int-id)|

***

### Métodos Públicos

|Retorno|Método|
|---|---|
||[BotonPosicionFila](#botonposicionfilaqwidget-parent--nullptr)(QWidget* parent = nullptr)|
||[BotonPosicionFila](#botonposicionfilaqstring-texto-qwidget-parent--nullptr)(QString texto, QWidget* parent = nullptr)|
||[BotonPosicionFila](#botonposicionfilaint-id-qwidget-parent--nullptr)(int id, QWidget* parent = nullptr)|
||[BotonPosicionFila](#botonposicionfilaqstring-texto-int-id-qwidget-parent--nullptr)(QString texto, int id, QWidget* parent = nullptr)|
|void|[setID](#void-setidint-id---1)(int ID = -1))|

***

### Slots Privados

|Retorno|Slot|
|---|---|
|void|[handleClick](#void-handleclick)()|

### Señales

|Retorno|Señal|
|---|---|
|void|[clicked](#void-clickedint)(int)|

## Descripción Detallada

### int: id

Este atributo almacena un identificador numérico.  
Su valor puede ser indicado al crear una instancia, de lo contrario se establecerá en -1.  

***

### BotonPosicionFila(QWidget* parent = nullptr)

Construye un objeto de tipo BotonPosicionFila que herede de QPushButton y establece su atributo [id](#int-id) en -1.  

***

### BotonPosicionFila(QString texto, QWidget *parent = nullptr)

Sobrecarga el constructor.  
Establece el texto del botón.

***

### BotonPosicionFila(int id, QWidget *parent = nullptr)

Sobrecarga el constructor.  
Llama al método [setID](#void-setidint-id---1)(int) con el parámetro id.

***

### BotonPosicionFila(QString texto, int id, QWidget *parent = nullptr)

Sobrecarga el constructor.  
Establece el texto del botón y llama al método [setID](#void-setidint-id---1)(int) con el parámetro id.

***

### void setID(int ID = -1)

Establece el valor del atributo [id](#int-id) con ID y conecta la señal de click con el slot [handleClick](#void-handleclick)()

***

### void handleClick()

Emite la señal [clicked](#void-clickedint)(int) con el valor del atributo [id](#int-id).

***

### void clicked(int)

Se emite cuando se hace click sobre el botón.

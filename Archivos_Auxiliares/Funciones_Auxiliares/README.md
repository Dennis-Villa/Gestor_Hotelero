# Funciones Auxiliares

Esta librería incluye algunas funciones útiles para manejar la lógica de la aplicación

## Funciones

|Retorno|Función|
|---|---|
|vector \<QString>|[stringSplit](#vectorqstring-stringsplitqstring-cadena-char-separador)(QString cadena, char separador)|
|bool|[soloLetras](#bool-sololetrasqstring-cadena)(QString cadena)|
|bool|[estadoReservaValido](#bool-estadoreservavalidoqstring-estadoreserva)(QString estadoReserva)|
|float|[importeMaximoDecimales](#float-importemaximodecimalesfloat-importe)(float importe)|
|bool|[tipoHabitacionValido](#bool-tipohabitacionvalidoqstring-tipohabitacion)(QString tipoHabitacion)|
|int|[contarDigitos](#int-contardigitosqstring-cadenaalfanumerica)(QString cadenaAlfanumerica)|
|vector<pair <QString, float>> |[stringGastosToVector](#vectorpair-qstring-float-stringgastostovectorqstring-desglosegastos)(QString desgloseGastos)|

## Descripción Detallada

### vector\<QString> stringSplit(QString cadena, char separador)

Toma una cadena de tipo QString y devuelve todas las subcadenas formadas al separar la cadena original según el parámetro separador.

***

### bool soloLetras(QString cadena)

Determina si una cadena está formada solamente por letras.

***

### bool estadoReservaValido(QString estadoReserva)

Devuelve `true` si la cadena estadoReserva tiene uno de los siguientes valores: "Pendiente", "Confirmado", "En Estadía", "Estancia Finalizada" o "Vencida".

***

### float importeMaximoDecimales(float importe)

Devuelve el valor de coma flotante que toma pero con un máximo de dos puntos decimales.

***

### bool tipoHabitacionValido(QString tipoHabitacion)

Devuelve `true` si la cadena tipoHabitacion tiene uno de los siguientes valores: "Estandar", "Premium" o "Suit".

***

### int contarDigitos(QString cadenaAlfanumerica)

Devuelve la cantidad de caracteres numéricos en cadenaAlfanumerica.

***

### vector<pair <QString, float>> stringGastosToVector(QString desgloseGastos)

Toma una cadena de tipo QString con formato "{Descripción_1,importe_1},{Descripción_2,importe_2},..." y convierte los datos en un vector de pares QString y float.

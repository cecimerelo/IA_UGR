# EL LENGUAJE IML

## Estructura básica de IML

~~~"xml"
<?xml version="1.0" encoding="UTF-8"?>
<aiml version="2.0">
    <category>
        <pattern>Esta es la pregunta</pattern>
        <template>Esta es la respuesta</template>
    </category>
</aiml>
~~~

## El intérprete "program-ab"

* **aiml** : archivos con extensión aiml
* **aimlif** : nueva información aprendida por el bot. La extensión de los ficheros es .csv
* **config** : información del bot
* **data** : información temoral del intérprete. Será ignorada
* **sets** : set que va a usar el intérprete
* **maps** : map que usará el intérprete

## Wildcards - "comodines"

Permiten capturar varias entradas para una misma regla.

* Captura una o más palabras de la entrada:

~~~"xml"
<pattern>Hola *</pattern>
~~~

* Captura cero o más palabras de la entrada:

~~~"xml"
<pattern>Hola ^</pattern>
~~~

El patrón que contiene "^" tiene mayor prioridad y, por tanto será la regla que se dispare.

Hay otros dos comodines:

* como el "*":

~~~"xml"
<pattern>Hola _</pattern>
~~~

* como el "^":

~~~"xml"
<pattern>Hola #</pattern>
~~~

Así el orden de prioridad de mayor a menor sería:
 **Hola # > Hola _ > Hola Amigo > Hola ^ > Hola \***

A veces se desea definir un patrón que tenga mayor prioridad que "#" o "_". En esos casos usamos el símbolo "$", que indica que ese patrón tiene la mayor prioridad si la adaptación contiene esa palabra.

~~~"xml"
<pattern> $Quien * Luis </pattern>
<pattern> _Luis </pattern>
~~~

En este caso, si en la entrada aparece Quien, el primer patrón tiene prioridad sobre el segundo.

Los parones pueden ser capturados:

~~~"xml"
<category>
    <pattern> Mi nombre es *</patter>
    <template>Hola </star></template>
</category>
~~~

Cuando hay más de un comodín:

~~~"xml"
<category>
    <pattern> Estudio * en *</patter>
    <template> En <star index="2">, yo también estudio <start/> </template>
</category>
~~~

#### Ejemplo 1

~~~"xml"
<?xml version="1.0" encoding="UTF-8"?>
<aiml version="2.0">

    <category>
		<pattern>Hola *</pattern>
		<template>
			Hola, que tal?
		</template>
	</category>

    <category>
		<pattern>Hola ^</pattern>
		<template>
			Hola de nuevo, que tal?
		</template>
	</category>


    <category>
		<pattern>^ que tal tu</pattern>
		<template>
			Genial!!!
		</template>
	</category>

    <category>
		<pattern> Me llamo * </pattern>
		<template>
			Que casualidad, yo tambien me llamo <star/>
		</template>
	</category>

    <category>
		<pattern> Estudio * en *</pattern>
		<template>
			Yo también estudio <star/> en <star index="2"/>
		</template>
	</category>

</aiml>
~~~

## Variables

En AIML hay 3 tipos de variables:

### Propiedades del bot 

Información que quiere proporcionar el bot sobre si mismo, sólo pueden ser asignadas por el bot master. Vienen definidas en el fichero "properties.txt" en la carpeta *config* de *mybots*. Se pueden añadir nuevas variables siguiendo el formato: \<nombre variable\> : \<valor\>

Tenemos que añadir la variable *age* a *properties*

Uso: 
~~~"xml"
<category>
    <pattern>Cual es tu edad</pattern>
    <template> Tengo <bot name="age"/> anios</template>
</category>
~~~

### Predicados o variables locales
Se denominan *predicados*. Son variables globales, es decir, su valor puede ser consultado o modificado fuera de una regla.


### Variables Locales
Su ámbito es local a una regla y su valor no puede ser consultado fuera de dicha regla.
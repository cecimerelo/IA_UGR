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
    <template>Hola <star/></template>
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

### Predicados o variables globales
Se denominan *predicados*. Son variables globales, es decir, su valor puede ser consultado o modificado fuera de una regla. 

#### Sintaxis

~~~"xml"
<set name="x">value</set>
~~~

#### Acceso

~~~"xml"
<get name="x"/>
~~~

#### Ejemplo de uso

donde x representa el nombre de la variable

~~~"xml"
<category>
	<pattern>^ me llamo *</pattern>
	<template>
		<set name="nombre"><star index="2"/></set>
		<get name="nombre"/> es un bonito nombre
	</template>
</category>
~~~

==> Una variable que se invoca sin haberle asignado un valor previamente devuelve siempre como valor "unknown".

### Variables Locales

Su ámbito es local a una regla y su valor no puede ser consultado fuera de dicha regla. Tienen como ámbito el template de la regla.

#### Sintaxis

~~~"xml"
<set var="x">value</set>
~~~

#### Acceso

~~~"xml"
<get var="x"/>
~~~

### El tag <think>

Tanto el acceso como la asignación de una variable provoca "eco" por pantalla. Para evitarlo las asignaciones y acceso se encierran en un par.

~~~"xml"
<think></think>
~~~

#### Ejemplo de uso

~~~"xml"
<category>
		<pattern>Mi color favorito es el *</pattern>
		<template>
			<think><set var="color"><star/></set></think>
			El color <get var="color"/> no me gusta nada
		</template>
	</category>
~~~

## Reducción simbólica \<srai\>

Permite:

* Simplificar las entradas usando pocas palabras.
* Enlazar distintas entradas sinónimas con un mismo template.
* Corregir errores ortográficos por parte del usuario.
* Reemplazar expresiones coloquiales por expresiones formales.
* Eliminar palabras innecesarias en las entradas.

#### Ejemplo de uso

~~~"xml"
<!-- USO DE SRAI -->
	<category>
		<pattern> Cual es mi nombre </pattern>
		<template>
			Tu nombre es <get name="nombre"/>
		</template>
	</category>

	<category>
		<pattern>* mi nombre </pattern>
		<template><srai>
			CUAL ES MI NOMBRE
		</srai></template>
	</category>

	<category>
		<pattern> ^ como me llamo </pattern>
		<template><srai>
			CUAL ES MI NOMBRE
		</srai></template>
	</category>
~~~

## Sets y maps

### SET

Es una lista de cadenas que se expresa sobre un fichero. Este fichero debe estar ubicado en la carpeta "sets". Tiene mayor prioridad que "*" y "^", pero menos que "_" y "#".

#### Ejemplo de uso

~~~"xml"
<!-- PRUEBA DEL SET-->
	<category>
		<pattern>Es el <set>color</set> un color</pattern>
		<template>
			Si, el <star/> es un color 
		</template>
	</category>

	<category>
		<pattern> Es el * un color</pattern>
		<template>
			No, el <star/> no es un color
		</template>
	</category>
~~~

### MAPS

Representa el tipo de dato diccionario. En cada línea del fichero se codifica una entrada con el siguiente formato: **cadena1:cadena2**

Para que no ocurra que no encuentre la respuesta se suele definir un set con las claves del map.

#### Ejemplo de uso

~~~"xml"
<!-- PRUEBA DEL MAP -->
	<category>
		<pattern> Cual es la capital de <set>pais</set></pattern>
		<template>
			La capital de <star/> es <map name="capital"><star/></map> 
		</template>
	</category>

	<category>
		<pattern> Cual es la capital de *</pattern>
		<template>
			No se cual es la capital de <star/>
		</template>
	</category>
~~~

AIML tiene definido los siguientes sets y maps:

~~~"xml"
<!-- Numeros naturales -->
<set>number</set>

<!-- Dado un número n devuelve n+1 -->
<map name=“successor”>

<!-- Dado un número n devuelve n-1 -->
<map name=“predecessor”>

<!-- Devuelve el plural de una palabra en singular, solo en inglés -->
<map name=“plural”>

<!-- Devuelve el singular de una palabra en singular, solo en inglés -->
<map name=“singular”>
~~~

## Contexto

Tiene que ver con recordar lo que se ha dicho previamente. En AIML hay tres elementos para recordar el contexto:

* Los predicados o variables globales

### El tag \<that\>
El bot recuerda la última respuesta. En base a esa respuesta puede alterar la respuesta a la siguiente pregunta.

#### Ejemplo de uso

~~~"xml"
	<!-- EL TAG THAT -->
	<category>
		<pattern>^ cafe ^</pattern>
		<template>
			Te gusta el cafe
		</template>
	</category>
	
	<category>
		<pattern>Si</pattern>
		<that> TE GUSTA EL CAFE </that>
		<template>
			Lo prefieres solo o con leche
		</template>
	</category>
~~~

### Un set predefinido en el lenguaje llamado "topic"

Permite agrupar las reglas de manera que estas sólo se activen cuando la conversación se centra en un tema en concreto. Lo primero es definir un bloque de reglas sobre un tema

#### Ejemplo de uso 

~~~"xml"
	<topic name=“cafe”>
		<category> ..... </category>
		..........................
		<category> ..... </category>
	</topic>
~~~

Para fijar un tema, en el "template" de alguna regla se usa:

~~~"xml"
<template> te gusta el <set name=“topic”> cafe </set></template>
~~~

## Random, estructura condicional y ciclos

### Random

Elige entre uno de los pares \<li\> para ofrecerlo como salida.

#### Ejemplo de uso

~~~"xml"
    <category>
		<pattern>Hola ^ </pattern>
		<template>
			<random>
				<li>Hola, que tal?</li>
				<li>Buenas, que tal?</li>
			</random>
		</template>
	</category>
~~~

### Condicionales

#### Ejemplo de uso

~~~"xml"
<category>
		<pattern> Cual es mi nombre </pattern>
		<template>
			<condition name="nombre">
				<li value="unknown"> Aun no me has dicho tu nombre </li>
				<li> Tu nombre es <get name="nombre"/></li>
			</condition>
		</template>
	</category>
~~~

### Ciclos

Son ciclos del tipo: mientras condición hacer bloque de operaciones, y eso implica el uso implícito de la operación de condición.

#### Ejemplo de uso

~~~"xml"
<!-- EJEMPLO DE CICLOS -->
	<category>
		<pattern>Cuenta hasta <set>number</set></pattern>
		<template>
			<think>
				<set var="contador">1</set>
				<set var="salida">1</set>
			</think>
			<condition var="contador">
			<li><value><star/></value><get var="salida"/></li>
			<li>
				<think>
				<set var="contador">
					<map name="successor"><get var="contador"/></map>
				</set>
				<set var="salida"><get var="salida"/> <get var="contador"/></set>
				</think>
				<loop/>
			</li>
			</condition>
		</template>
	</category>
~~~

## Aprender

Se usan los tags \<learn\> y \<learnf\>. La única diferencia entre ambos es si lo que aprende se usa sólo en la conversación actual, en ese caso, se usa learn, o si lo aprendido se desea que se mantenga como parte de la base de las reglas, en cuyo caso hay que usar learnf.

### Ejemplo de uso 

~~~"xml"
	<!-- USO DE LEARN -->
	<category>
		<pattern> La capital de * es * </pattern>
		<template>
			<think>
			<set var="cap"><srai> CUAL ES LA CAPITAL DE <star/></srai></set>
			</think>
			<condition var="cap">
				<li value="NO LO SE">
				<learn>
					<category>
					<pattern> CUAL ES LA CAPITAL DE <eval><star/></eval></pattern>
					<template>
						La capital de <eval><star/></eval> es <eval><star index="2"/></eval>
					</template>
					</category>
				</learn>
				Recordare que la capital de <star/> es <star index="2"/>.
				</li>
				<li> Ya lo sabía </li>
			</condition>
		</template>
	</category>

	<category>
		<pattern> Cual es la capital de <set>pais</set></pattern>
		<template>
			La capital de <star/> es <map name="capital"><star/></map> 
		</template>
	</category>

	<category>
		<pattern> Cual es la capital de *</pattern>
		<template>
			No lo se 
		</template>
	</category>
~~~
# MANCALA

## Objetivo del juego

* Debemos obtener un mayor número de semillas en nustro granero que nuestro contrincante

* Fin del juego: cuando alguno de los dos jugadores no tenga semillas en sus casillas

* Si se llega al fin del juego y uno de los jugadores aún tiene semillas en sus casillas, automáticamente las recogerá y las sumará a su granero.

## Reglas especiales

* Turno extra: cuando un jugador siembra una semilla y la última semilla la deposita en su granero, gana un turno extra y vuelve a jugar.
* Robo: si al realizar una siembra, la última semilla del jugador cae en una de sus casillas que esté vacía, pero la opuesta del contricante no, entonces el jugador lleva directamente esa semilla y las de la casilla del jugador contrario a su granero.
* Inmolación: si un jugador intenta hacer un movimiento no permitido(sembrar una casilla que no tiene semillas), automáticamente perderá la partida por 42 semillas a 0

## Objetivo de la práctica

* Deberá poder jugar como J1 o como J2.
* Implementar comportamiento deliberativo basado en búsqueda en entornos con adversario.
* Tiempo de turno limitado: 2 segundos.
* Heurística para saber cómo de bueno es un estado para el jugador.
* 2 segundos -> generar 140.000 estados del juego en el simulador.

## Creación de un bot


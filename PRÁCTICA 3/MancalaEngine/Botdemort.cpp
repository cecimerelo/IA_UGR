/*
 * Botdemort.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Botdemort.h"

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

Botdemort::Botdemort() {
	// Inicializar las variables necesarias para ejecutar la partida, reserva de memoria

}

Botdemort::~Botdemort() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void Botdemort::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string Botdemort::getName() {
	return "Botdemort"; // Sustituir por el nombre del bot
}

Move Botdemort::nextMove(const vector<Move> &adversary, const GameState &state) {

	Move movimiento= M_NONE;

	/*
	* - const vector<Move> &adversary: lista ordenada de los ultimos movimientos
	del adversario. Será 0 si fue un turno extra o si es el primer turno
	*/
	// Implementar aquí la selección de la acción a realizar

	// OJO: Recordatorio. NO USAR cin NI cout.
	// Para salidas por consola (debug) utilizar cerr. Ejemplo:
	// cerr<< "Lo que quiero mostrar"<<endl;


	// OJO: Recordatorio. El nombre del bot y de la clase deben coincidir.
	// En caso contrario, el bot no podrá participar en la competición.
	// Se deberá sustituir el nombre Botdemort como nombre de la clase por otro
	// seleccionado por el alumno. Se deberá actualizar también el nombre
	// devuelto por el método getName() acordemente.

	return movimiento;
}

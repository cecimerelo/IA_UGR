/*
 * Botdemort.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Botdemort.h"

#include <climits>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

Botdemort::Botdemort()
{
	// Inicializar las variables necesarias para ejecutar la partida, reserva de memoria
}

Botdemort::~Botdemort()
{
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void Botdemort::initialize()
{
	// Inicializar el bot antes de jugar una partida
}

string Botdemort::getName()
{
	return "Botdemort"; // Sustituir por el nombre del bot
}

/*
	profundidad: longitud del camino que comienza en la raiz y acaba en 
	el Nodo 
*/

int Botdemort::minimaxConPodaAlfaBeta(const GameState &tablero, int profundidad, int alpha, int beta, bool jugadorAMaximizar, Player jugador)
{
	Nodo node;

	GameState hijo;
	Move movimientosPosibles[6] = {M1, M2, M3, M4, M5, M6};
	int aux1 = 0;

	// el valor del tablero sería el numero de semillas en el granero del jugador
	if (tablero.isFinalState() or profundidad == 0)
		return tablero.getScore(jugador);

	if (jugadorAMaximizar)
	{
		aux1 = INT_MIN;
		// para cada  movimiento posible del juego
		for (int i = 0; i < 6; i++)
		{
			hijo = tablero.simulateMove(movimientosPosibles[i]);
			aux1 = max(aux1, minimaxConPodaAlfaBeta(hijo, profundidad - 1, alpha, beta, false, jugador));

			alpha = max(alpha, aux1);

			if (beta <= alpha)
				break;
		}

		return aux1;
	}

	else
	{
		aux1 = INT_MAX;
		for (int i = 0; i < 6; i++)
		{
			hijo = tablero.simulateMove(movimientosPosibles[i]);
			aux1 = min(aux1, minimaxConPodaAlfaBeta(hijo, profundidad - 1, alpha, beta, true, jugador));

			beta = min(beta, aux1);
			if (beta <= alpha)
				break;
		}

		return aux1;
	}
}

Move Botdemort::nextMove(const vector<Move> &adversary, const GameState &state)
{
	Move movimiento = M_NONE;

	Player jugador = state.getCurrentPlayer();

	long timeout = this->getTimeOut();

	Nodo aux;

	GameState hijo;

	int maxValor = 0;

	Move movimientosPosibles[6] = {M1, M2, M3, M4, M5, M6};

	for (int i = 0; i < 6; i++)
	{
		hijo = state.simulateMove(movimientosPosibles[i]);
		aux.movimiento = movimientosPosibles[i];
		aux.puntuacion = minimaxConPodaAlfaBeta(hijo, 9, INT_MIN, INT_MAX, true, jugador);

		if (aux.puntuacion > maxValor)
		{
			maxValor = aux.puntuacion;
			movimiento = aux.movimiento;
		}
	}

	return movimiento;
}

/*
Nodo::Nodo(){};

void Nodo::setChild(Nodo child)
{
	child.setParent(this);
	children.push_back(child);
}

void Nodo::setParent(Nodo *p)
{
	parent = p;
}

bool Nodo::hasChildren()
{
	bool tieneHijos = false;
	if (children.size() > 0)
		tieneHijos = true;

	return tieneHijos;
}

bool Nodo::hasParent()
{
	bool tienePadre = false;

	if (parent != NULL)
		tienePadre = true;

	return tienePadre;
}

Nodo *Nodo::getParent()
{
	return parent;
}
Nodo Nodo::getChild(int pos)
{

	list<Nodo>::iterator it = children.begin();
	Nodo aux;
	int tam;

	for (it = children.begin(); it != children.end(); ++it)
	{
		aux = *it;
		tam++;

		if (tam == pos)
			break;
	}

	return aux;
}

int Nodo::obtenerProfundidad(Nodo *node){

	int profundidad = 0;
	Nodo *aux;

	while( (*aux).hasParent()){
		profundidad++;
		aux = (*aux).getParent();
	}

	return profundidad;
}

int Nodo::childrenNumber()
{
	return children.size();
}

*/

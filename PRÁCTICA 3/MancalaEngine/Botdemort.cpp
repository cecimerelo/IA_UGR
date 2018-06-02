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
int Botdemort::evaluaNodo(const GameState &tablero, Player me)
{
	int sumaMe = 0,
		sumaContrario = 0,
		sumaTotal = 0;
	Player contrario;

	if (me == J1)
		contrario = J2;
	else
		contrario = J1;

	//recorremos nuestras casillas para intentar mantener el mayor número de piezas
	for (int i = 1; i < 7; i++)
	{
		sumaMe = tablero.getSeedsAt(me, (Position)i);
	}

	sumaContrario += tablero.getScore(contrario);
	sumaMe += tablero.getScore(me);

	sumaTotal = sumaMe - (sumaContrario/2);

	return sumaTotal;
}

int Botdemort::minimaxConPodaAlfaBeta(const GameState &tablero, int profundidad, int alpha, int beta, Player me)
{
	Nodo node;
	GameState hijo;
	Move movimientosPosibles[6] = {M1, M2, M3, M4, M5, M6};
	int aux1 = 0;

	// el valor del tablero sería el numero de semillas en el granero del jugador
	if (tablero.isFinalState() || profundidad == 0)
		return evaluaNodo(tablero,me);

	if (tablero.getCurrentPlayer() == me)
	{
		aux1 = INT_MIN;
		// para cada  movimiento posible del juego
		for (int i = 0; i < 6; i++)
		{
			if (tablero.getSeedsAt(tablero.getCurrentPlayer(), (Position)(i + 1)) > 0)
			{
				hijo = tablero.simulateMove(movimientosPosibles[i]);
				aux1 = max(aux1, minimaxConPodaAlfaBeta(hijo, profundidad - 1, alpha, beta, me));

				alpha = max(alpha, aux1);

				if (beta <= alpha) //poda correcta
					return beta;
			}
		}

		return aux1;
	}

	else
	{
		aux1 = INT_MAX;
		for (int i = 0; i < 6; i++)
		{
			if (tablero.getSeedsAt(tablero.getCurrentPlayer(), (Position)(i + 1)) > 0)
			{
				hijo = tablero.simulateMove(movimientosPosibles[i]);
				aux1 = min(aux1, minimaxConPodaAlfaBeta(hijo, profundidad - 1, alpha, beta, me));

				beta = min(beta, aux1);
				if (beta <= alpha) //poda correcta
					return alpha;
			}
		}

		return aux1;
	}
}

Move Botdemort::nextMove(const vector<Move> &adversary, const GameState &state)
{
	Move movimiento = M_NONE;

	Player me = this->getPlayer();

	long timeout = this->getTimeOut();

	Nodo aux;

	GameState hijo;

	int maxValor = 0;

	Move movimientosPosibles[6] = {M1, M2, M3, M4, M5, M6};

	for (int i = 0; i < 6; i++)
	{
		hijo = state.simulateMove(movimientosPosibles[i]);
		aux.movimiento = movimientosPosibles[i];
		aux.puntuacion = minimaxConPodaAlfaBeta(hijo, 7, INT_MIN, INT_MAX, me);

		cerr << "aux.puntuacion: " << aux.puntuacion << " > " << maxValor << endl;
		if (aux.puntuacion > maxValor)
		{
			maxValor = aux.puntuacion;
			movimiento = aux.movimiento;
		}
		else if (aux.puntuacion == maxValor && hijo.getCurrentPlayer() == me)
		{
			movimiento = aux.movimiento;
		}
	}

	return movimiento;
}

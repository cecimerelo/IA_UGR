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
int Botdemort::evaluaNodo(const GameState &tablero) // 0. No le he pasado player pq no esta en el .h
{
	return tablero.getScore(me);
}

int Botdemort::minimaxConPodaAlfaBeta(const GameState &tablero, int profundidad, int alpha, int beta, bool jugadorAMaximizar)
{
	GameState hijo;
	Move movimientosPosibles[6] = {M1, M2, M3, M4, M5, M6};
	int aux1;

	if (tablero.isFinalState() or profundidad == 0)
		return evaluaNodo(tablero);

	if (jugadorAMaximizar)
	{
		alpha = INT_MIN;
		// para cada  movimiento posible del juego
		for (int i = 0; i < 6; i++)
		{
			if (tablero.getSeedsAt(me, (Position)(i + 1)) > 0)
			{
				hijo = tablero.simulateMove(movimientosPosibles[i]);
				aux1 = max(aux1, minimaxConPodaAlfaBeta(hijo, profundidad - 1, alpha, beta, (hijo.getCurrentPlayer() == tablero.getCurrentPlayer())));

				alpha = max(alpha, aux1);

				if (beta <= alpha)
					break;
			}
		}

		//should be aux1
		return alpha;
	}

	else
	{
		beta = INT_MAX;
		for (int i = 0; i < 6; i++)
		{
			if (tablero.getSeedsAt(contrario, (Position)(i + 1)) > 0)
			{
				hijo = tablero.simulateMove(movimientosPosibles[i]);
				aux1 = min(aux1,minimaxConPodaAlfaBeta(hijo, profundidad - 1, alpha, beta, !(hijo.getCurrentPlayer() == tablero.getCurrentPlayer())));

				beta = min(beta, aux1);
				if (beta <= alpha)
					break;
			}
		}

		return beta;
	}
}

Move Botdemort::nextMove(const vector<Move> &adversary, const GameState &state)
{
	Move movimiento = M_NONE;

	me = this->getPlayer();

	if (me == J1)
		contrario = J2;
	else
		contrario = J1;

	long timeout = this->getTimeOut();

	Nodo aux;

	GameState hijo;

	int maxValor = INT_MIN;

	Move movimientosPosibles[6] = {M1, M2, M3, M4, M5, M6};

	cerr << "me: " << me << ", contrario: " << contrario <<endl;

	for (int i = 0; i < 6; i++)
	{
		if (state.getSeedsAt(me, (Position)(i + 1)) > 0)
		{

			hijo = state.simulateMove(movimientosPosibles[i]);
			aux.movimiento = movimientosPosibles[i];
			aux.puntuacion = minimaxConPodaAlfaBeta(hijo, 9, INT_MIN, INT_MAX, true);

			if (aux.puntuacion > maxValor)
			{
				maxValor = aux.puntuacion;
				movimiento = aux.movimiento;
			}

		}
	}

	return movimiento;
}

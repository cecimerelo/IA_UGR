/*
 * Botdemort.h
 *
 *  Created on: 15 ene. 2018
 *      Author: cecimerelo
 */

#include "Bot.h"
#include <list>
#include <queue>

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

using namespace std;

struct Nodo
{
	Move movimiento;
	int puntuacion;
};

class Botdemort : Bot
{
  private:
	Player me;
	Player contrario;

  public:
	Botdemort();
	~Botdemort();

	int evaluaNodo(const GameState &tablero, Player me);
	Move proximoMovimiento(Nodo state, Player jugador);
	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);
	bool esNodoTerminal(Nodo estado);
	int minimaxConPodaAlfaBeta(const GameState &tablero, int profundidad, int alpha, int beta, Player me);
};

#endif
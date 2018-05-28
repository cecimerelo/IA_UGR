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

/*
class Nodo
{
  public:
	Nodo *parent;
	GameState estado;
	list<Nodo> children;

	Nodo();
	Nodo(std::string iTextContent, std::string iTagName);

	void setChild(Nodo child);
	void setParent(Nodo *parent);

	bool hasChildren();
	bool hasParent();

	Nodo *getParent();
	Nodo getChild(int pos);

	int obtenerProfundidad(Nodo *node);
	int childrenNumber();
};
*/
class Botdemort : Bot
{

  public:
	Botdemort();
	~Botdemort();

	Move proximoMovimiento(Nodo state, Player jugador);
	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);
	bool esNodoTerminal(Nodo estado);
	int minimaxConPodaAlfaBeta(const GameState &tablero, int profundidad, int alpha, int beta, bool jugadorAMaximizar, Player jugador);
};

#endif
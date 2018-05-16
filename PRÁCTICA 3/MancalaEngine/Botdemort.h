/*
 * Botdemort.h
 *
 *  Created on: 15 ene. 2018
 *      Author: cecimerelo
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

class Botdemort:Bot {
public:
	Botdemort();
	~Botdemort();


	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);
};

#endif /* MANUPCBOT_H_ */

#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <stack>

void ComportamientoJugador::PintaPlan(list<Action> plan)
{
	auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			cout << "A ";
		}
		else if (*it == actTURN_R)
		{
			cout << "D ";
		}
		else if (*it == actTURN_L)
		{
			cout << "I ";
		}
		else
		{
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}
bool ComportamientoJugador::esSueloValido(int fila, int columna)
{
	bool valido = false;

	//cout << "Dentro de esSueloValido con " << fila << ":" << columna << endl << fflush ;
	//cout << "Es suelo valido: " << mapaResultado[fila][columna] << endl << fflush;

	if (fila != posAldeano.first or columna != posAldeano.second)
	{

		if (mapaResultado[fila][columna] == 'S' or mapaResultado[fila][columna] == 'T' or mapaResultado[fila][columna] == 'K')
		{
			valido = true;
		}
	}

	return valido;
}

bool ComportamientoJugador::comprobacionNodo(list<nodo> lista, nodo aux)
{
	//cout << "Dentro de comprobacionNodo" << endl << fflush;
	bool valido = false;

	list<nodo>::iterator it;

	//cout << "Empezamos bucle" << endl << fflush;
	for (it = lista.begin(); it != lista.end(); ++it)
	{
		if ((*it).posicion.fila == aux.posicion.fila and (*it).posicion.columna == aux.posicion.columna)
		{
			break;
		}
	}
	//cout << "Salimos bucle" << endl << fflush;
	if (it == lista.end())
	{
		valido = true;
	}

	//cout << "Valido : " << valido << endl << fflush;

	return valido;
}

list<nodo>::iterator ComportamientoJugador::devuelveIteradorAPadre(list<nodo> &cerrados, nodo actual)
{
	list<nodo>::iterator it = cerrados.begin();

	for (it = cerrados.begin(); it != cerrados.end(); ++it)
		if ((*it).posicion.fila == actual.posicion.fila and (*it).posicion.columna == actual.posicion.columna)
			break;

	return it;
}

void ComportamientoJugador::muestraLista(list<nodo> lista)
{
	list<nodo>::iterator it;

	for (it = lista.begin(); it != lista.end(); ++it)
	{
		cout << (*it).posicion.fila << ":" << (*it).posicion.columna << endl;
	}
}

bool ComportamientoJugador::pathFinding(const estado &origen, const estado &destino, list<Action> &plan)
{
	plan.clear();
	list<nodo> nodosAbiertos;
	list<nodo> nodosCerrados;
	stack<nodo> recorrido;
	nodo actual;
	nodo aux;

	actual.posicion = origen;

	nodosAbiertos.push_back(actual);

	while (true)
	{
		//cout << "\nLista abiertos actual: " << endl;
		//muestraLista(nodosAbiertos);

		actual = nodosAbiertos.front();
		//cout << "Front de la lista de abiertos: " << actual.posicion.fila << ":" << actual.posicion.columna << endl;

		nodosAbiertos.pop_front();
		//cout << "Sacado actual de abiertos" << endl;

		//como ya lo hemos visitado lo metemos en cerrados
		nodosCerrados.push_back(actual);
		//cout << "Metido actual en cerrados" << endl;

		//cout << "Lista cerrados actual: " << endl;
		//muestraLista(nodosCerrados);

		//comrpobamos si es solución
		//comprueba nodo de en frente
		//cout << "Pasamos a comprobar los adyacentes: " << endl;

		if (esSueloValido(actual.posicion.fila - 1, actual.posicion.columna))
		{
			//cout << "Nodo de en frente valido" << endl << fflush;
			aux.posicion.fila = actual.posicion.fila - 1;
			aux.posicion.columna = actual.posicion.columna;
			aux.posicion.orientacion = 0;
			aux.padre = devuelveIteradorAPadre(nodosCerrados, actual);

			//el hijo no está ni en abiertos ni en cerrados y es viable
			if (comprobacionNodo(nodosAbiertos, aux) && comprobacionNodo(nodosCerrados, aux))
			{
				nodosAbiertos.push_back(aux);
				//cout << "Soy: " << aux.posicion.fila << ":" << aux.posicion.columna << " y mi padre" << (*aux.padre).posicion.fila << ":" << (*aux.padre).posicion.columna << endl;

				if (aux.posicion.fila == destino.fila && aux.posicion.columna == destino.columna)
				{
					break;
				}
			}
		}

		//comprueba nodo de la derecha
		if (esSueloValido(actual.posicion.fila, actual.posicion.columna + 1))
		{
			aux.posicion.fila = actual.posicion.fila;
			aux.posicion.columna = actual.posicion.columna + 1;
			aux.posicion.orientacion = 1;
			aux.padre = devuelveIteradorAPadre(nodosCerrados, actual);

			if (comprobacionNodo(nodosAbiertos, aux) && comprobacionNodo(nodosCerrados, aux))
			{
				nodosAbiertos.push_back(aux);
				//cout << "Soy: " << aux.posicion.fila << ":" << aux.posicion.columna << " y mi padre" << (*aux.padre).posicion.fila << ":" << (*aux.padre).posicion.columna << endl;
			}

			if (aux.posicion.fila == destino.fila && aux.posicion.columna == destino.columna)
			{
				break;
			}
		}

		//comprueba nodo de abajo
		if (esSueloValido(actual.posicion.fila + 1, actual.posicion.columna))
		{
			aux.posicion.fila = actual.posicion.fila + 1;
			aux.posicion.columna = actual.posicion.columna;
			aux.posicion.orientacion = 2;
			aux.padre = devuelveIteradorAPadre(nodosCerrados, actual);

			if (comprobacionNodo(nodosAbiertos, aux) && comprobacionNodo(nodosCerrados, aux))
			{
				nodosAbiertos.push_back(aux);
				//cout << "Soy: " << aux.posicion.fila << ":" << aux.posicion.columna << " y mi padre" << (*aux.padre).posicion.fila << ":" << (*aux.padre).posicion.columna << endl;
			}

			if (aux.posicion.fila == destino.fila && aux.posicion.columna == destino.columna)
			{
				break;
			}
		}

		//comprueba nodo de la izquierda
		if (esSueloValido(actual.posicion.fila, actual.posicion.columna - 1))
		{
			aux.posicion.fila = actual.posicion.fila;
			aux.posicion.columna = actual.posicion.columna - 1;
			aux.posicion.orientacion = 3;
			aux.padre = devuelveIteradorAPadre(nodosCerrados, actual);

			if (comprobacionNodo(nodosAbiertos, aux) && comprobacionNodo(nodosCerrados, aux))
			{
				nodosAbiertos.push_back(aux);
				//cout << "Soy: " << aux.posicion.fila << ":" << aux.posicion.columna << " y mi padre" << (*aux.padre).posicion.fila << ":" << (*aux.padre).posicion.columna << endl;
			}

			if (aux.posicion.fila == destino.fila && aux.posicion.columna == destino.columna)
			{
				break;
			}
		}
	}

	//cout << "Lista de cerrados: ";
	//muestraLista(nodosCerrados);

	//cout << "Destino " << destino.fila << " : " << destino.columna;
	//cout << "Aux " << aux.posicion.fila << " : " << aux.posicion.columna;

	while (aux.posicion.fila != origen.fila || aux.posicion.columna != origen.columna)
	{
		//cout << "Lista del plan" << endl;
		//cout << "F:" << aux.posicion.fila << "- C:" << aux.posicion.columna;
		recorrido.push(aux);
		aux = *aux.padre;
	}

	//hasta aquí tenemos el plan
	recorrido.push(aux);

	int operacion;
	actual = recorrido.top();
	recorrido.pop();

	while (!recorrido.empty())
	{
		aux = recorrido.top();
		operacion = actual.posicion.orientacion - aux.posicion.orientacion;

		if (operacion == -1 || operacion == 3)
		{
			plan.push_back(actTURN_R);
			plan.push_back(actFORWARD);
		}

		else if (operacion == 1 || operacion == -3)
		{
			plan.push_back(actTURN_L);
			plan.push_back(actFORWARD);
		}

		else if (operacion == 2 || operacion == -2)
		{
			plan.push_back(actTURN_R);
			plan.push_back(actTURN_R);
			plan.push_back(actFORWARD);
		}

		else
		{
			plan.push_back(actFORWARD);
		}

		actual = aux;
		recorrido.pop();
	}
	// Descomentar para ver el plan en el mapa
	VisualizaPlan(origen, plan);

	return true;
}

Action ComportamientoJugador::think(Sensores sensores)
{
	if (sensores.mensajeF != -1)
	{
		fil = sensores.mensajeF;
		col = sensores.mensajeC;
	}

	// Actualizar el efecto de la ultima accion
	switch (ultimaAccion)
	{
	case actTURN_R:
		brujula = (brujula + 1) % 4;
		break;
	case actTURN_L:
		brujula = (brujula + 3) % 4;
		break;
	case actFORWARD:
		if (sensores.mensajeF == -1)
		{
			switch (brujula)
			{
			case 0:
				fil--;
				break;
			case 1:
				col++;
				break;
			case 2:
				fil++;
				break;
			case 3:
				col--;
				break;
			}
		}
		//cout << "fil: " << fil << "  col: " << col << " Or: " << brujula << endl;
	}

	// Determinar si ha cambiado el destino desde la ultima planificacion
	if (hayPlan and (sensores.destinoF != destino.fila or sensores.destinoC != destino.columna))
	{
		cout << "El destino ha cambiado\n";
		hayPlan = false;
	}

	//Comprobar si la siguiente casilla es un aldeano
	if (hayPlan && sensores.superficie[2] == 'a' && plan.front() == actFORWARD)
	{
		//almacenamos la casilla en la que se encontraba el aldenano
		switch (brujula)
		{
		case 0:
			posAldeano = make_pair(fil - 1, col);
			break;
		case 1:
			posAldeano = make_pair(fil, col + 1);
			break;
		case 2:
			posAldeano = make_pair(fil + 1, col);
			break;
		case 3:
			posAldeano = make_pair(fil, col - 1);
			break;
		}

		hayPlan = false;
	}

	// Determinar si tengo que construir un plan
	if (!hayPlan)
	{
		estado origen;
		origen.fila = fil;
		origen.columna = col;
		origen.orientacion = brujula;

		destino.fila = sensores.destinoF;
		destino.columna = sensores.destinoC;

		hayPlan = pathFinding(origen, destino, plan);
		posAldeano = make_pair(-1, -1);
	}

	// Ejecutar el plan
	Action sigAccion;
	if (hayPlan and plan.size() > 0)
	{
		sigAccion = plan.front();
		plan.erase(plan.begin());
	}
	else
	{
		sigAccion = actIDLE;
	}

	ultimaAccion = sigAccion;
	return sigAccion;
}

void AnularMatriz(vector<vector<unsigned char>> &m)
{
	for (int i = 0; i < m[0].size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			m[i][j] = 0;
		}
	}
}

void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan)
{
	AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			switch (cst.orientacion)
			{
			case 0:
				cst.fila--;
				break;
			case 1:
				cst.columna++;
				break;
			case 2:
				cst.fila++;
				break;
			case 3:
				cst.columna--;
				break;
			}
			mapaConPlan[cst.fila][cst.columna] = 1;
		}
		else if (*it == actTURN_R)
		{
			cst.orientacion = (cst.orientacion + 1) % 4;
		}
		else
		{
			cst.orientacion = (cst.orientacion + 3) % 4;
		}
		it++;
	}
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

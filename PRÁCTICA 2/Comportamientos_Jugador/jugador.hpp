#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct estado
{
  int fila;
  int columna;
  int orientacion;
};

struct nodo
{
  estado posicion;
  list<nodo>::iterator padre; //nodos por los que pasa
};

class ComportamientoJugador : public Comportamiento
{
public:
  ComportamientoJugador(unsigned int size) : Comportamiento(size)
  {
    // Inicializar Variables de Estado
    fil = col = 99;
    brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
    destino.fila = -1;
    destino.columna = -1;
    destino.orientacion = -1;
    hayPlan = false;
    ultimaAccion = actIDLE;
    pair<int,int> posAldeano = make_pair(-1,-1);

  }
  ComportamientoJugador(std::vector<std::vector<unsigned char>> mapaR) : Comportamiento(mapaR)
  {
    // Inicializar Variables de Estado
    fil = col = 99;
    brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
    destino.fila = -1;
    destino.columna = -1;
    destino.orientacion = -1;
    hayPlan = false;
    ultimaAccion = actIDLE;
    pair<int,int> posAldeano = make_pair(-1,-1);

  }
  ComportamientoJugador(const ComportamientoJugador &comport) : Comportamiento(comport) {}
  ~ComportamientoJugador() {}

  Action think(Sensores sensores);
  int interact(Action accion, int valor);
  void VisualizaPlan(const estado &st, const list<Action> &plan);
  bool esSueloValido(int fila, int columna);
  bool comprobacionNodo(list<nodo> lista, nodo aux);
  void muestraLista(list<nodo> lista);
  list<nodo>::iterator devuelveIteradorAPadre(list<nodo> &cerrados, nodo actual);
  ComportamientoJugador *clone() { return new ComportamientoJugador(*this); }

private:
  // Declarar Variables de Estado
  Action ultimaAccion;
  int fil, col, brujula;
  estado destino;
  list<Action> plan;
  bool hayPlan;
  pair<int,int> posAldeano;

  bool pathFinding(const estado &origen, const estado &destino, list<Action> &plan);
  void PintaPlan(list<Action> plan);
};

#endif

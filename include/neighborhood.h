#pragma once
#include "../include/solution.h"

typedef struct Neighborhood {
  int size;
  Solution** data;
} Neighborhood;

void freeNeighborhood(Neighborhood *neighborhood);

// dada una solucion, devuelve un array con sus soluciones vecinas hamming. k indica la distancia
void hammingNeighborhood(Neighborhood *neighborhood, Solution *sol, int k);

// realiza la operacion insert en una lista de booleanos
void insert(bool *list, int from, int to);

// recibe una solución y devuelve una lista de soluciones
void insertNeighborhood(Neighborhood *neighborhood, Solution *sol);

// imprime datos del vecindario (cuantos vecinos tiene, ...)
void descNeighborhood(Neighborhood *neighborhood);

// recupera la mejor solución de un vecindario. En *sol deposita la direccion de la mejor solución del vecindario
int getBestSolution(Solution *sol, Neighborhood *neighborhood, Gpp *gpp);

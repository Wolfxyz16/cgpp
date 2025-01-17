#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/neighborhood.h"
#include "../include/solution.h"

void freeNeighborhood(Neighborhood *neighborhood)
{
  for( int i = 0; i < neighborhood->size; i++ ) freeSolution(neighborhood->data[i]);
  free(neighborhood);
}

void hammingNeighborhood(Neighborhood *neighborhood, Solution *sol, int k)
{
  int i;
  int size = sol->size;
  int count = 0;
  Solution *newSolution = (Solution*) malloc(sizeof(Solution));
  newSolution->data = (bool*) malloc(sizeof(bool) * size);

  for( i = 0; i < size; i++ )
  {
    // copiamos la solucion original
    solcpy(newSolution, sol);

    // alteramos un bit
    newSolution->data[i] = !newSolution->data[i];

    // almacenamos la nueva solucion
    neighborhood->data[count] = (Solution*) malloc(sizeof(Solution));
    neighborhood->data[count]->data = (bool*) malloc(sizeof(bool) * size);
    solcpy(neighborhood->data[count], newSolution);
    count++;

    if( k > 1 ) hammingNeighborhood(neighborhood, newSolution, k - 1);
  }
  freeSolution(newSolution);
}

void insert(bool *list, int from, int to)
{
  int i;
  bool copia = list[from];
  // queremos insertar a la derecha
  if( from < to )
  {
    for( i = from; i < to; i++ ) list[i] = list[i + 1];
  // queremos insertar a la izquierda
  } else {
    for( i = from; i > to; i-- ) list[i] = list[i - 1];
  }
  list[to] = copia;
}

void insertNeighborhood(Neighborhood *neighborhood, Solution *sol)
{
  // ¿Cada vez el tamaño del vecindario cambia? No tiene sentido
  int to, from, count = 0, i = 0, size = sol->size;
  // calculamos cuantos vecinos unicos hay
  bool duplicated = false;
  Solution *solution = (Solution*) malloc(sizeof(Solution));
  solution->data = (bool*) malloc(sizeof(bool) * size);

  for( from = 0; from < size; from++ )
  {
    for( to = 0; to < size; to++ )
    {
      if( from == to ) continue;
      duplicated = false;
      // copiamos la solucion original y le hacemos un insert
      solcpy(solution, sol);
      insert(solution->data, from, to);

      // comprobamos si la solucion que hemos creado ya existe dentro de las soluciones
      for( i = 0; i < count; i++ )
      {
        if( areEquals(solution, neighborhood->data[i]) )
        {
          duplicated = true;
          break;
        }
      }

      // si no esta duplicada la insertamos en la lista
      if( !duplicated )
      {
        neighborhood->data[count] = (Solution*) malloc(sizeof(Solution));
        neighborhood->data[count]->data = (bool*) malloc(sizeof(bool) * size);
        solcpy(neighborhood->data[count], solution);
        count++;
      }
    }
  }
  neighborhood->size = count;
  freeSolution(solution);
}

void descNeighborhood(Neighborhood *neighborhood)
{
  printf("This neighborhood has %d solutions.\n", neighborhood->size);
}

// devuelve un entero que indica el fitness y en *sol la mejor solucion encontrada
int getBestSolution(Solution *sol, Neighborhood *neighborhood, Gpp *gpp)
{
  Solution *bestSolution = (Solution*) malloc(sizeof(Solution));
  initializeSolution(bestSolution, gpp->numNodes);

  solcpy(bestSolution, neighborhood->data[0]);
  int bestFitness = objectiveFunction(bestSolution, gpp);
  int newFitness = 9999999;

  for( int i = 1; i < neighborhood->size; i++ )
  {
    newFitness = objectiveFunction(neighborhood->data[i], gpp);
    if( newFitness < bestFitness )
    {
      newFitness = bestFitness;
      bestSolution = neighborhood->data[i];
    }
  }
  
  solcpy(sol, bestSolution);
  free(bestSolution);
  return bestFitness;
}

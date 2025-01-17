#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/random.h>
#include "../include/solution.h"
#include "../include/gpp.h"

// Las soluciones dentro del GPP deben de ser equilibradas, es decir, deben tener el mismo numero
// de true y false 

void printSolution(Solution *sol)
{
  for( int i = 0; i < sol->size; i++ ) printf("%d ", sol->data[i]);
  printf("\nSize: %d\n", sol->size);
}

void freeSolution(Solution *sol)
{
  free(sol->data);
  free(sol);
}

void initializeSolution(Solution *sol, unsigned int size)
{
  sol->size = size;
  sol->data = (bool*) malloc(size * sizeof(bool));
}

void randomMixSolution(Solution *sol)
{
  unsigned int randomIndex;
  int n = sol->size;
  for( int i = 0; i < n; i++ )
  {
    // generamos un índice aleatorio del vector
    getrandom(&randomIndex, sizeof(int), 0);
    randomIndex = randomIndex % n;
    // hacemos swap entre la posicion i y la random
    swap(&sol->data[i], &sol->data[randomIndex]);
  }
}

void swap(bool *a, bool *b) {
    bool temp = *a;
    *a = *b;
    *b = temp;
}

void createRandomSolution(Solution *sol)
{
  int size = sol->size;
  int halfIndex = size / 2;

  for( int i = 0; i < size; i++ )
  {
    if( i < halfIndex ) sol->data[i] = true;
    else                sol->data[i] = false;
  }
  randomMixSolution(sol);
}

int objectiveFunction(Solution *sol, Gpp *gpp) 
{
  int i, j;
  int n = sol->size;
  int fitness = 0;

  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      // si están en dos particiones distintas y...
      // existe una arista entre i y j sumamos 1
      if( sol->data[i] != sol->data[j] && connectionExists(&gpp->conn[i], j) ) fitness += 1;
    }
  }
  return fitness;
}

Solution *solcpy(Solution *dest, Solution *src)
{
  dest->size = src->size;
  memcpy(dest->data, src->data, sizeof(bool) * dest->size);
  return dest;
}

bool isBalanced(Solution *sol)
{
  int diff, trueCount = 0;
  bool isEven = (sol->size % 2) == 0;

  // contamos los true
  for( int i = 0; i < sol->size; i++ )
  {
    if( sol->data[i] ) trueCount++;
  }

  diff = sol->size - 2 * trueCount;

  // para que este balanceado la diferencia debe ser solo 0, si es par 
  // para que este balanceado la diferencia debe ser 1 o -1, si es impar 
  if( isEven && diff == 0 ) return true;
  else if( !isEven && (diff == 1 || diff == -1) ) return true;
  else return false;
}

bool areEquals(Solution *sol1, Solution *sol2)
{
  if( sol1->size != sol2->size ) return false;
  int length = sol1->size;

  for( int i = 0; i < length; i++ )
  {
    if(sol1->data[i] != sol2->data[i]) return false;
  }

  return true;
}

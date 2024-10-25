#include <stdlib.h>
#include <stdio.h>
#include "../include/gpp.h"
#include "../include/solution.h"

int main(int argc, char *argv[])
{
  Gpp *gpp = loadGPP("data/Grid8x8");

  Solution *sol = (Solution*) malloc(sizeof(sol));

  createRandomSolution(sol, gpp->numNodes);

  printSolution(sol);

  int fitness = objectiveFunction(sol, gpp);

  printf("fitness = %d\n", fitness);

  freeGPP(gpp);
  
  return EXIT_SUCCESS;
}

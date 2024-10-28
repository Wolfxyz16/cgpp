#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/gpp.h"
#include "../include/solution.h"
#include "../include/neighborhood.h"

int main(int argc, char *argv[])
{
  Gpp *gpp = loadGPP("data/Grid8x8");

  Solution *sol1 = (Solution*) malloc(sizeof(Solution));
  Solution *sol2 = (Solution*) malloc(sizeof(Solution));
  Solution *sol3 = (Solution*) malloc(sizeof(Solution));

  createRandomSolution(sol1, gpp->numNodes);

  int numNeighbour = (sol1->size * (sol1->size - 1) - (sol1->size - 1));
  printf("numNeighbour = %d\n", numNeighbour);

  Neighborhood *hamming = (Neighborhood*) malloc(sizeof(Neighborhood));
  hamming->size = numNeighbour;
  hamming->data = (Solution**) malloc(sizeof(Solution*) * 1000000);

  Neighborhood *insert = (Neighborhood*) malloc(sizeof(Neighborhood));
  insert->size = numNeighbour;
  insert->data = (Solution**) malloc(sizeof(Solution*) * numNeighbour);

  hammingNeighborhood(hamming, sol1, 1);
  insertNeighborhood(insert, sol1);

  descNeighborhood(hamming);
  descNeighborhood(insert);

  sol3 = getBestSolution(hamming, gpp);
  sol2 = getBestSolution(insert, gpp);

  printf("isBalanced(sol3) = %d\n", isBalanced(sol3));
  printf("isBalanced(sol2) = %d\n", isBalanced(sol2));

  printf("objectiveFunction(sol1, gpp) = %d\n", objectiveFunction(sol1, gpp));
  printf("objectiveFunction(sol3, gpp) = %d\n", objectiveFunction(sol3, gpp));
  printf("objectiveFunction(sol2, gpp) = %d\n", objectiveFunction(sol2, gpp));

  freeGPP(gpp);
  freeSolution(sol1);
  freeSolution(sol2);
  freeSolution(sol3);
  freeNeighborhood(insert);
  freeNeighborhood(hamming);
  
  return EXIT_SUCCESS;
}

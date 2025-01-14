#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/solution.h"
#include "../include/search.h"
#include "../include/neighborhood.h"

// dada una solucion realiza una busqueda random
void randomSearch(Solution *sol, unsigned int max_iterations, Gpp *gpp)
{
  clock_t start, end;
  double elapsed;
  Solution *randomSolution, *bestSolution;
  int bestFitness, randomFitness;

  randomSolution = (Solution*) malloc(sizeof(Solution));

  initializeSolution(randomSolution, sol->size);

  bestSolution = sol;
  bestFitness = objectiveFunction(bestSolution, gpp); 
  start = clock();

  for( int i = 0; i < max_iterations; i++ )
  {
    createRandomSolution(randomSolution);
    randomFitness = objectiveFunction(randomSolution, gpp);

    if( randomFitness < bestFitness )
    {
      bestFitness = randomFitness;
      bestSolution = randomSolution;
    }
  }
  end = clock();
  
  elapsed = (double) (end - start) / CLOCKS_PER_SEC;
  printf("%d iteration executed in %.6f seconds\n", max_iterations, elapsed);
  printf("Best Solution: \n");
  printSolution(bestSolution);
  printf("Fitness: %d\n", bestFitness);

  freeSolution(randomSolution);
}

// realiza una best first search
void bestFirstSearch(Solution *sol, Gpp *gpp)
{
  long int iterations = 0;
  clock_t start, end;
  double elapsed;
  Solution *bestSolution, *candidateSolution;
  int bestFitness, candidateFitness;
  bool isBestSolution = false;
  Neighborhood *neighborhood = (Neighborhood*) malloc(sizeof(Neighborhood));
  neighborhood->data = (Solution**) malloc(sizeof(Solution*) * 5000);

  bestSolution = (Solution*) malloc(sizeof(Solution));
  candidateSolution = (Solution*) malloc(sizeof(Solution));
  initializeSolution(bestSolution, sol->size);
  initializeSolution(candidateSolution, sol->size);

  solcpy(bestSolution, sol);
  bestFitness = objectiveFunction(bestSolution, gpp); 
  start = clock();

  while (!isBestSolution && iterations < 10000000)
  {
    iterations++;
    // calculamos el vecindario de la solucion
    hammingNeighborhood(neighborhood, bestSolution, 1);

    // calculamos la mejor solucion de este vecindario
    candidateFitness = getBestSolution(candidateSolution, neighborhood, gpp);

    printf("bestFitness = %d\n", bestFitness);
    printf("candidateFitness = %d\n", candidateFitness);

    // comprobamos si la nueva solucion mejora a la que tenemos
    if( candidateFitness < bestFitness )
    {
      solcpy(bestSolution, candidateSolution);
      bestFitness = candidateFitness;
    } 
    else 
    {
      isBestSolution = true;
    }
  }
  end = clock();
  elapsed = (double) (end - start) / CLOCKS_PER_SEC;
  printf("%d iteration executed in %.6f seconds\n", iterations, elapsed);
  printf("Best Solution: \n");
  printSolution(bestSolution);
  printf("Fitness: %d\n", bestFitness);

  freeSolution(bestSolution);
  freeSolution(candidateSolution);
}

void variableNeighborhoodDescent(Neighborhood *neighborhood, Solution *sol)
{

}

#pragma once
#include "../include/gpp.h"

typedef struct Solution {
  bool *data;
  int size;
} Solution;

void printSolution(Solution *sol);

void freeSolution(Solution *sol);

// dada una solucion la mezcla aleatoriamente
void randomMixSolution(Solution *sol);

void swap(bool *a, bool *b);

void createRandomSolution(Solution *sol, int size);

int objectiveFunction(Solution *sol, Gpp *gpp);

// copia la solucion de src a dest, ambas soluciones deben de estar inicializadas
Solution *solcpy(Solution *dest, Solution *src);

// comprueba si la solución es balanceada
bool isBalanced(Solution *sol);

// comprueba si las dos soluciones son iguales
bool areEquals(Solution *sol1, Solution *sol2);

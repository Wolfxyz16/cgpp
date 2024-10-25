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

// comprueba si la solución es balanceada
bool isBalanced(Solution *sol);

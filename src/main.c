#include "../include/gpp.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  Gpp *gpp = loadGPP("data/Grid8x8");

  printGPP(gpp);

  // int fitness = objective_function(gpp, ???);

  freeGPP(gpp);
  
  return EXIT_SUCCESS;
}

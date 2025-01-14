#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "../include/gpp.h"
#include "../include/solution.h"
#include "../include/neighborhood.h"
#include "../include/search.h"

int main(int argc, char *argv[])
{
  // comprobamos que haya mas de 1 argumento
  if( argc == 1 ) 
  {
    fprintf(stderr, "Not enough arguments. Please use --help\n");
    exit(EXIT_FAILURE);
  }

  int opt, index;
  char *filename = NULL;
  char *mode_str = (char*) malloc( strlen(argv[1]) );
  strcpy(mode_str, argv[1]);

  // procesamos las flags
  static struct option options[] = {
    {"help", no_argument, 0, 'h'},
    {"file", required_argument, 0, 'f'},
    {0, 0, 0, 0}
  };

  while( ( opt = getopt_long(argc, argv, "hf:",options, &index) ) != -1 )
  {
    switch (opt)
    {
      case 'h':
        printf("Usage: %s [options]\n", argv[0]);
        exit(EXIT_SUCCESS);

      case 'f':
        filename = optarg;
        break;

      case '?':
        fprintf(stderr, "Non valid option\n");
        exit(EXIT_FAILURE);

      default:
        break;
    }
  }

  // comprobar aqui, porque argv[optind] puede ser null
  if( argv[optind] == NULL )
  {
    fprintf(stderr, "Mode not valid.\n");
    exit(EXIT_FAILURE);
  }

  if( mode_str[0] == '-' )
  {
    fprintf(stderr, "Mode can not start with '-'\n");
    exit(EXIT_FAILURE);
  }

  // comprobamos que modo (busqueda) ha elegido el usuario
  char mode = '?';

  if( strcmp(mode_str, "random") == 0 ) mode = 'r';
  else if ( strcmp(mode_str, "local") == 0 ) mode = 'l';
  else if ( strcmp(mode_str, "vnd") == 0 ) mode = 'v';

  // si no hemos leido ningun modo valido, salimos
  if( mode == '?')
  {
    fprintf(stderr, "%s not valid.\n", mode_str); 
    exit(EXIT_FAILURE);
  }

  Gpp *gpp = loadGPP(filename);
  unsigned int size = gpp->numNodes;

  Solution *sol;

  sol = (Solution*) malloc(sizeof(Solution));

  initializeSolution(sol, size);

  createRandomSolution(sol);

  if( mode == 'r' ) randomSearch(sol, 1000000000, gpp);
  if( mode == 'l' ) bestFirstSearch(sol, gpp);
  if( mode == 'v' ) randomSearch(sol, 100000, gpp);

  freeGPP(gpp);
  freeSolution(sol);
  
  return EXIT_SUCCESS;
}

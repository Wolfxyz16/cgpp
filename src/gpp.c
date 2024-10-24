#include "../include/gpp.h"
#include <stdio.h>
#include <stdlib.h>

Gpp *loadGPP(char *route)
{
  FILE *file = fopen(route, "r");
  Gpp *gpp = (Gpp*) malloc(sizeof(Gpp));
  int number, length = 0;
  int i = 0, base = 10;
  int numbers[256];
  char *endptr;
  char line[256];

  if (file == NULL) {
    perror("Error leyendo el archivo");
    return NULL;
  }

  fgets(line, sizeof(line), file);

  gpp->numNodes = strtol(line, &endptr, base);
  gpp->numEdges = strtol(endptr, &endptr, base);
  gpp->conn = (Connections*) malloc(sizeof(Connections) * gpp->numNodes);

  while ( i < gpp->numNodes ) {
    length = 0;
    fgets(line, sizeof(line), file);
    char *ptr = line;

    while ( (number = strtol(ptr, &ptr, base) ) != 0) { 
      numbers[length] = number;
      length++;
    }

    gpp->conn[i].num = length;
    gpp->conn[i].connections = (int*) malloc(sizeof(int) * length);
    // copiamos lo que tenemos en numbers en conn.connections
    for( int k = 0; k < length; k++ ) gpp->conn[i].connections[k] = numbers[k];
    i++;
  }
  fclose(file);
  return gpp;
}

void freeGPP(Gpp *gpp)
{
  for( int i = 0; i < gpp->numNodes; i++ ) free(gpp->conn[i].connections);
  free(gpp->conn);
  free(gpp);
}

void printGPP(Gpp *gpp)
{
  for( int i = 0; i < gpp->numNodes; i++ )
  {
    printf("Node %d connections:% d\n", i + 1, gpp->conn[i].num);
    printConnections(&gpp->conn[i]);
  }
  printf("Numero de nodos: %d\n", gpp->numNodes);
  printf("Numero de vertices: %d\n", gpp->numEdges);
}

void printConnections(Connections *conn)
{
  for(int i = 0; i < conn->num; i++)
  {
    printf("%d  ", conn->connections[i]);
  }
  printf("\n");
}

int objectiveFunction(Gpp *gpp, bool *sol) 
{
  int i, j;
  int n = gpp->numNodes;
  int fitness = 0;

  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {

    }
  }
  return fitness;
}

#pragma once

// cada nodo tiene asociado una lista que indica cuantas y cuales conexiones tiene
typedef struct Connections {
  int num;
  int *connections;
} Connections;

typedef struct Gpp {
  int numNodes;
  int numEdges;
  Connections *conn;
} Gpp;

Gpp *loadGPP(char *route);

void freeGPP(Gpp *gpp);

void printGPP(Gpp *gpp);

void printConnections(Connections *conn);

int objectiveFunction(Gpp *gpp, bool *sol);

bool *createRandomSolution(int num);

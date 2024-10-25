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

// indica si dos nodos estan conectados en el problema dado
bool connectionExists(Connections *conn, int node2);

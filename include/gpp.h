typedef struct GPP {
  int numNodes;
  int numEdges;
  int **edges;
} GPP;

void loadGPP(GPP **gpp);

int objectiveFunction(GPP *gpp, bool *sol);

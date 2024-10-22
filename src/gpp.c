*GPP loadGPP(char *route)
{
  FILE *file = fopen(route, "r");
  char buffer[512];
  *GPP gpp = (*GPP) malloc(sizeof(GPP));
  int numNodes, numEdges;
  int i;

  if (file == NULL) {
    perror("Error leyendo el archivo");
    return;
  }

  fscanf(file, "%d", &numNodes);
  fscanf(file, "%d", &numEdges);

  gpp->numNodes = numNodes;
  gpp->numEdges = numEdges;
  gpp->edges = (**int) malloc(sizeof(*int));

  for( i = 0 ; i < numNodes; i++ )
  {
    // leemos la linea entera y lo cargamos en edges[i]
    edges[i] = 
  }
  
  for(i = 0; i < n*n; i++)
  {
    fscanf(file, "%d", &((*qap)->dis[i]));
  }

}

void freeGPP(GPP *gpp)
{
  free(gpp->numNodes);
  free(gpp->numEdges);
}

int objectiveFunction(GPP *gpp, bool *sol) 
{
  int i, j;
  int n = gpp->numNodes;
  int fitness = 0;

  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      fitness += gpp->edges[i*n+j] * sol[i] * (1 - sol[j]);
    }
  }
  return fitness;
}

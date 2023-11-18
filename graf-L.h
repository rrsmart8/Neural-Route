/*--- graf-L.h --- Graf reprezentat cu liste --*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>

#ifndef _GRAF_L_
#define _GRAF_L_

#define INF INT_MAX

typedef struct celarc 
{ 
  char* d;       /* destinatie arc */
  int c;            /* cost arc */
  struct celarc *urm;  /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct 
{ int n;     /* numar noduri */
  AArc* x;    /* vector adrese liste arce */
} TGL;

TGL* AlocG(int total_nodes);
void DistrG(TGL** ag);


AArc NewDestination(char dest[]);

void IsVisitedDestination(char **added_destinations, int *position, int total_nodes, char node[]);
void InitDestination(char **added_destinations, char node[], int adding_position);
void AddToAdjancey(TGL* graf, int adding_position, char destination[], int cost);

void EnterLastPlace(TGL* graf, int dest_pos, char node[], int cost);
void CheckIfExists(TGL* graf, int dest_pos, char node[], int cost);

void DFS(TGL* graf, int* visited, char** added_destinations, char first_node[], int total_nodes);

int FindZones(TGL* graf, char** added_destinations, int total_nodes);

int Prim(TGL* graf, char** added_destinations, int total_nodes, int* visited);

int* FindPaths(TGL* graf, char** added_destinations, int total_nodes, int zones);

int* Dijkstra(TGL* graf, int starting_node, char** added_destinations, int* depth_array, int* path, int* pathSize);

void storePath(int parent[], int node, int path[], int* pathSize);

#endif

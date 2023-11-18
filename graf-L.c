/*--- graf-L.c --- Graf implementat cu liste --*/
#include "graf-L.h"

TGL* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  TGL* g = (TGL*)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return g;
}

void DistrG(TGL** ag)
{ 
  int i;
  AArc p, aux;
  for(i = 1; i <= (*ag)->n; i++){ 
    p = (*ag)->x[i];
    while(p)
    { aux = p;
      free(aux->d); 
      p = p->urm;
      free(aux);
    }
  }
  free((*ag)->x);
  free(*ag);
  *ag = NULL;
}


AArc NewDestination(char dest[]) {

  AArc newDest = (AArc)malloc(sizeof(TCelArc));

  if (!newDest) {
    return NULL;
  }

  newDest->urm = NULL;
  newDest->d = malloc(strlen(dest)*sizeof(char));
  newDest->c = -1;

  return newDest;

}

void IsVisitedDestination(char **added_destinations, int *position, int total_nodes, char node[]) {

    for (int j = 1; j <= total_nodes; j++) {
      if (added_destinations[j] != NULL) {
      if (strcmp(added_destinations[j], node) == 0) {
          (*position) = j;
        }
      }
    }
}

void InitDestination(char **added_destinations,char node[], int adding_position) {

    added_destinations[adding_position] = malloc(strlen(node) * sizeof(char));
      if (!added_destinations[adding_position]) {
        return;
      }

      strcpy(added_destinations[adding_position], node);

}

void AddToAdjancey(TGL* graf, int adding_position, char destination[], int cost) {

      graf->x[adding_position] = NewDestination(destination);
      strcpy(graf->x[adding_position]->d, destination);
      graf->x[adding_position]->c = cost;

}

void EnterLastPlace(TGL* graf, int dest_pos, char node[], int cost) {

  AArc p = graf->x[dest_pos];
        while (p != NULL)
        {

          if (p->urm == NULL)
          {
            p->urm = NewDestination(node);
            strcpy(p->urm->d, node);
            p->urm->c = cost;
            break;
          }

          p = p->urm;
        }

}

void CheckIfExists(TGL* graf, int node_poz, char destination[], int cost) {

          AArc parse = graf->x[node_poz];
          
          while (parse != NULL) {
            if (strcmp(destination, parse->d) == 0) {
              break;
            }
            if (parse->urm == NULL) {
              parse->urm = NewDestination(destination);
              strcpy(parse->urm->d, destination);
              parse->urm->c = cost;
          break; 
            }

            parse = parse->urm;
          }

}

void DFS(TGL* graf, int* visited, char **added_destinations, char first_node[], int total_nodes) {

  int index = 0;

  IsVisitedDestination(added_destinations, &index, total_nodes, first_node);
  visited[index] = 1;

  AArc p = graf->x[index];

  while (p != NULL) {
    int dest_poz = 0;
    IsVisitedDestination(added_destinations, &dest_poz, total_nodes, p->d);
    if (visited[dest_poz] == 0) {
      DFS(graf, visited, added_destinations, p->d, total_nodes);
    } 

    p = p->urm;
  }


}

int FindZones(TGL* graf, char** added_destinations, int total_nodes) {

  int completed_zones = 0, zones = 0;

  char first_node[30];

  int *visited = calloc ((total_nodes+1), sizeof(int));
  if (!visited) {
    return -1;
  }

  do {

    int ok = 0;

    for (int i = 1; i <= total_nodes; i++) {
      if (visited[i] == 1) {
        ok++;
      }
    }

    if (ok == total_nodes) {
      completed_zones = 1;
    } else {
      zones++;

      for (int i = 1; i <= total_nodes; i++) {
      if (visited[i] == 0) {
        strcpy(first_node, added_destinations[i]);
        break;
      }
    }
      DFS(graf, visited, added_destinations, first_node, total_nodes);
      
    }

  } while(completed_zones == 0);

  free(visited);

  return zones;

}

int Prim(TGL* graf, char** added_destinations, int total_nodes, int* visited) {


      int* cost = calloc((total_nodes+1), sizeof(int));  
      if (!cost) {
        return -1;
      }

      
      for (int i = 1; i <= total_nodes; i++) {
        cost[i] = INF;
      }

    // Search for the first in vector that has the visited 0

      for (int i = 1; i <= total_nodes; i++) {
        if (visited[i] == 0) {
          cost[i] = 0;
          break;
        }
      }

      for (int i = 1; i <= total_nodes; i++) {
        int min = INF;
        int index = 0;

        for (int j = 1; j <= total_nodes; j++) {
          if (visited[j] == 0 && cost[j] < min) {
            min = cost[j];
            index = j;
          }
        }

        visited[index] = 1;

        AArc p = graf->x[index];

        while (p != NULL) {
          int visited_index = -1;
          IsVisitedDestination(added_destinations, &visited_index, total_nodes, p->d);

          if (visited[visited_index] == 0 && p->c <cost[visited_index]) {
            cost[visited_index] = p->c;
          }

          p = p->urm;
        }

      }
      int final_cost = 0;


      for (int i = 1; i <= total_nodes; i++) {
        if (cost[i] != INF) {
          final_cost += cost[i];
        }
      }

      free(cost);

      return final_cost;

}

int* FindPaths(TGL* graf, char** added_destinations, int total_nodes, int zones) {

  int* visited = calloc((total_nodes+1), sizeof(int));
  if (!visited) {
    return NULL;
  }

  int* PathCost = calloc(zones+1,sizeof(int));
  if (!PathCost) {
    return NULL;
  }

  for (int i = 1; i <= zones; i++) {
    PathCost[i] = Prim(graf, added_destinations, total_nodes, visited);
  }

  for (int i = 1; i < zones; i++) {
    for (int j = i+1; j <= zones; j++) {
        if (PathCost[i] > PathCost[j]) {
          int aux = PathCost[i];
          PathCost[i] = PathCost[j];
          PathCost[j] = aux;
        }
    }
  }

  free(visited);
  return PathCost;

}

void storePath(int parent[], int node, int path[], int* pathSize) {
    if (parent[node] == -1) {
        path[*pathSize] = node;
        (*pathSize)++;
        return;
    }

    storePath(parent, parent[node], path, pathSize);
    path[*pathSize] = node;
    (*pathSize)++;
}


int* Dijkstra(TGL* graf, int starting_node, char** added_destinations, int* depth_array, int* path, int*pathSize) {

int *cost = (int*)calloc((graf->n + 1),sizeof(int));

if (!cost) {
  return NULL;
}

int *visited = (int*)calloc((graf->n + 1), sizeof(int));

if (!visited) {
  return NULL;
}

int *parent = (int*)calloc((graf->n + 1), sizeof(int));

if (!parent) {
  return NULL;
}

float* score = (float*)calloc((graf->n + 1), sizeof(float));

for (int i = 1; i <= graf->n; i++) {
    score[i] = 999999;
    cost[i] = INF;
    visited[i] = 0;
    parent[i] = -1;
}

int node_index = -1;
 
cost[starting_node] = 0;
score[starting_node] = 0;

for (int i = 1; i <= graf->n; i++) {

float min_score = 999999;

for (int j = 1; j <= graf->n; j++) {
  if (score[j] < min_score && visited[j] == 0) {
    min_score = score[j];
    node_index = j;
  }
}

AArc p = graf->x[node_index];
visited[node_index] = 1;

while (p != NULL) {
      int dest_index = -1;
      IsVisitedDestination(added_destinations, &dest_index, graf->n, p->d);
      float score_cur = p->c / (depth_array[dest_index]*1.0);

  if (visited[dest_index] == 0 && score_cur + min_score < score[dest_index] && score[node_index] != 999999) {

    cost[dest_index] = p->c + cost[node_index];
    score[dest_index] = score_cur + min_score;
    parent[dest_index] = node_index;

  }

  p = p->urm;
}

}

    int destination = -1;
    IsVisitedDestination(added_destinations, &destination, graf->n, "Corabie");
    storePath(parent, destination, path, pathSize);

    free(score);

  return cost;

}



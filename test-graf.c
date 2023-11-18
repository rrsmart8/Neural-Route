/*--- test-graf.c ---*/
#include "graf-L.h"

int main(int argc, const char* argv[])
{

        if (atoi(argv[1]) == 1) {

        FILE *input = fopen("tema3.in", "rt");
        FILE *output = fopen("tema3.out", "w");

        int total_nodes = 0, total_paths = 0;

        /* Reading the number of nodes */

        fscanf(input, "%d", &total_nodes);
        fscanf(input, " %d", &total_paths);

        TGL *graf;

        graf = AlocG(total_nodes);

        int adding_position = 1;

        char **added_destinations = (char **)calloc((total_nodes + 1), sizeof(char *));
        if (!added_destinations)
        {
          return -1;
        }

  for (int i = 1; i <= total_paths; i++)
  {

        int cost = -1;
        char node[50], destination[50];

        fscanf(input, "%s ", node);
        fscanf(input, "%s", destination);
        fscanf(input, "%d", &cost);

        int position = -1;
        IsVisitedDestination(added_destinations, &position, total_nodes, node);

    if (position == -1) // Node source not found in the array
    {
        /* Introducing in dest array */
        InitDestination(added_destinations, node, adding_position);

        /* Introducing to the adjancey list of the graph */
        AddToAdjancey(graf, adding_position, destination, cost);

        adding_position++;

        int dest_pos = -1;
        IsVisitedDestination(added_destinations, &dest_pos, total_nodes, destination);

      if (dest_pos == -1) // Destination node not found in array either
      {
        /* Introducing in dest array */
        InitDestination(added_destinations, destination, adding_position);

         /* Introducing to the adjancey list of the graph */
        AddToAdjancey(graf, adding_position, node, cost);

        adding_position++;

      } else {  
      
        /* Add a certain node to the end of an adj list */
        EnterLastPlace(graf, dest_pos, node, cost);

        int node_poz = -1;
        IsVisitedDestination(added_destinations, &node_poz, total_nodes, node);

      if (node_poz != -1) {

        /* Add only If a certain node doesn't exists in a adj list */
        CheckIfExists(graf, node_poz, destination, cost);

      } else {

        /* Introducing in dest array */
        InitDestination(added_destinations, node, adding_position);

        /* Introducing to the adjancey list of the graph */
        AddToAdjancey(graf, adding_position, destination, cost);

        adding_position++;

          }
      }
    } else { // Node source found entering the destination

        /* Add a certain node to the end of an adj list */
        EnterLastPlace(graf, position, destination, cost);

        int remain_poz = -1;
        IsVisitedDestination(added_destinations, &remain_poz, total_nodes, destination);

    if (remain_poz != -1) { // Node found, destination not found (continue adding the dest)
      
        /* If the node doesn't exists in adj list of the destination */
        CheckIfExists(graf, remain_poz, node, cost);

    } else {

        /* Introducing in dest array */
        InitDestination(added_destinations, destination, adding_position);

        /* Introducing to the adjancey list of the graph */
        AddToAdjancey(graf, adding_position, node, cost);
        adding_position++;

      }

    }

  }

        for(int i = 0; i < total_nodes; i++)
        {
            printf("%s: ", added_destinations[i]);

            AArc aux = graf->x[i];

            while(aux)
            {
                printf("%s ", aux->d);
                aux = aux->urm;
            }
            printf("\n");
        }

        int zone = 0;

        zone = FindZones(graf, added_destinations, total_nodes);

        int *paths = calloc(zone+1, sizeof(int));

        paths = FindPaths(graf, added_destinations, total_nodes, zone);

        fprintf(output, "%d\n", zone);
        for (int i = 1; i <= zone; i++) {
          fprintf(output, "%d\n", paths[i]);
        }


        for (int i = 0; i < total_nodes+1; i++) {
          free(added_destinations[i]);
        }
        free(added_destinations);
        free(paths);
        DistrG(&graf);
        fclose(input);
        fclose(output);

  } if (atoi(argv[1]) == 2) {

        FILE *input = fopen("tema3.in", "rt");
        FILE *output = fopen("tema3.out", "w");


        int safe_zones = 0, arce = 0;
        unsigned int greutate_comoara = 0;

        fscanf(input, "%d", &safe_zones);
        fscanf(input, " %d", &arce);

        TGL *graf;

        graf = AlocG(safe_zones);
        graf->n = safe_zones;

        int adding_position = 1;

        char **added_destinations = (char **)calloc((safe_zones + 1), sizeof(char *));
        if (!added_destinations)
        {
          return -1;
        }


        for (int i = 1; i <= arce; i++) { // Reading the arces

            char node[50], destination[50];
            int cost = -1;

            fscanf(input, "%s ", node);
            fscanf(input, "%s", destination);
            fscanf(input, "%d", &cost);

            int position = -1;
            IsVisitedDestination(added_destinations, &position, safe_zones, node);

            if (position == -1) {

                InitDestination(added_destinations, node, adding_position); 
                AddToAdjancey(graf, adding_position, destination, cost);
                adding_position++;

                int dest_pos = -1;
                IsVisitedDestination(added_destinations, &dest_pos, safe_zones, destination);

                if (dest_pos == -1) {
                  InitDestination(added_destinations, destination, adding_position);
                  adding_position++;
                }

            } else {
              
        if (graf->x[position] == NULL) {
          graf->x[position] = NewDestination(destination);
          strcpy(graf->x[position]->d, destination);
          graf->x[position]->c = cost;

        } else {
          EnterLastPlace(graf, position, destination, cost);

        }
               int remain_pos = -1;
              IsVisitedDestination(added_destinations, &remain_pos, safe_zones, destination);

              if (remain_pos == -1) {
                InitDestination(added_destinations, destination, adding_position);
                adding_position++;
              }

            }


        }

        int* depth_array = calloc((safe_zones+1), sizeof(unsigned int));
        if (!depth_array) {
          return -1;
        }

        for (int i = 1; i <= safe_zones; i++) {
          char island[50];
          unsigned int adancime = 0;

          fscanf(input, "%s ", island);
          fscanf(input, "%d", &adancime);

          int island_index = 0;
          IsVisitedDestination(added_destinations, &island_index, safe_zones, island);

          depth_array[island_index] = adancime;

        }

        fscanf(input, "%u", &greutate_comoara);

        int starting_node = -1;
        IsVisitedDestination(added_destinations, &starting_node, safe_zones, "Insula");

        int ending_point =1;
        IsVisitedDestination(added_destinations, &ending_point, safe_zones, "Corabie");


        int* visited = calloc((safe_zones + 1), sizeof(int));
        if (!visited) {
          return -1;
        }
        int ok = 0;
        DFS(graf, visited, added_destinations, "Insula", safe_zones);
        if (visited[ending_point] == 0 && visited[starting_node] == 1) {
          ok = 1;
          fprintf(output, "Echipajul nu poate transporta comoara inapoi la corabie\n");
        } else {
          for (int k = 1; k <=safe_zones; k++) {
            visited[k] = 0;
          }
          DFS(graf, visited, added_destinations, "Corabie", safe_zones);
          if (visited[starting_node] == 0 && visited[ending_point] == 1) {
            ok = 1;
            fprintf(output, "Echipajul nu poate ajunge la insula\n");
          }
        }
        if (ok == 0) {

        int* path = (int*)calloc((graf->n + 2), sizeof(int));
        if (!path) {
        return -1;
          }

        int pathSize = 0;
        int* cost = Dijkstra(graf, starting_node, added_destinations, depth_array, path, &pathSize);

        // int* cost_arce = DijkstraDrum(graf, starting_node, added_destinations);

        int total_weight = 999999;
        for (int i = 0; i < pathSize; i++) {
            if (depth_array[path[i]] < total_weight && depth_array[path[i]] != 1) {
              total_weight = depth_array[path[i]];
            }
        }

        for (int i = 0; i < pathSize; ++i) {
        fprintf(output, "%s ", added_destinations[path[i]]); // linie 1
    }
        fprintf(output, "\n");

        fprintf(output, "%d\n", cost[ending_point]); // linie 2
        
        fprintf(output, "%d\n", total_weight); // linie 3

        fprintf(output, "%d\n", greutate_comoara/total_weight); // linie 4
        }

      for (int i = 1; i <= safe_zones+1; i++) {
          free(added_destinations[i]);
        }
        free(added_destinations);
        free(visited);
      DistrG(&graf);
      fclose(input);
      fclose(output);
  }


  return 0;
}

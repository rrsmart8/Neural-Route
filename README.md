# Neural-Route


# Overview

The program is designed to perform graph operations on two different types of graphs based on the value of the command-line argument argv[1].

Graph Type 1 (argv[1] == 1): Construct a graph with directed edges and calculate zones and paths.

Graph Type 2 (argv[1] == 2): Construct a graph with weighted edges, calculate paths using Dijkstra's algorithm, and provide information about a treasure transport scenario.


# File Structure

graf-L.h: Header file containing function declarations and structure definitions for graph operations.
graf-L.c: Source file containing the implementation of graph operations.
test-graf.c: Main program file that reads input data, performs graph operations, and generates output.


# Functions and Operations

The program performs various graph operations, including:

Graph Construction: Reads input data to construct a graph with specified nodes, edges, and costs.

Zone Calculation (argv[1] == 1): Finds zones in the graph and calculates the number of paths within each zone.

Dijkstra's Algorithm (argv[1] == 2): Calculates the shortest paths in a graph with weighted edges.

Treasure Transport Scenario (argv[1] == 2): Simulates a scenario involving transporting a treasure between two nodes, considering depth constraints.


# Building and Running

To build and run the program:

Compile the source files:

gcc -o test-graf graf-L.c test-graf.c -Wall

(Or you can use directly "make" command)

Run the compiled program with a command-line argument:

./test-graf 1   # For Graph Type 1
./test-graf 2   # For Graph Type 2


# Input Format

The program reads input data from a file named "tema3.in". The input format depends on the graph type:

Graph Type 1 (argv[1] == 1):

First line: Total number of nodes (total_nodes) and total number of paths (total_paths).
Subsequent lines: Information about paths, including source node, destination node, and cost.

Graph Type 2 (argv[1] == 2):

First line: Total number of safe zones (safe_zones) and total number of edges (arce).
Subsequent lines: Information about edges, including source node, destination node, and cost.

Lines after edges: Information about depth of each island.
Last line: Weight of the treasure (greutate_comoara).


# Output Format

The program generates output in a file named "tema3.out". The output format includes information based on the graph type and operations performed:

Graph Type 1 (argv[1] == 1):

First section: Adjacency list representation of the constructed graph.
Second section: Number of zones and the number of paths within each zone.

Graph Type 2 (argv[1] == 2):

Depending on the scenario:
Information about the nodes visited during a DFS traversal.
Shortest paths and related information using Dijkstra's algorithm.
Details about the treasure transport scenario.

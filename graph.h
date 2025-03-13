#ifndef GRAPH_H
#define GRAPH_H

bool **make_graph(int nodes, char *response, bool isDirected);
int nodes_count(char *response);
void print_graph(bool **graph, int nodes);
void print_graph(bool **graph, int nodes);
bool** generate_directed_graph_randomly(int nodes);
bool** generate_undirected_graph_randomly(int nodes);
bool** generate_graph_from_user(int nodes, bool is_directed);
void free_graph(bool **graph, int nodes);

#endif
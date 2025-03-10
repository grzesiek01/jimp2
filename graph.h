#ifndef GRAPH_H
#define GRAPH_H

bool **make_graph(int vertex_n, char *response);
int vertex_count(char *response);
void print_graph(bool **connections, int vertex_n);

#endif
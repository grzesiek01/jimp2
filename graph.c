#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

bool **make_graph(int nodes, char *response, bool isDirected) {
    
    if (nodes <= 0) {
        printf("Błąd: Niepoprawna liczba wierzchołków (%d)\n", nodes);
        return NULL;
    }
    if (!response) {
        printf("Błąd: Pusta odpowiedź!\n");
        return NULL;
    }

    bool **graph;
    int from, to;
    char *ptr = response;
    graph = malloc(nodes * sizeof(bool*));
    for(int i = 0; i < nodes; i++) {
        graph[i] = calloc(nodes, sizeof(bool));
    }

    while (*ptr && !isdigit(*ptr)) ptr++;

    while(*ptr){
        if (sscanf(ptr, "%d - %d", &from, &to) == 2) {
            if (from >= 0 && from < nodes && to >= 0 && to < nodes) {
                graph[from][to] = true;
                if(isDirected) {
                    graph[to][from] = true;
                }
            } else {
                printf("Błąd: indeksy poza zakresem (%d, %d)\n", from, to);
            }
        }
        if(ptr) {
            ptr++;
        }else{
            break;
        }
    }

    return graph;
}

int nodes_count(char *response) {
    int maxNumber = 0;
    int a, b;
    char *ptr = response;

    while (*ptr) {
        if (sscanf(ptr, "%d - %d", &a, &b) == 2) {
            if(a > maxNumber) {
                maxNumber = a;
            }
            if(b > maxNumber) {
                maxNumber = b;
            }
        }
        ptr = strchr(ptr, '\n');
        if(ptr) { 
            ptr++;
        }else{
            break;
        }
    }
    maxNumber++;
    return maxNumber;
}

bool** generate_directed_graph_randomly(int nodes){ //Losowe generowanie grafu skierowanego
    bool** graph_structure = malloc(sizeof(bool*)*nodes); //tablica polaczen reprezentujaca strukture grafu
    for(int i = 0; i < nodes; i++){//pusty graf
        graph_structure[i] = malloc(sizeof(bool)*nodes);
        for(int j = 0; j < nodes; j++){
            graph_structure[i][j] = 0;
        }
    }
    srand(time(NULL));
    int edges = rand() % ((nodes*(nodes-1))/2) + ((nodes*(nodes-1))/2);//zmienna oznaczjaca ilosc potencjalnych krawedzi w grafie
    for(int i = 0; i < edges; i++){
        int edge_start = rand() % nodes;
        int edge_end = rand() % nodes;
        if(edge_start != edge_end && graph_structure[edge_start][edge_end] != 1){
            graph_structure[edge_start][edge_end] = 1;
        }
    }
    return graph_structure;
}

bool** generate_undirected_graph_randomly(int nodes){
    bool** graph_structure = malloc(sizeof(bool*)*nodes); //tablica polaczen reprezentujaca strukture grafu
    for(int i = 0; i < nodes; i++){//pusty graf
        graph_structure[i] = malloc(sizeof(bool)*nodes);
        for(int j = 0; j < nodes; j++){
            graph_structure[i][j] = 0;
        }
    }
    srand(time(NULL));
    int edges;
    if(nodes % 4 == 0 || (nodes-1) % 4 == 0){
        edges = rand() % ((nodes*(nodes-1))/4) + ((nodes*(nodes-1))/4);//zmienna oznaczjaca ilosc potencjalnych krawedzi w grafie
    }
    else{
        edges = rand() % ((nodes*(nodes-1))/4) + ((nodes*(nodes-1))/4)+1;//zmienna oznaczjaca ilosc potencjalnych krawedzi w grafie
    }
    for(int i = 0; i < edges; i++){
        int edge_start = rand() % nodes;
        int edge_end = rand() % nodes;
        if(edge_start != edge_end && graph_structure[edge_start][edge_end] != 1 && graph_structure[edge_end][edge_start] != 1){
            graph_structure[edge_start][edge_end] = 1;
            graph_structure[edge_end][edge_start] = 1;
        }
    }
    return graph_structure;
}

void print_graph(bool **graph, int nodes) {
    printf("   ");
    for(int i = 0; i < nodes; i++) {
        printf(" %2d", i);
    }
    printf("\n");
    for(int i = 0; i < nodes; i++) {
        printf("%2d [", i);
        for(int j = 0; j < nodes; j++) {
            printf("%2d ", graph[i][j]);
        }
        printf("]\n");
    }
}

void free_graph(bool **graph, int nodes) {
    for(int i = 0; i < nodes; i++) {
        free(graph[i]);
    }
    free(graph);
}

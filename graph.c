#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool **make_graph(int vertex_n, char *response) {
    
    if (vertex_n <= 0) {
        printf("Błąd: Niepoprawna liczba wierzchołków (%d)\n", vertex_n);
        return NULL;
    }
    if (!response) {
        printf("Błąd: Pusta odpowiedź!\n");
        return NULL;
    }

    bool **connections;
    int from, to;
    char *ptr = response;
    connections = malloc(vertex_n * sizeof(bool*));
    for(int i = 0; i < vertex_n; i++) {
        connections[i] = calloc(vertex_n, sizeof(bool));
    }

    while (*ptr && !isdigit(*ptr)) ptr++;

    while(*ptr){
        if (sscanf(ptr, "%d - %d", &from, &to) == 2) {
            if (from >= 0 && from < vertex_n && to >= 0 && to < vertex_n) {
                connections[from][to] = true;
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

    return connections;
}

int vertex_count(char *response) {
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

void print_graph(bool **connections, int vertex_n) {
    printf("   ");
    for(int i = 0; i < vertex_n; i++) {
        printf(" %2d", i);
    }
    printf("\n");
    for(int i = 0; i < vertex_n; i++) {
        printf("%2d [", i);
        for(int j = 0; j < vertex_n; j++) {
            printf("%2d ", connections[i][j]);
        }
        printf("]\n");
    }
}

void free_graph(bool **connections, int vertex_n) {
    for(int i = 0; i < vertex_n; i++) {
        free(connections[i]);
    }
    free(connections);
}

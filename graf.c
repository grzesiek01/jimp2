#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct connection{ //moj pomysl na strukture grafu jest taki, zeby tworzyc tablice polaczen w grafie
    int start;//wierzcolek z ktorego wychodzi krawedz
    int end;//wierzcholek w ktorym konczy sie krawedz
    int is_connection;//ewentualnie mozemy dodac pole "is connection" i wtedy tworzyc tablice dwuwymiarowa gdzie beda wszystkie mozliwe polaczenia z A do B i to pole oznaczalo by czy jest polaczenie czy go nie ma 
}connection;

connection** generate_directed_graph_randomly(int nodes){ //Losowe generowanie grafu skierowanego
    connection** graph_structure = malloc(sizeof(connection)*nodes); //tablica polaczen reprezentujaca strukture grafu
    for(int i = 0; i < nodes; i++){//pusty graf
        graph_structure[i] = malloc(sizeof(connection)*nodes);
        for(int j = 0; j < nodes; j++){
            graph_structure[i][j].start = i;
            graph_structure[i][j].end = j;
            graph_structure[i][j].is_connection = 0;
        }
    }
    srand(time(NULL));
    int edges = rand() % ((nodes*(nodes-1))/2) + ((nodes*(nodes-1))/2);//zmienna oznaczjaca ilosc potencjalnych krawedzi w grafie
    for(int i = 0; i < edges; i++){
        int edge_start = rand() % nodes;
        int edge_end = rand() % nodes;
        if(edge_start != edge_end && graph_structure[edge_start][edge_end].is_connection != 1){
            graph_structure[edge_start][edge_end].is_connection = 1;
        }
    }
    return graph_structure;
}

connection** generate_undirected_graph_randomly(int nodes){
    connection** graph_structure = malloc(sizeof(connection)*nodes); //tablica polaczen reprezentujaca strukture grafu
    for(int i = 0; i < nodes; i++){//pusty graf
        graph_structure[i] = malloc(sizeof(connection)*nodes);
        for(int j = 0; j < nodes; j++){
            graph_structure[i][j].start = i;
            graph_structure[i][j].end = j;
            graph_structure[i][j].is_connection = 0;
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
        if(edge_start != edge_end && graph_structure[edge_start][edge_end].is_connection != 1 && graph_structure[edge_end][edge_start].is_connection != 1){
            graph_structure[edge_start][edge_end].is_connection = 1;
            graph_structure[edge_end][edge_start].is_connection = 1;
        }
    }
    return graph_structure;
}

void write_graph(connection** graph, int nodes){
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            printf("[%d]",graph[i][j].is_connection);
        }
        printf("\n");
    }
}

connection**  generate_graph_via_chat(){
    //Tu nie mam pojecia co powinno sie zadziac
}


int main(int argc, char** argv){
    char input1;//zmienna odpowiadajaca za wybor komunikacji urzytkownika z komputerem
    int flag1 = 0;//flaga, ktora zmieniamy dopiero wtedy gdy uzytkownik poda dobry input1
    char input2[3];//zmienna odpowiadajaca za przechowanie odpowiedzi urzytkownika co do ilosci wierzcholkow
    int flag2 = 0;//flaga, ktora zmieniamy dopiero wtedy gdy uzytkownik poda dobry input2
    char input3;//zmienna odpowiadajaca za wybor czy graf ma byc skierowany czy nie
    int flag3 = 0;//flaga, ktora zmieniamy dopiero wtedy gdy uzytkownik poda dobry input3
    int nodes;//zmienna przechowujaca ilosc wierzcholkow
    connection** graph;
    while(flag1 == 0){
        printf("How would you like to tell, how to generate graph?\n1. Tell how many nodes should be in graph\n2. Tell chat to generate graph\n");
        scanf(" %c",&input1);
        if(input1 == '1'){
            while(flag2 == 0){
                printf("How many nodes should be in graph?\n");
                scanf("%s",&input2);
                if(atoi(input2)>1){
                    nodes = atoi(input2);
                    flag2 = 1;
                }
                else{
                    printf("Wrong input\n");
                }
            }
            while(flag3 == 0){
                printf("Should the graph be directed?\n1. Yes\n2. No\n");
                scanf(" %c",&input3);
                if(input3 == '1'){
                    graph = generate_directed_graph_randomly(nodes);
                    flag1 = 1;
                    flag3 = 1;
                }
                else if(input3 == '2'){
                    graph = generate_undirected_graph_randomly(nodes);
                    flag1 = 1;
                    flag3 = 1;
                }
                else{
                    printf("Wrong input\n");
                }
            }            
        }
        else if(input1 == '2'){
            graph = generate_graph_via_chat();
            flag1 = 1;
        }
        else{
            printf("Wrong input\n");
        }
    }
    write_graph(graph,nodes);
    return 0;
}

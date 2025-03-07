#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool** generate_graph_randomly(int nodes){
    bool** graph_structure = malloc(sizeof(bool)*nodes); //tablica polaczen reprezentujaca strukture grafu
    //Losowe generowanie grafu
    return graph_structure;
}
bool**  generate_graph_via_chat(){
    //Tu nie mam pojecia co powinno sie zadziac
}


int main(int argc, char** argv){
    bool **connections;
    int input1;//zmienna odpowiadajaca za wybor komunikacji urzytkownika z komputerem
    printf("How would you like to tell, how to generate graph?\n1. Tell how many nodes should be in graph\n2. Tell chat to generate graph");
    gets(input1);

    //Tu trzeba napisac sprawdzanie input1

    if(input1 == 1){
        int nodes;//zmienna przechowujaca ilosc wierzcholkow
        //Tu trzeba napisac pytanie o ilosc wierzcholkow
        generate_graph_randomly(nodes);
    }
    else if(input1 == 2){
        generate_graph_via_chat();
    }
    return 0;
}

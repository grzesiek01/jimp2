#include <stdio.h>
#include <stdlib.h>

typedef struct connection{ //moj pomysl na strukture grafu jest taki, zeby tworzyc tablice polaczen w grafie
    int start;//wierzcolek z ktorego wychodzi krawedz
    int end;//wierzcholek w ktorym konczy sie krawedz
    int is_connection;//ewentualnie mozemy dodac pole "is connection" i wtedy tworzyc tablice dwuwymiarowa gdzie beda wszystkie mozliwe polaczenia z A do B i to pole oznaczalo by czy jest polaczenie czy go nie ma 
}connection;

connection** generate_graph_randomly(int nodes){
    connection** graph_structure = malloc(sizeof(connection)*nodes); //tablica polaczen reprezentujaca strukture grafu
    //Losowe generowanie grafu
    return graph_structure;
}
connection**  generate_graph_via_chat(){
    //Tu nie mam pojecia co powinno sie zadziac
}


int main(int argc, char** argv){
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

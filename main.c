#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "http_request.h"
#include "graph.h"

/*bool** generate_graph_randomly(int nodes){
    bool** graph_structure = malloc(sizeof(bool)*nodes); //tablica polaczen reprezentujaca strukture grafu
    //Losowe generowanie grafu
    return graph_structure;
}
bool**  generate_graph_via_chat(){
    //Tu nie mam pojecia co powinno sie zadziac
}*/


int main() {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    char userQuestion[MAX_MSG_LEN];
    const char *host;
    int port;
    int choice;

    while(1) {
        printf("Podaj gdzie postawiony jest model ai:\n[1] LM Studio\n[2]Ollama\n> ");
        if (scanf("%d", &choice) != 1) {
            printf("Błąd! Podaj poprawny numer.\n");
            while (getchar() != '\n');
            continue;
        }
        
        while (getchar() != '\n');

        if(choice == 1) {
            host = "localhost";
            port = 1234;
            break;
        }else if(choice == 2) {
            host = "127.0.0.1";
            port = 11434;
            break;
        }else{
            printf("Błąd! Niepoprawny wybór, wybierz 1 lub 2!\n");
        }
    }

    printf("Zadaj pytanie (wpisz 'exit' aby zakończyć):\n");

    while (1) {
        // Pobieranie pytania od użytkownika
        printf("> ");
        fgets(userQuestion, sizeof(userQuestion), stdin);
        
        // Usuwamy nową linię na końcu (jeśli jest)
        userQuestion[strcspn(userQuestion, "\n")] = 0;

        // Jeśli użytkownik wpisał 'exit', kończymy program
        if (strcmp(userQuestion, "exit") == 0) {
            break;
        }

        char postData[8192];
    
        // Dodaj pytanie do historii rozmowy
        addToHistory(userQuestion);
    
        // Zbuduj JSON-a uwzględniającego całą historię rozmowy
        buildJsonPayload(postData, sizeof(postData), userQuestion);
        printf("Wysyłanie żądania HTTP POST z danymi JSON...\n\n");
        char *response = SendHttpPostRequest(host, port, postData);
        int vertex_n = vertex_count(response);
        if(vertex_n > 1) {
            printf("Graf:\n");
            bool **connections = make_graph(vertex_n, response);
            print_graph(connections, vertex_n);
            free(connections);
        }else{
            printf("Błąd! Zbyt mało wierzchołków, aby stworzyć graf!\n");
        }
    }
    return 0;
}


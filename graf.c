#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "http_request.h"

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
    const char* url = "http://localhost:1234/v1/chat/completions";  // Adres lokalnego serwera AI
    char userQuestion[MAX_MSG_LEN];

    printf("Zadaj pytanie (wpisz 'exit' aby zakonczyc):\n");

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
        printf("Wysylanie zadania HTTP POST z danymi JSON...\n\n");
        SendHttpPostRequest(url, postData);
        
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "http_request.h"
#include "graph.h"

int main(int argc, char** argv){
    setlocale(LC_ALL, "pl_PL.UTF-8");
    char input1;//zmienna odpowiadajaca za wybor komunikacji urzytkownika z komputerem
    int flag1 = 0;//flaga, ktora zmieniamy dopiero wtedy gdy uzytkownik poda dobry input1
    char input2[3];//zmienna odpowiadajaca za przechowanie odpowiedzi urzytkownika co do ilosci wierzcholkow
    int flag2 = 0;//flaga, ktora zmieniamy dopiero wtedy gdy uzytkownik poda dobry input2
    char input3;//zmienna odpowiadajaca za wybor czy graf ma byc skierowany czy nie
    int flag3 = 0;//flaga, ktora zmieniamy dopiero wtedy gdy uzytkownik poda dobry input3
    int nodes;//zmienna przechowujaca ilosc wierzcholkow
    bool** graph;


    while(flag1 == 0){
        printf("W jaki sposób graf ma zostać wygenerowany?\n[1] Graf wygenerowany losowo przez program\n[2] Graf wygenerowany przez model AI\n");
        scanf(" %c",&input1);
        if(input1 == '1'){
            while(flag2 == 0){
                printf("Ile wierzchołków ma zawierać graf?\n");
                scanf("%s",&input2);
                if(atoi(input2)>1){
                    nodes = atoi(input2);
                    flag2 = 1;
                }
                else{
                    printf("Wprowadź poprawną liczbę wierzchołków!\n");
                }
            }
            while(flag3 == 0){
                printf("Czy graf ma być skierowany?\n[1] Tak\n[2] Nie\n> ");
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
                    printf("Niepoprawna odpowiedź! Wybierz [1] lub [2]\n");
                }
            }            
        }
        else if(input1 == '2'){
            flag1 = 1;
            char userQuestion[MAX_MSG_LEN];
            const char *host;
            int port;
            int choice;
            bool isDirected;
            char ai_model[50];

            while(1) {
                printf("Podaj gdzie postawiony jest model ai:\n[1] LM Studio\n[2] Ollama\n> ");
                if (scanf("%d", &choice) != 1) {
                    printf("Niepoprawna odpowiedź! Wybierz [1] lub [2]\n");
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
                    printf("Niepoprawna odpowiedź! Wybierz [1] lub [2]\n");
                }
            }

            printf("Podaj model AI, z którego korzystasz: ");
            scanf("%49s", ai_model);
            getchar();

            printf("Zadaj pytanie:\n");

            // Pobieranie pytania od użytkownika
            printf("> ");
            fgets(userQuestion, sizeof(userQuestion), stdin);
                
            // Usuwamy nową linię na końcu (jeśli jest)
            userQuestion[strcspn(userQuestion, "\n")] = 0;

            char postData[8192];
            
            // Dodaj pytanie do historii rozmowy
            addToHistory(userQuestion);
            
            // Zbuduj JSON-a uwzględniającego całą historię rozmowy
            buildJsonPayload(postData, sizeof(postData), userQuestion, ai_model);
            printf("Wysyłanie żądania HTTP POST z danymi JSON...\n\n");
            char *response = SendHttpPostRequest(host, port, postData);
            nodes = nodes_count(response);

            if(nodes > 1) {
                while(1){
                    printf("Czy graf ma być skierowany?\n[1] Tak\n[2] Nie\n> ");
                    scanf("%d", &choice);
                    if(choice == 1) {
                        isDirected = true;
                        break;
                    }else if(choice == 2){
                        isDirected = false;
                        break;
                    }else{
                        printf("Niepoprawna odpowiedź! Wybierz [1] lub [2]");
                    }
                }
                graph = make_graph(nodes, response, isDirected);
            }else{
                printf("Błąd! Zbyt mało wierzchołków, aby stworzyć graf!\n");
                return 1;
            }
        }else{
            printf("Niepoprawna odpowiedź! Wybierz [1] lub [2]\n");
        }
    }
    printf("Graf:\n");
    print_graph(graph, nodes);
    free_graph(graph, nodes);
    return 0;
}



#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include "graph.h"

#pragma comment(lib, "wininet.lib")

#define HISTORY_LEN 10   // Maksymalna liczba przechowywanych wiadomości
#define MAX_MSG_LEN 4096  // Maksymalna długość pojedynczej wiadomości

char history[HISTORY_LEN][MAX_MSG_LEN]; // Historia rozmowy
int historyCount = 0;  // Licznik przechowywanych wiadomości

void replaceNewlines(char* response) {
    char* pos;
    while ((pos = strstr(response, "\\n")) != NULL) {
        *pos = '\n';  // Zamienia "\n" na faktyczny znak nowej linii
        memmove(pos + 1, pos + 2, strlen(pos + 2) + 1);  // Przesuwa resztę ciągu
    }
}

// Dodaje wiadomość do historii, przesuwając starsze wiadomości
void addToHistory(const char* content) {
    if (historyCount >= HISTORY_LEN) {
        // Jeśli przekroczyliśmy limit, usuwamy najstarszą wiadomość
        for (int i = 1; i < HISTORY_LEN; i++) {
            strncpy(history[i - 1], history[i], sizeof(history[i]));
        }
        historyCount--;
    }
    
    // Dodajemy nową wiadomość na koniec
    strncpy(history[historyCount], content, sizeof(history[historyCount]) - 1);
    historyCount++;
}

// Tworzy JSON z pełnym kontekstem rozmowy
void buildJsonPayload(char* postData, size_t size, const char* lastQuestion, char *ai_model) {
    snprintf(postData, size, "{\n    \"model\": \"%s\",\n    \"messages\": [\n", ai_model);


    // Podsumowanie historii rozmowy
    strncat(postData, "        {\"role\": \"system\", \"content\": \"Answer as short as you can. If asked to create a graph, provide the random graph's connections in the following format: \\\"vertex_from - vertex_to\\\". Number vertices from 0. Make many connections. Multiple connections allowed from single vertex. At least one connection to each vertex. Mix connections. They don't have to be ascending. The user may ask for graphs with any number of vertices. Connections do not have to form cycle.\\nContext of the conversation:\\n", size - strlen(postData) - 1);

    // Dodajemy historię rozmowy jako tekst w "system"
    for (int i = 0; i < historyCount; i++) {
        snprintf(postData + strlen(postData), size - strlen(postData),
                 "user: %s\\n",
                 history[i]);
    }

    // Zamykamy historię
    strncat(postData, "\"},\n", size - strlen(postData) - 1);

    // Dodajemy ostatnie pytanie użytkownika jako normalną wiadomość
    snprintf(postData + strlen(postData), size - strlen(postData),
             "        {\"role\": \"user\", \"content\": \"%s\"}\n",
             lastQuestion);

    strncat(postData, "    ],\n    \"temperature\": 0.7\n}", size - strlen(postData) - 1);
}



// Funkcja do wysyłania żądania HTTP POST z danymi JSON
char *SendHttpPostRequest(const char *host, int port, const char* postData) {
    HINTERNET hInternet, hConnect;
    HINTERNET hRequest;
    DWORD bytesRead;
    char buffer[4096];
    BOOL bResult;
    
    // Inicjalizowanie WinINet
    hInternet = InternetOpenA("HTTP Client", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        printf("Błąd podczas otwierania połączenia z Internetem: %ld\n", GetLastError());
        EXIT_FAILURE;
    }

    DWORD timeout = 240000;  // Czas oczekiwania ustawiony na 4 min
    InternetSetOptionA(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));
    InternetSetOptionA(hInternet, INTERNET_OPTION_SEND_TIMEOUT, &timeout, sizeof(timeout));
    InternetSetOptionA(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));

    // Tworzenie połączenia z serwerem
    hConnect = InternetConnectA(hInternet, host, port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (hConnect == NULL) {
        printf("Błąd podczas łączenia sie z serwerem: %ld\n", GetLastError());
        InternetCloseHandle(hInternet);
        EXIT_FAILURE;
    }

    // Tworzenie żądania HTTP POST na URL /v1/chat/completions
    hRequest = HttpOpenRequestA(hConnect, "POST", "/v1/chat/completions", NULL, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
    if (hRequest == NULL) {
        printf("Błąd podczas otwierania zadania POST: %ld\n", GetLastError());
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        EXIT_FAILURE;
    }

    // Dodanie nagłówków
    const char* headers = "Content-Type: application/json\r\n";
    bResult = HttpAddRequestHeadersA(hRequest, headers, -1, HTTP_ADDREQ_FLAG_ADD);
    if (!bResult) {
        printf("Błąd podczas dodawania nagłówków: %ld\n", GetLastError());
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        EXIT_FAILURE;
    }

    // Wysłanie żądania HTTP POST z danymi JSON
    bResult = HttpSendRequestA(hRequest, NULL, 0, (LPVOID)postData, strlen(postData));
    if (!bResult) {
        printf("Blad podczas wysyłania zadania: %ld\n", GetLastError());
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        EXIT_FAILURE;
    }

    char *response;

    // Odczyt odpowiedzi z serwera
    while (1) {
        bResult = InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead);
        if (!bResult || bytesRead == 0) {
            break;
        }
        buffer[bytesRead] = '\0';  // Null-terminate the buffer
        response = strstr(buffer, "\"content\":");
        response += 12;
        char *response_end = strchr(response, '\"');
        *response_end = '\0';
        replaceNewlines(response);
    }

    // Czyszczenie
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return response;
}



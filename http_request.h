#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#pragma comment(lib, "wininet.lib")

#define HISTORY_LEN 10   // Maksymalna liczba przechowywanych wiadomości
#define MAX_MSG_LEN 4096  // Maksymalna długość pojedynczej wiadomości

void replaceNewlines(char* response);
void addToHistory(const char* content);
void buildJsonPayload(char* postData, size_t size, const char* lastQuestion);
char *SendHttpPostRequest(const char *host, int port, const char* postData);


#endif
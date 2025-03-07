#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#pragma comment(lib, "wininet.lib")

#define HISTORY_LEN 10   // Maksymalna liczba przechowywanych wiadomości
#define MAX_MSG_LEN 4096  // Maksymalna długość pojedynczej wiadomości

void replaceNewlines(char* response);
void addToHistory(const char* content);
void buildJsonPayload(char* postData, size_t size, const char* lastQuestion);
void SendHttpPostRequest(const char* url, const char* postData);


#endif
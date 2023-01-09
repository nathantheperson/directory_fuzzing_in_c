#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

char buffer[MAX_LINE];
char filename[FILENAME_SIZE];
int file_size;
char ip[100];

int iterates_file(char *host, in_port_t port, char *wordlist,
                  int request_delay);
int pulls_string(FILE *pfile, int read_line, char *wordlist);
int hello_socket(char *host, in_port_t port);
char *name_resolution(char *hostname);
int count_char(char *s, char c);

int main(int argc, char *argv[]) {

  if (argc != 5) {
    fprintf(stderr,
            "Usage: %s <hostname> <port> <path/to/wordlist> <request delay in "
            "seconds>\n",
            argv[0]);
    return 1;
  }

  int count_periods = count_char(argv[1], '.');

  if (count_periods < 3) {
    char *hostname = name_resolution(argv[1]);
    argv[1] = ip;
    iterates_file(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
  }

  else {
    iterates_file(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
  }

  return 0;
}

char *name_resolution(char *hostname) {

  struct hostent *he;
  struct in_addr **addr_list;
  int i;

  if ((he = gethostbyname(hostname)) == NULL) {
    herror("gethostbyname");
  }

  addr_list = (struct in_addr **)he->h_addr_list;

  for (i = 0; addr_list[i] != NULL; i++) {
    strcpy(ip, inet_ntoa(*addr_list[i]));
  }

  return (ip);
}

int count_char(char *s, char c) {
  int length = strlen(s);
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (s[i] == c)
      count++;
  }
  return count;
}

int hello_socket(char *host, in_port_t port) {

  struct sockaddr_in server;
  int socket_call;
  char server_reply[MAX_LINE * 2];

  socket_call = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_call == -1) {
    printf("socket returned -1. socket() failed\n\n");
  }

  server.sin_addr.s_addr = inet_addr(host);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (connect(socket_call, (struct sockaddr *)&server, sizeof(server)) < 0) {
    puts("\n\nconnect error\n\n");
    return 1;
  }

  // if you want to use a word list with / before the words, change   char
  // get[MAX_LINE * 2] = "GET /";    to    char get[MAX_LINE * 2] = "GET ";
  char get[MAX_LINE * 2] = "GET /";
  char *cat1 = strcat(get, buffer);
  char request_type[] = " HTTP/1.1\r\n";
  char *cat2 = strcat(cat1, request_type);
  char host_colon[] = "Host: ";
  char *cat3 = strcat(cat2, host_colon);
  char *cat4 = strcat(cat3, host);
  char end_of_request[] = "\r\n\r\n";
  char *cat5 = strcat(cat4, end_of_request);

  if (send(socket_call, cat5, strlen(cat5), 0) < 0) {
    puts("\n\nsend failed\n\n");
    return 1;
  }

  if (recv(socket_call, server_reply, 2000, 0) < 0) {
    puts("\n\nrecv failed\n");
  }

  server_reply[15] = '\0';

  char check200[] = "HTTP/1.1 200";

  if (memcmp(server_reply, check200, 12) == 0) {
    char *cat6 = strcat(cat5, "\n");
    char *cat7 = strcat(cat6, server_reply);
    char *cat8 = strcat(cat7, "\n");
    char *cat9 = strcat(cat8, "----------------");
    char *cat10 = strcat(cat9, "\n");
    printf("%s", cat10);
  }

  close(socket_call);

  return 0;
}

int iterates_file(char *host, in_port_t port, char *wordlist,
                  int request_delay) {

  FILE *file;

  file = fopen(wordlist, "r");

  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  char c;
  do {
    c = fgetc(file);
    if (c == '\n')
      file_size++;

  } while (c != EOF);

  for (int i = 0; i < file_size; i++) {
    pulls_string(file, i, wordlist);
    hello_socket(host, port);
    sleep(request_delay);
  }

  fclose(file);

  return file_size;
}

int pulls_string(FILE *pfile, int read_line, char *wordlist) {

  pfile = fopen(wordlist, "r");

  if (pfile == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  bool keep_reading = true;
  int current_line = 1;
  do {

    fgets(buffer, MAX_LINE, pfile);
    buffer[strcspn(buffer, "\n")] = 0;
    buffer[strcspn(buffer, " ")] = 0;

    if (feof(pfile)) {
      keep_reading = false;
      printf("File %d lines.\n", current_line - 1);
      printf("Couldn't find line %d.\n", read_line);
    } else if (current_line == read_line) {
      keep_reading = false;
    }

    current_line++;

  } while (keep_reading);

  fclose(pfile);

  return 0;
}

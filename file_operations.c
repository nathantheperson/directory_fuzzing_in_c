#include "config.h"

int iteratesFile(char* wordlist) {
  int file_size = 0;

  FILE* file;

  file = fopen(wordlist, "r");

  if (file == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  char c;
  do {
    c = fgetc(file);
    if (c == '\n') file_size++;

  } while (c != EOF);

  fclose(file);

  return file_size;
}

char* pullsString(char* wordlist, int read_line, char buffer[]) {
  FILE* file;

  file = fopen(wordlist, "r");

  if (file == NULL) {
    printf("Error opening file.\n");
    return NULL;
  }

  bool keep_reading = true;
  int current_line = 1;
  do {
    fgets(buffer, MAX_LINE, file);
    buffer[strcspn(buffer, "\n")] = 0;
    buffer[strcspn(buffer, " ")] = 0;

    if (feof(file)) {
      keep_reading = false;
      printf("%d requests will be sent\n----------------\n", current_line - 1);
    } else if (current_line == read_line) {
      keep_reading = false;
    }

    current_line++;

  } while (keep_reading);

  fclose(file);

  return buffer;
}

char* buildRequest(char* buffer, char* host, char build_request[]) {
  // if you want to use a word list with / before the words, change   char
  // get[MAX_LINE * 2] = "GET /";    to    char get[MAX_LINE * 2] = "GET ";
  char get[MAX_LINE] = "GET /";
  char* cat1 = strcat(get, buffer);
  char request_type[] = " HTTP/1.1\r\n";
  char* cat2 = strcat(cat1, request_type);
  char host_colon[] = "Host: ";
  char* cat3 = strcat(cat2, host_colon);
  char* cat4 = strcat(cat3, host);
  char end_of_request[] = "\r\n\r\n";
  char* cat5 = strcat(cat4, end_of_request);

  for (int i = 0; i < sizeof(get); i++) {
    *(build_request + i) = *(get + i);
  }

  return build_request;
}

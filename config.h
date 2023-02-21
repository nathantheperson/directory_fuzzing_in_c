#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
//#include <openssl/ssl.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 512
#define TABLE_SIZE 20000

typedef struct ResponseData {
  char* head;
  char* body;
  int head_size_in_bytes;
  int head_lines;
  int total_response_size;
  int current_response_size;
} ResponseData;


typedef struct entry_t {
  char* key;
  char* value;
  struct entry_t *next;
} entry_t;


typedef struct ht_t {
  entry_t** entries;
} ht_t;


typedef struct TemporaryKeyHolder {
  char* key;
  char* value;
} TemporaryKeyHolder;


#include "file_operations.h"
#include "response_parsing.h"
#include "socket_http.h"
#include "hash_table.h"

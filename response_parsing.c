#include "config.h"

int severHeadFromBody(char* server_reply, int numbytes,
                                ResponseData* pData) {

  char* check_if_header1 = strstr(server_reply, "\r\nContent-Type: ");
  char* check_if_header2 = strstr(server_reply, "\r\nContent-Length: ");
  char* check_if_header3 = strstr(server_reply, "\r\nDate: ");
  char* check_if_header4 = strstr(server_reply, "\r\nServer: ");

  int head_size = 0;
  int body_size = 0;
  char* savehead = NULL;
  char* savebody = NULL;

  pData->head = NULL;
  pData->body = NULL;
  pData->current_response_size = 0;

  if (check_if_header1 == NULL || check_if_header2 == NULL ||
      check_if_header3 == NULL || check_if_header4 == NULL) {
    printf("\n\nNULL pointer \n\n");
    return 1;
  }

  char* ptr = server_reply;
  for (int i = 0; i < (numbytes - 3); i++) {
    
        if ((ptr[0] == '\r') && (ptr[1] == '\n') && (ptr[2] == '\r') &&
            (ptr[3] == '\n')) {
          ptr[3] = 0;
          savehead = server_reply;
          savebody = ptr + 4;
	  pData->head = savehead;
	  pData->body = savebody;
          break;
        }
        
    ptr++;
  }

  if (pData->head == NULL || pData->body == NULL) {
    printf("\n\nerror parsing server response\n\n");
  }

 
  while (*(savehead++) != '\0') {
    head_size++;
  }
  while (*(savebody++) != '\0') {
    body_size++;
  }
  
  pData->head_size_in_bytes = head_size;
  pData->current_response_size = body_size;

  return 0;
}



int countHeadSize(ResponseData* pData, char c) {

  int length = pData->head_size_in_bytes;
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (pData->head[i] == c) { count++; }
  } 
  return count;
}  



char* pullsHeaderString(ResponseData* pData, int read_line, char c, char* buffer) {

  int length = pData->head_size_in_bytes;
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (pData->head[i] == c) { 
      count++; 
      if (count == read_line) {
        buffer = (pData->head+i+1);
	int find_end = strcspn(buffer, "\r");
        *(pData->head+i+1+find_end) = '\0';
	return buffer;
      }
    }
  }
   
  printf("\n\nerror parsing header in pullsHeaderString\n\n");
  return NULL;
}


int pullKey_Value(TemporaryKeyHolder* pKey_Value, char* ht_buffer) {

  int find_colon = strcspn(ht_buffer, ":");
  char* value = (ht_buffer+find_colon+2);
  *(ht_buffer+find_colon) = 0;

  pKey_Value->key = ht_buffer;
  pKey_Value->value = value;


  return 0;
}

int pullResponseCode(char* server_reply, ht_t* ht) {

  int find_space = strcspn(server_reply, " ");
  char* value = (server_reply+find_space+1);
  *(server_reply+find_space) = 0;
  *(server_reply+find_space+4) = 0;
  *(server_reply+4) = 0;
  ht_set(ht, server_reply, value);

  return 0;
}

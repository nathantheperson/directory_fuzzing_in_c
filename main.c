#include "config.h"

int main(int argc, char* argv[]) {
  if (argc != 5) {
    fprintf(stderr,
            "Usage: %s <hostname> <port> <path/to/wordlist> <http or https>\n",
            argv[0]);

    return 0;
  }

  //name_resolution()

  int file_size = iteratesFile(argv[3]);

  if (strcmp(argv[4], "http") == 0) {
    int socket_call = createSockHttp();
    int connect_socket = connectSockHttp(socket_call, argv[1], atoi(argv[2]));

    for (int i = 1; i < file_size + 1; i++) {
      char buffer[MAX_LINE];
      char http_request[MAX_LINE];
      char server_reply[MAX_LINE];
      char* pbuffer = buffer;
      char* phttp_request = http_request;

      char* current_word = pullsString(argv[3], i, pbuffer);

      char* built_request = buildRequest(current_word, argv[1], phttp_request);

      if (sendHttp(socket_call, built_request) != 0) {
        puts("\nsend error\n");
      }

      int numbytes = recvHttp(socket_call, server_reply);
      if (numbytes < 0) {
        printf("\n\nHTTP receive failed\n\n");
        return 0;
      }

      ResponseData Data;
      ResponseData* pData = &Data; 

      int sever_return = severHeadFromBody(server_reply, numbytes, pData);
      if (sever_return != 0) {
        printf("\n\nResponse parsing failed\n\n");
      }

      pData->head_lines = countHeadSize(pData, '\n');

      ht_t* ht = ht_create();
      char* ht_buffer;

      TemporaryKeyHolder Key_Value;
      TemporaryKeyHolder* pKey_Value = &Key_Value;

      if (pullResponseCode(pData->head, ht) != 0) {
        printf("\n\npullResponseCode failed\n\n");
      }
      for (int i = 1; i < pData->head_lines; i++) {
        char* current_line = pullsHeaderString(pData, i, '\n', ht_buffer);
        if (pullKey_Value(pKey_Value, current_line) != 0) {
	  printf("\n\npullKey_Value failed\n\n");
	}
	ht_set(ht, pKey_Value->key, pKey_Value->value);
      }

      //ht_dump(ht);
      printf("\nfor %s\n", current_word);
      printf("HTTP=%s\n", ht_get(ht, "HTTP"));

      pData->total_response_size = atoi(ht_get(ht, "Content-Length"));

      while (pData->current_response_size < pData->total_response_size) {
        int new_recv = recvHttp(socket_call, server_reply);
        pData->current_response_size = (pData->current_response_size + new_recv);
	sleep(1);
      }

      //figure out how to dynamically iterate through the list and free everything
      ht_del(ht, "Date");
      ht_del(ht, "HTTP/1.1");
      ht_del(ht, "Content-Length");
      ht_del(ht, "Last-Modified");
      ht_del(ht, "Vary");
      ht_del(ht, "ETab");
      ht_del(ht, "Accept-Ranges");
      ht_del(ht, "Server");
      ht_del(ht, "Content-Type");

      //make sure to free all malloc's
      free(ht->entries);
      free(ht);


    }

     
  }

  else if (strcmp(argv[4], "https") == 0) {
    printf("\n\nyou chose https instead of http");
    return 0;
  }

  else {
    printf("\n\nplease specify http or https\n\n");
    return 0;
  }

  return 0;
}

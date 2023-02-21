#pragma once

#include "config.h"

int severHeadFromBody(char* server_reply, int numbytes, ResponseData* pData);

int countHeadSize(ResponseData* pData, char c);

char* pullsHeaderString(ResponseData* pData, int read_line, char c, char* buffer);

int pullKey_Value(TemporaryKeyHolder* pKey_Value, char* ht_buffer);

int pullResponseCode(char* server_reply, ht_t* ht);

#pragma once 

#include "config.h"

int iteratesFile(char* wordlist);

char* pullsString(char* wordlist, int read_line, char buffer[]);

char* buildRequest(char* buffer, char* host, char* request);

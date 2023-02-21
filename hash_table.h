#pragma once

#include "config.h"

unsigned int hash(const char *key);

entry_t *ht_pair(const char *key, const char *value);

ht_t *ht_create(void);

void ht_set(ht_t *hashtable, const char *key, const char *value);

char *ht_get(ht_t *hashtable, const char *key);

void ht_del(ht_t *hashtable, const char *key);

void ht_dump(ht_t *hashtable);

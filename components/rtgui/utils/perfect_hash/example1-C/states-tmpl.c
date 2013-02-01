
#include <string.h>

#include "states-code.h"


static int T1[] = { $S1 };

static int T2[] = { $S2 };

static int G[] = { $G };

static char *K[] = { $K };

static int hash_g (const char *key, const int *T)
{
  int i, sum = 0;
  
  for (i = 0; key[i] != '\0'; i++) {
    sum += T[i] * key[i];
    sum %= $NG;
  }
  return G[sum];
}

static int perfect_hash (const char *key)
{
  if (strlen (key) > $NS)
    return 0;
  
  return (hash_g (key, T1) + hash_g (key, T2)) % $NG;
}

int has_key (const char *abbr)
{
  int hash_value = perfect_hash (abbr);
  
  if (hash_value < $NK && strcmp(abbr, K[hash_value]) == 0)
    return hash_value;
  
  return -1;
}

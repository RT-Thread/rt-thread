
#include <string.h>

#include <iostream>

#include "states-code.hh"

static struct {
  char *name;
  char *abbr;
  int pop;
} states[$NK] = {
#include "states.dat.h"
};

static int T1[] = { $S1 };

static int T2[] = { $S2 };

static int G[] = { $G };

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

State::State (const string abbr)
{
  int hash_value = perfect_hash (abbr.c_str ());
  
  if (hash_value < $NK &&
      strcmp(abbr.c_str (), states[hash_value].abbr) == 0)
    {
      nam = states[hash_value].name;
      pop = states[hash_value].pop;
    }
  else
    {
      cerr << "'" << abbr << "' is not an abbreviation for a state\n";
    }
}

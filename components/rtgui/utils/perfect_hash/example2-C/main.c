
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "keys.code.h"

int hash_g (char *s, int *T)
{
  int i, f = 0;

  for (i = 0; s[i] != '\0'; i++) {
    f += T[i] * s[i];
    f %= NG;
  }
  return G[f];
}

int hash (char *k)
{
  if (strlen (k) > NS)
    return 0;
  
  return (hash_g (k, T1) + hash_g (k, T2)) % NG;
}

bool has_key (char *k)
{
  int h = hash (k);
  
  return h < NK && strcmp(k, K[h]) == 0;
}

int main ()
{
  int i;

  char *junk = "acnhuvn5yushvghnw7og5siuhgsiuhnglsh45vgghwn";

  assert (has_key(junk) == 0);
  assert (hash(junk) == 0);
  
  for (i = 0; i < NK; i++) {
    assert (has_key(K[i]) == true);
    assert (hash(K[i]) == i);
  }
  puts ("OK");
  
  return 0;
}

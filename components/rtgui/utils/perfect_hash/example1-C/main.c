
#include <stdio.h>

#include "states-code.h"

struct {
  char *name;
  char *abbr;
  int pop;
} states[] = {
#include "states.dat.h"
};


int main (int argc, char *argv[])
{
  if (argc != 2) {
    printf ("Usage: %s <abbreviation>\n", argv[0]);
    return 2;
  }

  char *abbr = argv[1];
  int hashval;
  
  if ((hashval = has_key(abbr)) == -1)
    printf ("'%s' is not an abbreviation for a state.\n", abbr);
  else
    printf ("The state of %s has a population of %g million.\n",
	    states[hashval].name,
	    1e-6 * states[hashval].pop);
  
  return 0;
}

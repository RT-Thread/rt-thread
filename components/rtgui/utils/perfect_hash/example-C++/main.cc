
#include <iostream>
#include <string>
using namespace std;

#include "states-code.hh"


int main (int argc, char *argv[])
{
  if (argc != 2) {
    printf ("Usage: %s <abbreviation>\n", argv[0]);
    return 2;
  }

  string abbr = argv[1];

  State s(abbr);

  cout << "The state of " << s.name ()
       << " has a population of " << 1e-6 * s.population () << " million.\n";
  
  return 0;
}



#include <string>
using namespace std;


class State
{
public:
  State (const string abbr);

  string name () const { return nam; };
  int population () const { return pop; };

private:
  string nam;
  int pop;
};


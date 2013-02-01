
#include <Python.h>

#include "stations-code.h"

static struct {
  char *callsign;
  char *locator;
} station_list[] = {
#include "stations.dat.h"
};

static int hash_f (const char *s, const int *T)
{
  register int i, sum = 0;

  for (i = 0; s[i] != '\0'; i++) {
    sum += T[i] * s[i];
    sum %= NG;
  }
  return sum;
}

static int perf_hash (const char *k)
{
  if (strlen (k) > NS)
    return 0;
  
  return (G[ hash_f(k, T1) ] + G[ hash_f(k, T2)] ) % NG;
}

static int getlocator (char *locator, const char *callsign)
{
  int hashval = perf_hash (callsign);
  
  if (hashval < NK && strcmp(callsign, station_list[hashval].callsign) == 0) {
    strcpy (locator, station_list[hashval].locator);
    return 1;
  }
  return 0;
}

static PyObject *
stations_locator(PyObject *self, PyObject *args)
{
  const char *callsign;
  char locator[6];
  
  if (!PyArg_ParseTuple(args, "s", &callsign))
    return NULL;
  
  return Py_BuildValue("s", (getlocator (locator, callsign) == 1) ?
		       locator : NULL);
}

static PyMethodDef StationsMethods[] = {

    {"locator",  stations_locator, METH_VARARGS,
     "Get locator from callsign."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};


PyMODINIT_FUNC
initstations(void)
{
  (void) Py_InitModule("stations", StationsMethods);
}

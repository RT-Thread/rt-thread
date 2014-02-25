#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h> // for readdir

#include "jslex.h"
#include "jsvar.h"
#include "jsparse.h"
#include "jswrap_json.h"

#include "jsinteractive.h"
#include "jshardware.h"
#include <finsh.h>

#define TEST_DIR "tests/"

bool isRunning = true;

void nativeQuit(JsVarRef var) {
  NOT_USED(var);
  isRunning = false;
}

void nativeInterrupt(JsVarRef var) {
  NOT_USED(var);
  jspSetInterrupted(true);
}

const char *read_file(const char *filename) {
  struct stat results;
  if (!stat(filename, &results) == 0) {
    printf("Cannot stat file! '%s'\r\n", filename);
    return 0;
  }
  int size = (int)results.st_size;
  FILE *file = fopen( filename, "rb" );
  /* if we open as text, the number of bytes read may be > the size we read */
  if( !file ) {
     printf("Unable to open file! '%s'\r\n", filename);
     return 0;
  }
  char *buffer = malloc(size+1);
  size_t actualRead = fread(buffer,1,size,file);
  buffer[actualRead]=0;
  buffer[size]=0;
  fclose(file);
  return buffer;
}

bool run_test(const char *filename) {
  printf("----------------------------------\r\n");
  printf("----------------------------- TEST %s \r\n", filename);
  char *buffer = (char *)read_file(filename);
  if (!buffer) return (false);

  jshInit();
  jsiInit(false /* do not autoload!!! */);

  jspAddNativeFunction(jsiGetParser(), "function quit()", nativeQuit);
  jspAddNativeFunction(jsiGetParser(), "function interrupt()", nativeInterrupt);

  jsvUnLock(jspEvaluate(jsiGetParser(), buffer ));

  isRunning = true;
  while (isRunning && jsiHasTimers()) jsiLoop();

  JsVar *result = jsvObjectGetChild(jsiGetParser()->root, "result", 0/*no create*/);
  bool pass = jsvGetBool(result);
  jsvUnLock(result);

  if (pass)
    printf("----------------------------- PASS %s\r\n", filename);
  else {
    printf("----------------------------------\r\n");
    printf("----------------------------- FAIL %s <-------\r\n", filename);
    jsvTrace(jsvGetRef(jsiGetParser()->root), 0);
    printf("----------------------------- FAIL %s <-------\r\n", filename);
    printf("----------------------------------\r\n");
  }
  printf("BEFORE: %d Memory Records Used\r\n", jsvGetMemoryUsage());
 // jsvTrace(jsiGetParser()->root, 0);
  jsiKill();
  printf("AFTER: %d Memory Records Used\r\n", jsvGetMemoryUsage());
  jsvGarbageCollect();
  printf("AFTER GC: %d Memory Records Used (should be 0!)\r\n", jsvGetMemoryUsage());
  jsvShowAllocated();
  jshKill();

  //jsvDottyOutput();
  printf("\r\n");

  free(buffer);
  return pass;
}


bool run_all_tests() {
  int count = 0;
  int passed = 0;

  char *fails = malloc(1);
  fails[0] = 0;

  DIR *dir = opendir(TEST_DIR);
  if(dir) {
    struct dirent *pDir=NULL;
    while((pDir = readdir(dir)) != NULL) {
      char *fn = (*pDir).d_name;
      int l = strlen(fn);
      if (l>3 && fn[l-3]=='.' && fn[l-2]=='j' && fn[l-1]=='s') {
        char *full_fn = malloc(1+l+strlen(TEST_DIR));
        strcpy(full_fn, TEST_DIR);
        strcat(full_fn, fn);
        if (run_test(full_fn)) {
          passed++;
        } else {
          char *t = malloc(strlen(fails)+3+strlen(full_fn));
          strcpy(t, fails);
          strcat(t,full_fn);
          strcat(t,"\r\n");
          free(fails);
          fails  =t;
        }
        count++;
      }
    }
    closedir(dir);
  } else {
    printf(TEST_DIR" directory not found");
  }

  if (count==0) printf("No tests found in "TEST_DIR"test*.js!\r\n");
  printf("--------------------------------------------------\r\n");
  printf(" %d of %d tests passed\r\n", passed, count);
  if (passed!=count) {
   printf("FAILS:\r\n%s", fails);
  }
  printf("--------------------------------------------------\r\n");
  free(fails);
  return passed == count;
}

bool run_memory_test(const char *fn, int vars) {
  int i;
  int min = 20;
  int max = 100;
  if (vars>0) {
    min = vars;
    max = vars+1;
  }
  for (i=min;i<max;i++) {
    jsvSetMaxVarsUsed(i);
    printf("----------------------------------------------------- MEMORY TEST WITH %d VARS\n", i);
    if (!run_test(fn))
        return false;
  }
  return true;
}

bool run_memory_tests(int vars) {
  int test_num = 1;
  int count = 0;
  int passed = 0;

  while (test_num<1000) {
    char fn[32];
    sprintf(fn, TEST_DIR"test%03d.js", test_num);
    // check if the file exists - if not, assume we're at the end of our tests
    FILE *f = fopen(fn,"r");
    if (!f) break;
    fclose(f);

    run_memory_test(fn, vars);
    test_num++;
  }

  if (count==0) printf("No tests found in "TEST_DIR"test*.js!\n");
  return true;
}

void show_help() {
    printf("Usage:\n");
    printf("   ./espruino                           : JavaScript immdeiate mode (REPL)\n");
    printf("   ./espruino script.js                 : Load and run script.js\n");
    printf("   ./espruino -e \"print('Hello World')\" : Print 'Hello World'\n");
    printf("\n");
    printf("Options:\n");
    printf("   -h, --help              Print this help screen\n");
    printf("   -e, --eval script       Evaluate the JavaScript supplied on the command-line\n");
    printf("   --test-all              Run all tests (in 'tests' directory)\n");
    printf("   --test test.js          Run the supplied test\n");
    printf("   --test-mem-all          Run all Exhaustive Memory crash tests\n");
    printf("   --test-mem test.js      Run the supplied Exhaustive Memory crash test\n");
    printf("   --test-mem-n test.js #  Run the supplied Exhaustive Memory crash test with # vars\n");
}

#define die(txt)                \
do{                             \
  printf("%s", txt);            \
  return (1);                   \
} while(0)

int espruino(int argc, char **argv) {
  int i;
  for (i=1;i<argc;i++) {
    if (argv[i][0]=='-') {
      // option
      char *a = argv[i];
      if (!strcmp(a,"-h") || !strcmp(a,"--help")) {
        show_help();
        return (1);
      } else if (!strcmp(a,"-e") || !strcmp(a,"--eval")) {
        if (i+1>=argc) die("Expecting an extra argument\n");
        jshInit();
        jsiInit(true);
        jspAddNativeFunction(jsiGetParser(), "function quit()", nativeQuit);
        jsvUnLock(jspEvaluate(jsiGetParser(), argv[i+1]));
        isRunning = true;
        //while (isRunning && jsiHasTimers()) jsiLoop();
        jsiKill();
        jshKill();
        return (0);
      } else if (!strcmp(a,"--test")) {
        if (i+1>=argc) die("Expecting an extra argument\n");
        bool ok = run_test(argv[i+1]);
        return (ok ? 0 : 1);
      } else if (!strcmp(a,"--test-all")) {
        bool ok = run_all_tests();
        return (ok ? 0 : 1);
      } else if (!strcmp(a,"--test-mem-all")) {
        bool ok = run_memory_tests(0);
        return (ok ? 0 : 1);
      } else if (!strcmp(a,"--test-mem")) {
        if (i+1>=argc) die("Expecting an extra argument\n");
        bool ok = run_memory_test(argv[i+1], 0);
        return (ok ? 0 : 1);
      } else if (!strcmp(a,"--test-mem-n")) {
        if (i+2>=argc) die("Expecting an extra 2 arguments\n");
        bool ok = run_memory_test(argv[i+1], atoi(argv[i+2]));
        return (ok ? 0 : 1);
      } else {
        printf("Unknown Argument %s\n", a);
        show_help();
        return -1;
      }
    }
  }

  if (argc==1) {
    printf("Interactive mode.\n");
  } else if (argc==2) {
    // single file - just run it
    char *buffer = (char *)read_file(argv[1]);
    if (!buffer) return (1);
    // check for '#' as the first char, and if so, skip the first line
    char *cmd = buffer;
    if (cmd[0]=='#') {
      while (cmd[0] && cmd[0]!='\n') cmd++;
      if (cmd[0]=='\n') cmd++;
    }
    jshInit();
    jsiInit(false /* do not autoload!!! */);
    jspAddNativeFunction(jsiGetParser(), "function quit()", nativeQuit);
    jsvUnLock(jspEvaluate(jsiGetParser(), cmd ));
    free(buffer);
    //isRunning = true;
    //while (isRunning && jsiHasTimers()) jsiLoop();
    jsiKill();
    jshKill();
    return -1;
  } else {
    printf("Unknown arguments!\n");
    show_help();
    return -1;
  }

  printf("Size of JsVar is now %d bytes\n", (int)sizeof(JsVar));
  printf("Size of JsVarRef is now %d bytes\n", (int)sizeof(JsVarRef));

  jshInit();
  jsiInit(true);

  jspAddNativeFunction(jsiGetParser(), "function quit()", nativeQuit);
  jspAddNativeFunction(jsiGetParser(), "function interrupt()", nativeInterrupt);

  while (isRunning) {
    jsiLoop();
  }
  jsiConsolePrint("\n");
  jsiKill();

  jsvShowAllocated();
  jshKill();

  return 0;
}

MSH_CMD_EXPORT(espruino, JavaScript Interpreter)


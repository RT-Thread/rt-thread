#include <ctype.h>
#include <fnmatch.h>
#include <string.h>

#define NOTFIRST 128

#define STRUCT_CHARCLASS(c) { #c , is##c }

static struct charclass {
  char * class;
  int (*istype)(int);
} allclasses[] = {
  STRUCT_CHARCLASS(alnum),
  STRUCT_CHARCLASS(alpha),
  STRUCT_CHARCLASS(blank),
  STRUCT_CHARCLASS(cntrl),
  STRUCT_CHARCLASS(digit),
  STRUCT_CHARCLASS(graph),
  STRUCT_CHARCLASS(lower),
  STRUCT_CHARCLASS(print),
  STRUCT_CHARCLASS(punct),
  STRUCT_CHARCLASS(space),
  STRUCT_CHARCLASS(upper),
  STRUCT_CHARCLASS(xdigit),
};

/* look for "class:]" in pattern */
static struct charclass *charclass_lookup(const char *pattern) {
  unsigned int i;

  for (i = 0; i< sizeof(allclasses)/sizeof(*allclasses); i++) {
    int len = strlen(allclasses[i].class);
    if (!strncmp(pattern, allclasses[i].class, len)) {
      pattern += len;
      if (strncmp(pattern, ":]", 2)) goto noclass;
      return &allclasses[i];
    }
  }
noclass:
  return NULL;
}

static int match(char c,char d,int flags) {
  if (flags&FNM_CASEFOLD)
    return (tolower(c)==tolower(d));
  else
    return (c==d);
}

int fnmatch(const char *pattern, const char *string, int flags) {
  if (*string==0) {
    while (*pattern=='*') ++pattern;
    return (!!*pattern);
  }
  if (*string=='.' && *pattern!='.' && (flags&FNM_PERIOD)) {
    /* don't match if FNM_PERIOD and this is the first char */
    if (!(flags&NOTFIRST))
      return FNM_NOMATCH;
    /* don't match if FNM_PERIOD and FNM_PATHNAME and previous was '/' */
    if ((flags&(FNM_PATHNAME)) && string[-1]=='/')
      return FNM_NOMATCH;
  }
  flags|=NOTFIRST;
  switch (*pattern) {
  case '[':
    {
      int neg=0;
      const char* start;	/* first member of character class */

      ++pattern;
      if (*string=='/' && flags&FNM_PATHNAME) return FNM_NOMATCH;
      if (*pattern=='!') { neg=1; ++pattern; }
      start=pattern;
      while (*pattern) {
	int res=0;

	if (*pattern==']' && pattern!=start) break;
	if (*pattern=='[' && pattern[1]==':') {
	  /* MEMBER - stupid POSIX char classes */
	  const struct charclass *cc;

	  if (!(cc = charclass_lookup(pattern+2))) goto invalidclass;
	  pattern += strlen(cc->class) + 4;
	  if (flags&FNM_CASEFOLD
	      && (cc->istype == isupper || cc->istype == islower)) {
	    res = islower(tolower(*string));
	  } else {
            res = ((*(cc->istype))(*string));
	  }
	} else {
invalidclass:
	  if (pattern[1]=='-' && pattern[2]!=']') {
	    /* MEMBER - character range */
	    if (*string>=*pattern && *string<=pattern[2]) res=1;
	    if (flags&FNM_CASEFOLD) {
	      if (tolower(*string)>=tolower(*pattern) && tolower(*string)<=tolower(pattern[2])) res=1;
	    }
	    pattern+=3;
	  } else {
	    /* MEMBER - literal character match */
	    res=match(*pattern,*string,flags);
	    ++pattern;
	  }
	}
	if ((res&&!neg) || ((neg&&!res) && *pattern==']')) {
	  while (*pattern && *pattern!=']') ++pattern;
	  return fnmatch(pattern+!!*pattern,string+1,flags);
	} else if (res && neg)
	  return FNM_NOMATCH;
      }
    }
    break;
  case '\\':
    if (flags&FNM_NOESCAPE) {
      if (*string=='\\')
	return fnmatch(pattern+1,string+1,flags);
    } else {
      if (*string==pattern[1])
	return fnmatch(pattern+2,string+1,flags);
    }
    break;
  case '*':
    if ((*string=='/' && flags&FNM_PATHNAME) || fnmatch(pattern,string+1,flags))
      return fnmatch(pattern+1,string,flags);
    return 0;
  case 0:
    if (*string==0 || (*string=='/' && (flags&FNM_LEADING_DIR)))
      return 0;
    break;
  case '?':
    if (*string=='/' && flags&FNM_PATHNAME) break;
    return fnmatch(pattern+1,string+1,flags);
  default:
    if (match(*pattern,*string,flags))
      return fnmatch(pattern+1,string+1,flags);
    break;
  }
  return FNM_NOMATCH;
}

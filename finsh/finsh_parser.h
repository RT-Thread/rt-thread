#ifndef __FINSH_PARSER_H__
#define __FINSH_PARSER_H__

#include <finsh.h>

int finsh_parser_init(struct finsh_parser* self);
void finsh_parser_run(struct finsh_parser* self, const u_char* string);

#endif

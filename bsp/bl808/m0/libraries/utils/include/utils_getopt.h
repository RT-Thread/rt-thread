/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __GETOPT_H__
#define __GETOPT_H__
/**
 * @brief Parameters needed to parse the command line
 *
 */
typedef struct getopt_env {
    char *optarg;    /*!< if the option accepts parameters, then optarg point to the option parameter*/
    int optind;      /*!< current index of argv*/
    int opterr;      /*!< non-zero enable error message output, while 0,no error message output*/
    int optopt;      /*!< contain unrecognized option character*/
    int __optpos;    
} getopt_env_t;

/**
 * @brief Initialize struct getopt_env
 *
 * @param env pointer to struct getopt_env
 * @param opterr set error message output method
 *
 * @return 
 *     -  0: success
 *     - -1: fail
 */
int utils_getopt_init(getopt_env_t *env, int opterr);

/**
 * @brief Parses the command-line arguments
 *
 * @param env pointer to struct getopt_env
 * @param argc the argument count 
 * @param argv the argument array
 *
 * @return 
 *     -  option character : an option was successfully found
 *     - -1 : all command-line options have been parsed 
 *     - '?' : option character was not in optstring
 *     - ':' or '?' : If utils_getopt() encounters an option with a missing argument, then the return value depends on the first character in optstring: if it is ':', then ':' is returned; otherwise '?' is returned
 *
 * @note Example
 * @code
 *
 * #include <utils_getopt.h>
 * #include <stdio.h>
 *
 * void cmd(char *buf, int len, int argc, char **argv)
 * {
 *     int opt;
       getopt_env_t getopt_env;
       utils_getopt_init(&getopt_env, 0);
 *     //put ':' in the starting of the string so that program can distinguish between '?' and ':'
 *     while ((opt = utils_getopt(&getopt_env, argc, argv, ":if:lr")) != -1) {
 *         switch(opt)
 *         {
 *             case 'i':
 *             case 'l':
 *             case 'r':
 *                 printf("option: %c\r\n", opt);
 *                 break;
 *             case 'f':
 *                 printf("filename: %s\r\n", getopt_env.optarg);
 *                 break;
 *             case ':':
                   printf("%s: %c requires an argument\r\n", *argv, getopt_env.optopt);
 *                 break;
 *             case '?':
 *                 printf("unknow option: %c\r\n", getopt_env.optopt);
 *                 break;
 *          }
 *      }
 *      //optind is for the extra arguments which are not parsed
 *      for(; getopt_env.optind < argc; getopt_env.optind++){
 *          printf("extra arguments: %s\r\n", argv[getopt_env.optind]);
 *      }
 *
 *  }
 *  @endcode
 */
int utils_getopt(getopt_env_t *env, int argc, char * const argv[], const char *optstring);

#endif /* __GETOPT_H__ */

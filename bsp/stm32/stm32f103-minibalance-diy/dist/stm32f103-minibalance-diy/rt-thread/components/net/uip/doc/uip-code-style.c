/* This is the official code style of uIP. */

/**
 * \defgroup codestyle Coding style
 *
 * This is how a Doxygen module is documented - start with a \defgroup
 * Doxygen keyword at the beginning of the file to define a module,
 * and use the \addtogroup Doxygen keyword in all other files that
 * belong to the same module. Typically, the \defgroup is placed in
 * the .h file and \addtogroup in the .c file.
 *
 * @{
 */

/**
 * \file
 *         A brief description of what this file is.
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 *         Every file that is part of a documented module has to have
 *         a \file block, else it will not show up in the Doxygen
 *         "Modules" * section.
 */

/* Single line comments look like this. */

/*
 * Multi-line comments look like this. Comments should prefferably be
 * full sentences, filled to look like real paragraphs.
 */

#include "uip.h"

/*
 * Make sure that non-global variables are all maked with the static
 * keyword. This keeps the size of the symbol table down.
 */
static int flag;

/*
 * All variables and functions that are visible outside of the file
 * should have the module name prepended to them. This makes it easy
 * to know where to look for function and variable definitions.
 *
 * Put dividers (a single-line comment consisting only of dashes)
 * between functions.
 */
/*---------------------------------------------------------------------------*/
/**
 * \brief      Use Doxygen documentation for functions.
 * \param c    Briefly describe all parameters.
 * \return     Briefly describe the return value.
 * \retval 0   Functions that return a few specified values
 * \retval 1   can use the \retval keyword instead of \return.
 *
 *             Put a longer description of what the function does
 *             after the preamble of Doxygen keywords.
 *
 *             This template should always be used to document
 *             functions. The text following the introduction is used
 *             as the function's documentation.
 *
 *             Function prototypes have the return type on one line,
 *             the name and arguments on one line (with no space
 *             between the name and the first parenthesis), followed
 *             by a single curly bracket on its own line.
 */
void
code_style_example_function(void)
{
  /*
   * Local variables should always be declared at the start of the
   * function.
   */
  int i;                   /* Use short variable names for loop
			      counters. */

  /*
   * There should be no space between keywords and the first
   * parenthesis. There should be spaces around binary operators, no
   * spaces between a unary operator and its operand.
   *
   * Curly brackets following for(), if(), do, and case() statements
   * should follow the statement on the same line.
   */
  for(i = 0; i < 10; ++i) {
    /*
     * Always use full blocks (curly brackets) after if(), for(), and
     * while() statements, even though the statement is a single line
     * of code. This makes the code easier to read and modifications
     * are less error prone.
     */
    if(i == c) {
      return c;           /* No parentesis around return values. */
    } else {              /* The else keyword is placed inbetween
			     curly brackers, always on its own line. */
      c++;
    }
  }
}
/*---------------------------------------------------------------------------*/
/*
 * Static (non-global) functions do not need Doxygen comments. The
 * name should not be prepended with the module name - doing so would
 * create confusion.
 */
static void
an_example_function(void)
{
  
}
/*---------------------------------------------------------------------------*/

/* The following stuff ends the \defgroup block at the beginning of
   the file: */

/** @} */

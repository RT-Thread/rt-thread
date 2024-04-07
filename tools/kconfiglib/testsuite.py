# Copyright (c) 2011-2019, Ulf Magnusson
# SPDX-License-Identifier: ISC

# This is the Kconfiglib test suite. It runs selftests on Kconfigs provided by
# us and tests compatibility with the C Kconfig implementation by comparing the
# output of Kconfiglib with the output of the scripts/kconfig/*conf utilities
# for different targets and defconfigs. It should be run from the top-level
# kernel directory with
#
#   $ python Kconfiglib/testsuite.py
#
# Some additional options can be turned on by passing them as arguments. They
# default to off.
#
#  - obsessive:
#    By default, only valid arch/defconfig pairs are tested. In obsessive mode,
#    every arch will be tested with every defconfig. Increases the testing time
#    by an order of magnitude. Occasionally finds (usually obscure) bugs, and I
#    make sure everything passes with it.
#
#  - obsessive-min-config:
#    Like obsessive, for the minimal configuation (defconfig) tests.
#
#  - log:
#    Log timestamped defconfig test failures to the file test_defconfig_fails.
#    Handy in obsessive mode.
#
# For example, this commands runs the test suite in obsessive mode with logging
# enabled:
#
#   $ python(3) Kconfiglib/testsuite.py obsessive log
#
# pypy works too, and runs most tests much faster than CPython.
#
# All tests should pass. Report regressions to ulfalizer a.t Google's email
# service.

import difflib
import errno
import os
import re
import shutil
import subprocess
import sys
import tempfile
import textwrap

from kconfiglib import Kconfig, Symbol, Choice, COMMENT, MENU, MenuNode, \
                       BOOL, TRISTATE, HEX, \
                       TRI_TO_STR, \
                       escape, unescape, \
                       expr_str, expr_items, split_expr, \
                       _ordered_unique, \
                       OR, AND, \
                       KconfigError


def shell(cmd):
    with open(os.devnull, "w") as devnull:
        subprocess.call(cmd, shell=True, stdout=devnull, stderr=devnull)


all_passed = True


def fail(msg=None):
    global all_passed
    all_passed = False
    if msg is not None:
        print("fail: " + msg)


def verify(cond, msg):
    if not cond:
        fail(msg)


def verify_equal(x, y):
    if x != y:
        fail("'{}' does not equal '{}'".format(x, y))


# Prevent accidental loading of configuration files by removing
# KCONFIG_ALLCONFIG from the environment
os.environ.pop("KCONFIG_ALLCONFIG", None)

obsessive = False
obsessive_min_config = False
log = False


def run_tests():
    global obsessive, log
    for s in sys.argv[1:]:
        if s == "obsessive":
            obsessive = True
            print("Obsessive mode enabled")
        elif s == "obsessive-min-config":
            obsessive_min_config = True
            print("Obsessive minimal config mode enabled")
        elif s == "log":
            log = True
            print("Log mode enabled")
        else:
            print("Unrecognized option '{}'".format(s))
            return

    run_selftests()
    run_compatibility_tests()


def run_selftests():
    #
    # Common helper functions. These all expect 'c' to hold the current
    # configuration.
    #

    def verify_value(sym_name, val):
        # Verifies that a symbol has a particular value.

        if isinstance(val, int):
            val = TRI_TO_STR[val]

        sym = c.syms[sym_name]
        verify(sym.str_value == val,
               'expected {} to have the value "{}", had the value "{}"'
               .format(sym_name, val, sym.str_value))

    def assign_and_verify_value(sym_name, val, new_val):
        # Assigns 'val' to a symbol and verifies that its value becomes
        # 'new_val'. Assumes (and tests) that 'val' is valid for the
        # symbol type.

        if isinstance(new_val, int):
            new_val = TRI_TO_STR[new_val]

        sym = c.syms[sym_name]
        old_val = sym.str_value
        verify(sym.set_value(val),
               "assigning '{}' to {} unexpectedly failed"
               .format(val, sym_name))
        verify(sym.str_value == new_val,
               "expected {} to have the value '{}' after being assigned the "
               "value '{}'. Instead, the value is '{}'. The old value was "
               "'{}'."
               .format(sym_name, new_val, val, sym.str_value, old_val))

    def assign_and_verify(sym_name, user_val):
        # Like assign_and_verify_value(), with the expected value being the
        # value just set.

        assign_and_verify_value(sym_name, user_val, user_val)

    def assign_and_verify_user_value(sym_name, val, user_val, valid):
        # Assigns a user value to the symbol and verifies the new user value.
        # If valid is True, the user value is valid for the type, otherwise
        # not. This is used to test the set_value() return value.

        sym = c.syms[sym_name]
        sym_old_user_val = sym.user_value

        verify(sym.set_value(val) == valid,
               "expected the user value '{}' to be {} for {}, was not"
               .format(val, "valid" if valid else "invalid", sym_name))
        verify(sym.user_value == user_val,
               "the assigned user value '{}' wasn't reflected in user_value "
               "on the symbol {}. Instead, the new user_value was '{}'. The "
               "old user value was '{}'."
               .format(user_val, sym_name, sym.user_value, sym_old_user_val))

    #
    # Selftests
    #

    print("Testing string literal lexing")

    # Dummy empty configuration just to get a Kconfig object
    c = Kconfig("Kconfiglib/tests/empty")

    def verify_string_lex(s, expected):
        # Verifies that a constant symbol with the name 'res' is produced from
        # lexing 's'

        res = c._tokenize("if " + s)[1].name
        verify(res == expected,
               "expected <{}> to produced the constant symbol <{}>, "
               'produced <{}>'.format(s[1:-1], expected, res))

    verify_string_lex(r""" "" """, "")
    verify_string_lex(r""" '' """, "")

    verify_string_lex(r""" "a" """, "a")
    verify_string_lex(r""" 'a' """, "a")
    verify_string_lex(r""" "ab" """, "ab")
    verify_string_lex(r""" 'ab' """, "ab")
    verify_string_lex(r""" "abc" """, "abc")
    verify_string_lex(r""" 'abc' """, "abc")

    verify_string_lex(r""" "'" """, "'")
    verify_string_lex(r""" '"' """, '"')

    verify_string_lex(r""" "\"" """, '"')
    verify_string_lex(r""" '\'' """, "'")

    verify_string_lex(r""" "\"\"" """, '""')
    verify_string_lex(r""" '\'\'' """, "''")

    verify_string_lex(r""" "\'" """, "'")
    verify_string_lex(r""" '\"' """, '"')

    verify_string_lex(r""" "\\" """, "\\")
    verify_string_lex(r""" '\\' """, "\\")

    verify_string_lex(r""" "\a\\'\b\c\"'d" """, 'a\\\'bc"\'d')
    verify_string_lex(r""" '\a\\"\b\c\'"d' """, "a\\\"bc'\"d")

    def verify_string_bad(s):
        # Verifies that tokenizing 's' throws a KconfigError. Strips the first
        # and last characters from 's' so we can use readable raw strings as
        # input.

        try:
            c.eval_string(s)
        except KconfigError:
            pass
        else:
            fail("expected tokenization of {} to fail, didn't".format(s[1:-1]))

    verify_string_bad(r""" " """)
    verify_string_bad(r""" ' """)
    verify_string_bad(r""" "' """)
    verify_string_bad(r""" '" """)
    verify_string_bad(r""" "\" """)
    verify_string_bad(r""" '\' """)
    verify_string_bad(r""" "foo """)
    verify_string_bad(r""" 'foo """)


    print("Testing escape() and unescape()")

    def verify_escape_unescape(s, sesc):
        # Verify that 's' escapes to 'sesc' and that 'sesc' unescapes to 's'
        verify_equal(escape(s), sesc)
        verify_equal(unescape(sesc), s)

    verify_escape_unescape(r''          , r''              )
    verify_escape_unescape(r'foo'       , r'foo'           )
    verify_escape_unescape(r'"'         , r'\"'            )
    verify_escape_unescape(r'""'        , r'\"\"'          )
    verify_escape_unescape('\\'         , r'\\'            )
    verify_escape_unescape(r'\\'        , r'\\\\'          )
    verify_escape_unescape(r'\"'        , r'\\\"'          )
    verify_escape_unescape(r'"ab\cd"ef"', r'\"ab\\cd\"ef\"')

    # Backslashes before any character should be unescaped, not just before "
    # and \
    verify_equal(unescape(r"\afoo\b\c\\d\\\e\\\\f"), r"afoobc\d\e\\f")


    print("Testing _ordered_unique()")

    verify_equal(_ordered_unique([]), [])
    verify_equal(_ordered_unique([1]), [1])
    verify_equal(_ordered_unique([1, 2]), [1, 2])
    verify_equal(_ordered_unique([1, 1]), [1])
    verify_equal(_ordered_unique([1, 1, 2]), [1, 2])
    verify_equal(_ordered_unique([1, 2, 1]), [1, 2])
    verify_equal(_ordered_unique([1, 2, 2]), [1, 2])
    verify_equal(_ordered_unique([1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 1, 0]),
                                 [1, 2, 3, 4, 0])


    print("Testing expression evaluation")

    c = Kconfig("Kconfiglib/tests/Keval", warn=False)

    def verify_eval(expr, val):
        res = c.eval_string(expr)
        verify(res == val,
               "'{}' evaluated to {}, expected {}".format(expr, res, val))

    # No modules
    verify_eval("n", 0)
    verify_eval("m", 0)
    verify_eval("y", 2)
    verify_eval("'n'", 0)
    verify_eval("'m'", 0)
    verify_eval("'y'", 2)
    verify_eval("M", 2)

    # Modules
    c.modules.set_value(2)
    verify_eval("n", 0)
    verify_eval("m", 1)
    verify_eval("y", 2)
    verify_eval("'n'", 0)
    verify_eval("'m'", 1)
    verify_eval("'y'", 2)
    verify_eval("M", 1)
    verify_eval("(Y || N) && (m && y)", 1)

    # Non-bool/non-tristate symbols are always n in a tristate sense
    verify_eval("Y_STRING", 0)
    verify_eval("Y_STRING || m", 1)

    # As are all constants besides y and m
    verify_eval('"foo"', 0)
    verify_eval('"foo" || "bar"', 0)
    verify_eval('"foo" || m', 1)

    # Test equality for symbols

    verify_eval("N = N", 2)
    verify_eval("N = n", 2)
    verify_eval("N = 'n'", 2)
    verify_eval("N != N", 0)
    verify_eval("N != n", 0)
    verify_eval("N != 'n'", 0)

    verify_eval("M = M", 2)
    verify_eval("M = m", 2)
    verify_eval("M = 'm'", 2)
    verify_eval("M != M", 0)
    verify_eval("M != m", 0)
    verify_eval("M != 'm'", 0)

    verify_eval("Y = Y", 2)
    verify_eval("Y = y", 2)
    verify_eval("Y = 'y'", 2)
    verify_eval("Y != Y", 0)
    verify_eval("Y != y", 0)
    verify_eval("Y != 'y'", 0)

    verify_eval("N != M", 2)
    verify_eval("N != Y", 2)
    verify_eval("M != Y", 2)

    verify_eval("Y_STRING = y", 2)
    verify_eval("Y_STRING = 'y'", 2)
    verify_eval('FOO_BAR_STRING = "foo bar"', 2)
    verify_eval('FOO_BAR_STRING != "foo bar baz"', 2)
    verify_eval('INT_37 = 37', 2)
    verify_eval("INT_37 = '37'", 2)
    verify_eval('HEX_0X37 = 0x37', 2)
    verify_eval("HEX_0X37 = '0x37'", 2)

    # These should also hold after 31847b67 (kconfig: allow use of relations
    # other than (in)equality)
    verify_eval("HEX_0X37 = '0x037'", 2)
    verify_eval("HEX_0X37 = '0x0037'", 2)

    # Constant symbol comparisons
    verify_eval('"foo" != "bar"', 2)
    verify_eval('"foo" = "bar"', 0)
    verify_eval('"foo" = "foo"', 2)

    # Undefined symbols get their name as their value
    c.warn = False
    verify_eval("'not_defined' = not_defined", 2)
    verify_eval("not_defined_2 = not_defined_2", 2)
    verify_eval("not_defined_1 != not_defined_2", 2)

    # Test less than/greater than

    # Basic evaluation
    verify_eval("INT_37 < 38", 2)
    verify_eval("38 < INT_37", 0)
    verify_eval("INT_37 < '38'", 2)
    verify_eval("'38' < INT_37", 0)
    verify_eval("INT_37 < 138", 2)
    verify_eval("138 < INT_37", 0)
    verify_eval("INT_37 < '138'", 2)
    verify_eval("'138' < INT_37", 0)
    verify_eval("INT_37 < -138", 0)
    verify_eval("-138 < INT_37", 2)
    verify_eval("INT_37 < '-138'", 0)
    verify_eval("'-138' < INT_37", 2)
    verify_eval("INT_37 < 37", 0)
    verify_eval("37 < INT_37", 0)
    verify_eval("INT_37 < 36", 0)
    verify_eval("36 < INT_37", 2)

    # Different formats in comparison
    verify_eval("INT_37 < 0x26", 2) # 38
    verify_eval("INT_37 < 0x25", 0) # 37
    verify_eval("INT_37 < 0x24", 0) # 36
    verify_eval("HEX_0X37 < 56", 2) # 0x38
    verify_eval("HEX_0X37 < 55", 0) # 0x37
    verify_eval("HEX_0X37 < 54", 0) # 0x36

    # Other int comparisons
    verify_eval("INT_37 <= 38", 2)
    verify_eval("INT_37 <= 37", 2)
    verify_eval("INT_37 <= 36", 0)
    verify_eval("INT_37 >  38", 0)
    verify_eval("INT_37 >  37", 0)
    verify_eval("INT_37 >  36", 2)
    verify_eval("INT_37 >= 38", 0)
    verify_eval("INT_37 >= 37", 2)
    verify_eval("INT_37 >= 36", 2)

    # Other hex comparisons
    verify_eval("HEX_0X37 <= 0x38", 2)
    verify_eval("HEX_0X37 <= 0x37", 2)
    verify_eval("HEX_0X37 <= 0x36", 0)
    verify_eval("HEX_0X37 >  0x38", 0)
    verify_eval("HEX_0X37 >  0x37", 0)
    verify_eval("HEX_0X37 >  0x36", 2)
    verify_eval("HEX_0X37 >= 0x38", 0)
    verify_eval("HEX_0X37 >= 0x37", 2)
    verify_eval("HEX_0X37 >= 0x36", 2)

    # A hex holding a value without a "0x" prefix should still be treated as
    # hexadecimal
    verify_eval("HEX_37 < 0x38", 2)
    verify_eval("HEX_37 < 0x37", 0)
    verify_eval("HEX_37 < 0x36", 0)

    # Symbol comparisons
    verify_eval("INT_37   <  HEX_0X37", 2)
    verify_eval("INT_37   >  HEX_0X37", 0)
    verify_eval("HEX_0X37 <  INT_37  ", 0)
    verify_eval("HEX_0X37 >  INT_37  ", 2)
    verify_eval("INT_37   <  INT_37  ", 0)
    verify_eval("INT_37   <= INT_37  ", 2)
    verify_eval("INT_37   >  INT_37  ", 0)
    verify_eval("INT_37   <= INT_37  ", 2)

    # Tristate value comparisons
    verify_eval("n < n", 0)
    verify_eval("n < m", 2)
    verify_eval("n < y", 2)
    verify_eval("n < N", 0)
    verify_eval("n < M", 2)
    verify_eval("n < Y", 2)
    verify_eval("0 > n", 0)
    verify_eval("1 > n", 2)
    verify_eval("2 > n", 2)
    verify_eval("m < n", 0)
    verify_eval("m < m", 0)
    verify_eval("m < y", 2)

    # Strings compare lexicographically
    verify_eval("'aa' < 'ab'", 2)
    verify_eval("'aa' > 'ab'", 0)
    verify_eval("'ab' < 'aa'", 0)
    verify_eval("'ab' > 'aa'", 2)

    # Comparisons where one of the operands doesn't parse as a number also give
    # a lexicographic comparison
    verify_eval("INT_37 <  '37a' ", 2)
    verify_eval("'37a'  >  INT_37", 2)
    verify_eval("INT_37 <= '37a' ", 2)
    verify_eval("'37a'  >= INT_37", 2)
    verify_eval("INT_37 >= '37a' ", 0)
    verify_eval("INT_37 >  '37a' ", 0)
    verify_eval("'37a'  <  INT_37", 0)
    verify_eval("'37a'  <= INT_37", 0)

    def verify_eval_bad(expr):
        try:
            c.eval_string(expr)
        except KconfigError:
            pass
        else:
            fail('expected eval_string("{}") to throw KconfigError, '
                 "didn't".format(expr))

    # Verify that some bad stuff throws KconfigError's
    verify_eval_bad("")
    verify_eval_bad("&")
    verify_eval_bad("|")
    verify_eval_bad("!")
    verify_eval_bad("(")
    verify_eval_bad(")")
    verify_eval_bad("=")
    verify_eval_bad("(X")
    verify_eval_bad("X)")
    verify_eval_bad("X X")
    verify_eval_bad("!X X")
    verify_eval_bad("X !X")
    verify_eval_bad("(X) X")
    verify_eval_bad("X &&")
    verify_eval_bad("&& X")
    verify_eval_bad("X && && X")
    verify_eval_bad("X && !&&")
    verify_eval_bad("X ||")
    verify_eval_bad("|| X")


    print("Testing Symbol.__str__()/custom_str() and def_{int,hex,string}")

    def verify_str(item, s):
        verify_equal(str(item), s[1:-1])

    def verify_custom_str(item, s):
        verify_equal(item.custom_str(lambda sc: "[{}]".format(sc.name)),
                     s[1:-1])

    c = Kconfig("Kconfiglib/tests/Kstr", warn=False)

    c.modules.set_value(2)

    verify_str(c.syms["UNDEFINED"], """
""")

    verify_str(c.syms["BASIC_NO_PROMPT"], """
config BASIC_NO_PROMPT
	bool
	help
	  blah blah
	  
	    blah blah blah
	  
	   blah
""")

    verify_str(c.syms["BASIC_PROMPT"], """
config BASIC_PROMPT
	bool "basic"
""")

    verify_str(c.syms["ADVANCED"], """
config ADVANCED
	tristate "prompt" if DEP
	default DEFAULT_1
	default DEFAULT_2 if DEP
	select SELECTED_1
	select SELECTED_2 if DEP
	imply IMPLIED_1
	imply IMPLIED_2 if DEP
	help
	  first help text

config ADVANCED
	tristate "prompt 2"

menuconfig ADVANCED
	tristate "prompt 3"

config ADVANCED
	tristate
	depends on (A || !B || (C && D) || !(E && F) || G = H || (I && !J && (K || L) && !(M || N) && O = P)) && DEP4 && DEP3
	help
	  second help text

config ADVANCED
	tristate "prompt 4" if VIS
	depends on DEP4 && DEP3
""")

    verify_custom_str(c.syms["ADVANCED"], """
config ADVANCED
	tristate "prompt" if [DEP]
	default [DEFAULT_1]
	default [DEFAULT_2] if [DEP]
	select [SELECTED_1]
	select [SELECTED_2] if [DEP]
	imply [IMPLIED_1]
	imply [IMPLIED_2] if [DEP]
	help
	  first help text

config ADVANCED
	tristate "prompt 2"

menuconfig ADVANCED
	tristate "prompt 3"

config ADVANCED
	tristate
	depends on ([A] || ![B] || ([C] && [D]) || !([E] && [F]) || [G] = [H] || ([I] && ![J] && ([K] || [L]) && !([M] || [N]) && [O] = [P])) && [DEP4] && [DEP3]
	help
	  second help text

config ADVANCED
	tristate "prompt 4" if [VIS]
	depends on [DEP4] && [DEP3]
""")


    verify_str(c.syms["ONLY_DIRECT_DEPS"], """
config ONLY_DIRECT_DEPS
	int
	depends on DEP1 && DEP2
""")

    verify_str(c.syms["STRING"], """
config STRING
	string
	default "foo"
	default "bar" if DEP
	default STRING2
	default STRING3 if DEP
""")

    verify_str(c.syms["INT"], """
config INT
	int
	range 1 2
	range FOO BAR
	range BAZ QAZ if DEP
	default 7 if DEP
""")

    verify_str(c.syms["HEX"], """
config HEX
	hex
	range 0x100 0x200
	range FOO BAR
	range BAZ QAZ if DEP
	default 0x123
""")

    verify_str(c.modules, """
config MODULES
	bool "MODULES"
	option modules
""")

    verify_str(c.syms["OPTIONS"], """
config OPTIONS
	option allnoconfig_y
	option defconfig_list
	option env="ENV"
""")

    verify_str(c.syms["CORRECT_PROP_LOCS_BOOL"], """
config CORRECT_PROP_LOCS_BOOL
	bool "prompt 1"
	default DEFAULT_1
	default DEFAULT_2
	select SELECT_1
	select SELECT_2
	imply IMPLY_1
	imply IMPLY_2
	depends on LOC_1
	help
	  help 1

menuconfig CORRECT_PROP_LOCS_BOOL
	bool "prompt 2"
	default DEFAULT_3
	default DEFAULT_4
	select SELECT_3
	select SELECT_4
	imply IMPLY_3
	imply IMPLY_4
	depends on LOC_2
	help
	  help 2

config CORRECT_PROP_LOCS_BOOL
	bool "prompt 3"
	default DEFAULT_5
	default DEFAULT_6
	select SELECT_5
	select SELECT_6
	imply IMPLY_5
	imply IMPLY_6
	depends on LOC_3
	help
	  help 2
""")

    verify_str(c.syms["CORRECT_PROP_LOCS_INT"], """
config CORRECT_PROP_LOCS_INT
	int
	range 1 2
	range 3 4
	depends on LOC_1

config CORRECT_PROP_LOCS_INT
	int
	range 5 6
	range 7 8
	depends on LOC_2
""")

    verify_str(c.syms["PROMPT_ONLY"], """
config PROMPT_ONLY
	prompt "prompt only"
""")

    verify_custom_str(c.syms["CORRECT_PROP_LOCS_INT"], """
config CORRECT_PROP_LOCS_INT
	int
	range [1] [2]
	range [3] [4]
	depends on [LOC_1]

config CORRECT_PROP_LOCS_INT
	int
	range [5] [6]
	range [7] [8]
	depends on [LOC_2]
""")



    print("Testing Choice.__str__()/custom_str()")

    verify_str(c.named_choices["CHOICE"], """
choice CHOICE
	tristate "foo"
	default CHOICE_1
	default CHOICE_2 if dep
""")

    verify_str(c.named_choices["CHOICE"].nodes[0].next.item, """
choice
	tristate "no name"
	optional
""")

    verify_str(c.named_choices["CORRECT_PROP_LOCS_CHOICE"], """
choice CORRECT_PROP_LOCS_CHOICE
	bool
	default CHOICE_3
	depends on LOC_1

choice CORRECT_PROP_LOCS_CHOICE
	bool
	default CHOICE_4
	depends on LOC_2

choice CORRECT_PROP_LOCS_CHOICE
	bool
	default CHOICE_5
	depends on LOC_3
""")

    verify_custom_str(c.named_choices["CORRECT_PROP_LOCS_CHOICE"], """
choice CORRECT_PROP_LOCS_CHOICE
	bool
	default [CHOICE_3]
	depends on [LOC_1]

choice CORRECT_PROP_LOCS_CHOICE
	bool
	default [CHOICE_4]
	depends on [LOC_2]

choice CORRECT_PROP_LOCS_CHOICE
	bool
	default [CHOICE_5]
	depends on [LOC_3]
""")


    print("Testing MenuNode.__str__()/custom_str() for menus and comments")

    verify_str(c.syms["SIMPLE_MENU_HOOK"].nodes[0].next, """
menu "simple menu"
""")

    verify_str(c.syms["ADVANCED_MENU_HOOK"].nodes[0].next, """
menu "advanced menu"
	depends on A
	visible if B && (C || D)
""")

    verify_custom_str(c.syms["ADVANCED_MENU_HOOK"].nodes[0].next, """
menu "advanced menu"
	depends on [A]
	visible if [B] && ([C] || [D])
""")

    verify_str(c.syms["SIMPLE_COMMENT_HOOK"].nodes[0].next, """
comment "simple comment"
""")

    verify_str(c.syms["ADVANCED_COMMENT_HOOK"].nodes[0].next, """
comment "advanced comment"
	depends on A && B
""")

    verify_custom_str(c.syms["ADVANCED_COMMENT_HOOK"].nodes[0].next, """
comment "advanced comment"
	depends on [A] && [B]
""")


    print("Testing {MenuNode,Symbol,Choice}.orig_*")

    # Just test some corner cases here re. MenuNode.orig_*. They are already
    # indirectly tested above. Use MenuNode.__str__() as a proxy.

    verify_str(c.syms["DEP_REM_CORNER_CASES"], """
config DEP_REM_CORNER_CASES
	bool
	default A
	depends on n

config DEP_REM_CORNER_CASES
	bool
	default B if n

config DEP_REM_CORNER_CASES
	bool
	default C
	depends on m && MODULES

config DEP_REM_CORNER_CASES
	bool
	default D if A

config DEP_REM_CORNER_CASES
	bool
	default E if !E1
	default F if F1 = F2
	default G if G1 || H1
	depends on !H

config DEP_REM_CORNER_CASES
	bool
	default H
	depends on "foo" = "bar"

config DEP_REM_CORNER_CASES
	bool "prompt" if FOO || BAR
	depends on BAZ && QAZ
""")

    # Test {Symbol,Choice}.orig_*

    def verify_deps(elms, dep_index, expected):
        verify_equal(" ".join(expr_str(elm[dep_index]) for elm in elms),
                     expected)

    verify_deps(c.syms["BOOL_SYM_ORIG"].orig_defaults,        1, "DEP y y")
    verify_deps(c.syms["BOOL_SYM_ORIG"].orig_selects,         1, "y DEP y")
    verify_deps(c.syms["BOOL_SYM_ORIG"].orig_implies,         1, "y y DEP")
    verify_deps(c.syms["INT_SYM_ORIG"].orig_ranges,           2, "DEP y DEP")
    verify_deps(c.named_choices["CHOICE_ORIG"].orig_defaults, 1, "y DEP DEP")


    print("Testing Symbol.__repr__()")

    def verify_repr(item, s):
        verify_equal(repr(item) + "\n", s[1:])

    c = Kconfig("Kconfiglib/tests/Krepr", warn=False)

    verify_repr(c.n, """
<symbol n, tristate, value n, constant>
""")

    verify_repr(c.m, """
<symbol m, tristate, value m, constant>
""")

    verify_repr(c.y, """
<symbol y, tristate, value y, constant>
""")

    verify_repr(c.syms["UNDEFINED"], """
<symbol UNDEFINED, unknown, value "UNDEFINED", visibility n, direct deps n, undefined>
""")

    verify_repr(c.syms["BASIC"], """
<symbol BASIC, bool, value y, visibility n, direct deps y, Kconfiglib/tests/Krepr:9>
""")

    verify_repr(c.syms["VISIBLE"], """
<symbol VISIBLE, bool, "visible", value n, visibility y, direct deps y, Kconfiglib/tests/Krepr:14>
""")

    c.syms["VISIBLE"].set_value(2)
    c.syms["STRING"].set_value("foo")

    verify_repr(c.syms["VISIBLE"], """
<symbol VISIBLE, bool, "visible", value y, user value y, visibility y, direct deps y, Kconfiglib/tests/Krepr:14>
""")

    verify_repr(c.syms["STRING"], """
<symbol STRING, string, "visible", value "foo", user value "foo", visibility y, direct deps y, Kconfiglib/tests/Krepr:17>
""")

    verify_repr(c.syms["DIR_DEP_N"], """
<symbol DIR_DEP_N, unknown, value "DIR_DEP_N", visibility n, direct deps n, Kconfiglib/tests/Krepr:20>
""")

    verify_repr(c.syms["OPTIONS"], """
<symbol OPTIONS, unknown, value "OPTIONS", visibility n, allnoconfig_y, is the defconfig_list symbol, from environment variable ENV, direct deps y, Kconfiglib/tests/Krepr:23>
""")

    verify_repr(c.syms["MULTI_DEF"], """
<symbol MULTI_DEF, unknown, value "MULTI_DEF", visibility n, direct deps y, Kconfiglib/tests/Krepr:28, Kconfiglib/tests/Krepr:29>
""")

    verify_repr(c.syms["CHOICE_1"], """
<symbol CHOICE_1, tristate, "choice sym", value n, visibility m, choice symbol, direct deps m, Kconfiglib/tests/Krepr:36>
""")

    verify_repr(c.modules, """
<symbol MODULES, bool, value y, visibility n, is the modules symbol, direct deps y, Kconfiglib/tests/Krepr:1>
""")


    print("Testing Choice.__repr__()")

    verify_repr(c.named_choices["CHOICE"], """
<choice CHOICE, tristate, "choice", mode m, visibility y, Kconfiglib/tests/Krepr:33>
""")

    c.named_choices["CHOICE"].set_value(2)

    verify_repr(c.named_choices["CHOICE"], """
<choice CHOICE, tristate, "choice", mode y, user mode y, CHOICE_1 selected, visibility y, Kconfiglib/tests/Krepr:33>
""")

    c.syms["CHOICE_2"].set_value(2)

    verify_repr(c.named_choices["CHOICE"], """
<choice CHOICE, tristate, "choice", mode y, user mode y, CHOICE_2 selected, CHOICE_2 selected by user, visibility y, Kconfiglib/tests/Krepr:33>
""")

    c.named_choices["CHOICE"].set_value(1)

    verify_repr(c.named_choices["CHOICE"], """
<choice CHOICE, tristate, "choice", mode m, user mode m, CHOICE_2 selected by user (overridden), visibility y, Kconfiglib/tests/Krepr:33>
""")

    verify_repr(c.syms["CHOICE_HOOK"].nodes[0].next.item, """
<choice, tristate, "optional choice", mode n, visibility n, optional, Kconfiglib/tests/Krepr:46>
""")


    print("Testing MenuNode.__repr__()")

    verify_repr(c.syms["BASIC"].nodes[0], """
<menu node for symbol BASIC, deps y, has help, has next, Kconfiglib/tests/Krepr:9>
""")

    verify_repr(c.syms["DIR_DEP_N"].nodes[0], """
<menu node for symbol DIR_DEP_N, deps n, has next, Kconfiglib/tests/Krepr:20>
""")

    verify_repr(c.syms["MULTI_DEF"].nodes[0], """
<menu node for symbol MULTI_DEF, deps y, has next, Kconfiglib/tests/Krepr:28>
""")

    verify_repr(c.syms["MULTI_DEF"].nodes[1], """
<menu node for symbol MULTI_DEF, deps y, has next, Kconfiglib/tests/Krepr:29>
""")

    verify_repr(c.syms["MENUCONFIG"].nodes[0], """
<menu node for symbol MENUCONFIG, is menuconfig, deps y, has next, Kconfiglib/tests/Krepr:31>
""")

    verify_repr(c.named_choices["CHOICE"].nodes[0], """
<menu node for choice CHOICE, prompt "choice" (visibility y), deps y, has child, has next, Kconfiglib/tests/Krepr:33>
""")

    verify_repr(c.syms["CHOICE_HOOK"].nodes[0].next, """
<menu node for choice, prompt "optional choice" (visibility n), deps y, has next, Kconfiglib/tests/Krepr:46>
""")

    verify_repr(c.syms["NO_VISIBLE_IF_HOOK"].nodes[0].next, """
<menu node for menu, prompt "no visible if" (visibility y), deps y, 'visible if' deps y, has next, Kconfiglib/tests/Krepr:53>
""")

    verify_repr(c.syms["VISIBLE_IF_HOOK"].nodes[0].next, """
<menu node for menu, prompt "visible if" (visibility y), deps y, 'visible if' deps m, has next, Kconfiglib/tests/Krepr:58>
""")

    verify_repr(c.syms["COMMENT_HOOK"].nodes[0].next, """
<menu node for comment, prompt "comment" (visibility y), deps y, Kconfiglib/tests/Krepr:64>
""")


    print("Testing Kconfig.__repr__()")

    verify_repr(c, """
<configuration with 15 symbols, main menu prompt "Main menu", srctree is current directory, config symbol prefix "CONFIG_", warnings disabled, printing of warnings to stderr enabled, undef. symbol assignment warnings disabled, overriding symbol assignment warnings enabled, redundant symbol assignment warnings enabled>
""")

    os.environ["srctree"] = "Kconfiglib"
    os.environ["CONFIG_"] = "CONFIG_ value"

    c = Kconfig("tests/Krepr", warn=False)
    c.warn = True
    c.warn_to_stderr = False
    c.warn_assign_override = False
    c.warn_assign_redun = False
    c.warn_assign_undef = True

    verify_repr(c, """
<configuration with 15 symbols, main menu prompt "Main menu", srctree "Kconfiglib", config symbol prefix "CONFIG_ value", warnings enabled, printing of warnings to stderr disabled, undef. symbol assignment warnings enabled, overriding symbol assignment warnings disabled, redundant symbol assignment warnings disabled>
""")

    os.environ.pop("srctree", None)
    os.environ.pop("CONFIG_", None)


    print("Testing tricky help strings")

    c = Kconfig("Kconfiglib/tests/Khelp")

    def verify_help(node, s):
        verify_equal(node.help, s[1:-1])

    verify_help(c.syms["TWO_HELP_STRINGS"].nodes[0], """
first help string
""")

    verify_help(c.syms["TWO_HELP_STRINGS"].nodes[1], """
second help string
""")

    verify_help(c.syms["NO_BLANK_AFTER_HELP"].nodes[0], """
help for
NO_BLANK_AFTER_HELP
""")

    verify_help(c.named_choices["CHOICE_HELP"].nodes[0], """
help for
CHOICE_HELP
""")

    verify_help(c.syms["HELP_TERMINATED_BY_COMMENT"].nodes[0], """
a
b
c
""")

    verify_help(c.syms["TRICKY_HELP"].nodes[0], """
a
 b
  c

 d
  e
   f


g
 h
  i
""")


    print("Testing locations, source/rsource/gsource/grsource, and "
          "Kconfig.kconfig_filenames")

    def verify_locations(nodes, *expected_locs):
        verify(len(nodes) == len(expected_locs),
               "Wrong number of locations for " + repr(nodes))

        for node, expected_loc in zip(nodes, expected_locs):
            node_loc = "{}:{}".format(node.filename, node.linenr)
            verify(node_loc == expected_loc,
                   "expected {} to have the location {}, had the location {}"
                   .format(repr(node), expected_loc, node_loc))

    # Expanded in the 'source' statement in Klocation

    os.environ["TESTS_DIR_FROM_ENV"] = "tests"
    os.environ["SUB_DIR_FROM_ENV"] = "sub"

    os.environ["_SOURCED"] = "_sourced"
    os.environ["_RSOURCED"] = "_rsourced"
    os.environ["_GSOURCED"] = "_gsourced"
    os.environ["_GRSOURCED"] = "_grsourced"

    # Test twice, with $srctree as a relative and an absolute path,
    # respectively
    for srctree in "Kconfiglib", os.path.abspath("Kconfiglib"):
        os.environ["srctree"] = srctree

        # Has symbol with empty help text, so disable warnings
        c = Kconfig("tests/Klocation", warn=False)

        verify_locations(c.syms["UNDEFINED"].nodes)
        verify_equal(c.syms["UNDEFINED"].name_and_loc, "UNDEFINED (undefined)")

        verify_locations(c.syms["ONE_DEF"].nodes, "tests/Klocation:4")
        verify_equal(c.syms["ONE_DEF"].name_and_loc,
                     "ONE_DEF (defined at tests/Klocation:4)")

        verify_locations(c.syms["TWO_DEF"].nodes,
                         "tests/Klocation:7",
                         "tests/Klocation:10")
        verify_equal(c.syms["TWO_DEF"].name_and_loc,
                     "TWO_DEF (defined at tests/Klocation:7, tests/Klocation:10)")

        verify_locations(c.syms["MANY_DEF"].nodes,
                         "tests/Klocation:13",
                         "tests/Klocation:43",
                         "tests/Klocation:45",
                         "tests/Klocation_sourced:3",
                         "tests/sub/Klocation_rsourced:2",
                         "tests/sub/Klocation_gsourced1:1",
                         "tests/sub/Klocation_gsourced2:1",
                         "tests/sub/Klocation_gsourced1:1",
                         "tests/sub/Klocation_gsourced2:1",
                         "tests/sub/Klocation_grsourced1:1",
                         "tests/sub/Klocation_grsourced2:1",
                         "tests/sub/Klocation_grsourced1:1",
                         "tests/sub/Klocation_grsourced2:1",
                         "tests/Klocation:78")

        verify_locations(c.named_choices["CHOICE_ONE_DEF"].nodes,
                         "tests/Klocation_sourced:5")
        verify_equal(c.named_choices["CHOICE_ONE_DEF"].name_and_loc,
                     "<choice CHOICE_ONE_DEF> (defined at tests/Klocation_sourced:5)")

        verify_locations(c.named_choices["CHOICE_TWO_DEF"].nodes,
                         "tests/Klocation_sourced:9",
                         "tests/Klocation_sourced:13")
        verify_equal(c.named_choices["CHOICE_TWO_DEF"].name_and_loc,
                     "<choice CHOICE_TWO_DEF> (defined at tests/Klocation_sourced:9, tests/Klocation_sourced:13)")

        verify_locations([c.syms["MENU_HOOK"].nodes[0].next],
                         "tests/Klocation_sourced:20")

        verify_locations([c.syms["COMMENT_HOOK"].nodes[0].next],
                         "tests/Klocation_sourced:26")

        # Test Kconfig.kconfig_filenames

        verify_equal(c.kconfig_filenames, [
            "tests/Klocation",
            "tests/Klocation_sourced",
            "tests/sub/Klocation_rsourced",
            "tests/sub/Klocation_gsourced1",
            "tests/sub/Klocation_gsourced2",
            "tests/sub/Klocation_gsourced1",
            "tests/sub/Klocation_gsourced2",
            "tests/sub/Klocation_grsourced1",
            "tests/sub/Klocation_grsourced2",
            "tests/sub/Klocation_grsourced1",
            "tests/sub/Klocation_grsourced2"
        ])

        # Test recursive 'source' detection

        try:
            Kconfig("tests/Krecursive1")
        except KconfigError as e:
            verify_equal(str(e), """
tests/Krecursive2:1: recursive 'source' of 'tests/Krecursive1' detected. Check that environment variables are set correctly.
Include path:
tests/Krecursive1:1
tests/Krecursive2:1
"""[:-1])
        except:
            fail("recursive 'source' raised wrong exception")
        else:
            fail("recursive 'source' did not raise exception")

        # Verify that source and rsource throw exceptions for missing files

        # TODO: Make an exception test helper

        try:
            Kconfig("tests/Kmissingsource")
        except KconfigError as e:
            if "not found" not in str(e):
                fail("'source' with missing file raised wrong KconfigError")
        except:
            fail("'source' with missing file raised wrong exception")
        else:
            fail("'source' with missing file did not raise exception")

        try:
            Kconfig("tests/Kmissingrsource")
        except KconfigError as e:
            if "not found" not in str(e):
                fail("'rsource' with missing file raised wrong KconfigError")
        except:
            fail("'rsource' with missing file raised wrong exception")
        else:
            fail("'rsource' with missing file did not raise exception")

    # Test a tricky case involving symlinks. $srctree is tests/symlink, which
    # points to tests/sub/sub, meaning tests/symlink/.. != tests/. Previously,
    # using 'rsource' from a file sourced with an absolute path triggered an
    # unsafe relpath() with tests/symlink/.. in it, crashing.

    os.environ["srctree"] = "Kconfiglib/tests/symlink"
    os.environ["KCONFIG_SYMLINK_2"] = os.path.abspath(
        "Kconfiglib/tests/sub/Kconfig_symlink_2")
    if not os.path.isabs(
        Kconfig("Kconfig_symlink_1").syms["FOUNDME"].nodes[0].filename):

        fail("Symlink + rsource issues")


    print("Testing Kconfig.node_iter()")

    # Reuse tests/Klocation. The node_iter(unique_syms=True) case already gets
    # plenty of testing from write_config() as well.

    os.environ["srctree"] = "Kconfiglib"
    c = Kconfig("tests/Klocation", warn=False)

    verify_equal(
        [node.item.name for node in c.node_iter()
         if isinstance(node.item, Symbol)],
        ["ONE_DEF", "TWO_DEF", "TWO_DEF", "MANY_DEF", "HELP_1", "HELP_2",
         "HELP_3", "MANY_DEF", "MANY_DEF", "MANY_DEF", "MENU_HOOK",
         "COMMENT_HOOK"] + 10*["MANY_DEF"])

    verify_equal(
        [node.item.name for node in c.node_iter(True)
         if isinstance(node.item, Symbol)],
        ["ONE_DEF", "TWO_DEF", "MANY_DEF", "HELP_1", "HELP_2", "HELP_3",
         "MENU_HOOK", "COMMENT_HOOK"])

    verify_equal(
        [node.prompt[0] for node in c.node_iter()
         if not isinstance(node.item, Symbol)],
        ["one-def choice", "two-def choice 1", "two-def choice 2",
         "menu", "comment"])

    verify_equal(
        [node.prompt[0] for node in c.node_iter(True)
         if not isinstance(node.item, Symbol)],
        ["one-def choice", "two-def choice 1", "two-def choice 2",
         "menu", "comment"])


    print("Testing MenuNode.include_path")

    os.environ["srctree"] = "Kconfiglib/tests"

    c = Kconfig("Kinclude_path")

    def verify_node_path(node, *expected):
        if node.include_path != expected:
            fail("Wrong include path for node {!r}. Got {}, expected {}."
                 .format(node, node.include_path, expected))

    def verify_sym_path(sym_name, node_i, *expected):
        verify_node_path(c.syms[sym_name].nodes[node_i], *expected)

    verify_sym_path("TOP", 0)
    verify_sym_path("TOP", 1)
    verify_sym_path("TOP", 2)

    verify_sym_path("ONE_DOWN", 0, ("Kinclude_path", 4))
    verify_sym_path("ONE_DOWN", 1, ("Kinclude_path", 4))
    verify_sym_path("ONE_DOWN", 2, ("Kinclude_path", 4))
    verify_sym_path("ONE_DOWN", 3, ("Kinclude_path", 9))
    verify_sym_path("ONE_DOWN", 4, ("Kinclude_path", 9))
    verify_sym_path("ONE_DOWN", 5, ("Kinclude_path", 9))

    verify_sym_path("TWO_DOWN", 0,
                    ("Kinclude_path", 4), ("Kinclude_path_sourced_1", 4))
    verify_sym_path("TWO_DOWN", 1,
                    ("Kinclude_path", 4), ("Kinclude_path_sourced_1", 9))
    verify_sym_path("TWO_DOWN", 2,
                    ("Kinclude_path", 9), ("Kinclude_path_sourced_1", 4))
    verify_sym_path("TWO_DOWN", 3,
                    ("Kinclude_path", 9), ("Kinclude_path_sourced_1", 9))

    verify_node_path(c.top_node)
    verify_node_path(c.menus[0], ("Kinclude_path", 4), ("Kinclude_path_sourced_1", 4))
    verify_node_path(c.comments[0], ("Kinclude_path", 4), ("Kinclude_path_sourced_1", 4))
    verify_node_path(c.choices[0].nodes[0], ("Kinclude_path", 4), ("Kinclude_path_sourced_1", 4))

    os.environ.pop("srctree", None)


    print("Testing Kconfig.choices/menus/comments")

    c = Kconfig("Kconfiglib/tests/Kitemlists")

    def verify_prompts(items, *expected_prompts):
        verify(len(items) == len(expected_prompts),
               "Wrong number of prompts for {}".format(items))

        for item, expected_prompt in zip(items, expected_prompts):
            if not isinstance(item, MenuNode):
                item = item.nodes[0]

            verify(item.prompt[0] == expected_prompt,
                   "Wrong prompt for {}, expected '{}'"
                   .format(repr(item), expected_prompt))

    verify_prompts(c.choices, "choice 1", "choice 2", "choice 3", "choice 2")
    verify_prompts(c.menus, "menu 1", "menu 2", "menu 3", "menu 4", "menu 5")
    verify_prompts(c.comments, "comment 1", "comment 2", "comment 3")


    print("Testing Symbol/Choice.direct_dep")

    c = Kconfig("Kconfiglib/tests/Kdirdep")

    verify_equal(expr_str(c.syms["NO_DEP_SYM"].direct_dep), 'y')
    verify_equal(expr_str(c.syms["DEP_SYM"].direct_dep), "A || (B && C) || !D")

    verify_equal(expr_str(c.named_choices["NO_DEP_CHOICE"].direct_dep), 'y')
    verify_equal(expr_str(c.named_choices["DEP_CHOICE"].direct_dep),
                 "A || B || C")


    print("Testing expr_items()")

    c = Kconfig("Kconfiglib/tests/Kexpr_items")

    def verify_expr_items(expr, *sym_names):
        verify_equal(tuple(sorted(item.name for item in expr_items(expr))),
                     sym_names)

    verify_expr_items(
        c.syms["TEST"].defaults[0][0],
        "A", "B", "C", "D", "E", "F", "G", "H"
    )

    verify_expr_items(
        c.syms["TEST_CHOICE"].nodes[0].prompt[1],
        "A", "CHOICE"
    )


    print("Testing MenuNode/Symbol/Choice.referenced")

    c = Kconfig("Kconfiglib/tests/Kreferenced", warn=False)

    def verify_deps(item, *dep_names):
        verify_equal(tuple(sorted(item.name for item in item.referenced)),
                     dep_names)

    verify_deps(c.top_node, "y")

    verify_deps(c.syms["NO_REFS"].nodes[0], "y")

    verify_deps(c.syms["JUST_DEPENDS_ON_REFS"].nodes[0], "A", "B")

    verify_deps(c.syms["LOTS_OF_REFS"].nodes[0],
                *(chr(n) for n in range(ord("A"), ord("Z") + 1)))

    verify_deps(c.syms["INT_REFS"].nodes[0],
                "A", "B", "C", "D", "E", "F", "G", "H", "y")

    verify_deps(c.syms["CHOICE_REF"].nodes[0], "CHOICE")

    verify_deps(c.menus[0], "A", "B", "C", "D")

    verify_deps(c.comments[0], "A", "B")

    verify_deps(c.syms["MULTI_DEF_SYM"], "A", "B", "C", "y")
    verify_deps(c.named_choices["MULTI_DEF_CHOICE"], "A", "B", "C")


    print("Testing split_expr()")

    c = Kconfig("Kconfiglib/tests/empty")
    c.warn = False

    def verify_split(to_split, op, operand_strs):
        # The same hackage as in Kconfig.eval_string()
        c._tokens = c._tokenize("if " + to_split)[1:]
        c._tokens_i = 0

        operands = split_expr(c._parse_expr(False), op)

        verify(len(operands) == len(operand_strs),
               "Wrong number of operands when {} was split by {}"
               .format(to_split, "OR" if op == OR else "AND"))

        for operand, operand_str in zip(operands, operand_strs):
            verify_equal(expr_str(operand), operand_str)

    verify_split("A",                    OR, ("A",                ))
    verify_split("!A",                   OR, ("!A",               ))
    verify_split("A = B",                OR, ("A = B",            ))
    verify_split("A && B",               OR, ("A && B",           ))
    verify_split("A || B",               OR, ("A", "B"            ))
    verify_split("(A || B) || C",        OR, ("A", "B", "C"       ))
    verify_split("A || (B || C)",        OR, ("A", "B", "C"       ))
    verify_split("A || !(B || C)",       OR, ("A", "!(B || C)"    ))
    verify_split("A || (B && (C || D))", OR, ("A", "B && (C || D)"))
    verify_split("(A && (B || C)) || D", OR, ("A && (B || C)", "D"))

    verify_split("A",                    AND, ("A",                ))
    verify_split("!A",                   AND, ("!A",               ))
    verify_split("A = B",                AND, ("A = B",            ))
    verify_split("A || B",               AND, ("A || B",           ))
    verify_split("A && B",               AND, ("A", "B"            ))
    verify_split("(A && B) && C",        AND, ("A", "B", "C"       ))
    verify_split("A && (B && C)",        AND, ("A", "B", "C"       ))
    verify_split("A && !(B && C)",       AND, ("A", "!(B && C)"    ))
    verify_split("A && (B || (C && D))", AND, ("A", "B || (C && D)"))
    verify_split("(A || (B && C)) && D", AND, ("A || (B && C)", "D"))


    print("Testing visibility")

    c = Kconfig("Kconfiglib/tests/Kvisibility")

    def verify_visibility(item, no_module_vis, module_vis):
        c.modules.set_value(0)
        verify(item.visibility == no_module_vis,
               "expected {} to have visibility {} without modules, had "
               "visibility {}".
               format(repr(item), no_module_vis, item.visibility))

        c.modules.set_value(2)
        verify(item.visibility == module_vis,
               "expected {} to have visibility {} with modules, had "
               "visibility {}".
               format(repr(item), module_vis, item.visibility))

    # Symbol visibility

    verify_visibility(c.syms["NO_PROMPT"],     0, 0)
    verify_visibility(c.syms["BOOL_N"],        0, 0)
    verify_visibility(c.syms["BOOL_M"],        0, 2)
    verify_visibility(c.syms["BOOL_MOD"],      2, 2)
    verify_visibility(c.syms["BOOL_Y"],        2, 2)
    verify_visibility(c.syms["TRISTATE_M"],    0, 1)
    verify_visibility(c.syms["TRISTATE_MOD"],  2, 1)
    verify_visibility(c.syms["TRISTATE_Y"],    2, 2)
    verify_visibility(c.syms["BOOL_IF_N"],     0, 0)
    verify_visibility(c.syms["BOOL_IF_M"],     0, 2)
    verify_visibility(c.syms["BOOL_IF_Y"],     2, 2)
    verify_visibility(c.syms["BOOL_MENU_N"],   0, 0)
    verify_visibility(c.syms["BOOL_MENU_M"],   0, 2)
    verify_visibility(c.syms["BOOL_MENU_Y"],   2, 2)
    verify_visibility(c.syms["BOOL_CHOICE_N"], 0, 0)

    # Non-tristate symbols in tristate choices are only visible if the choice
    # is in y mode

    # The choice can't be brought to y mode because of the 'if m'
    verify_visibility(c.syms["BOOL_CHOICE_M"], 0, 0)
    c.syms["BOOL_CHOICE_M"].choice.set_value(2)
    verify_visibility(c.syms["BOOL_CHOICE_M"], 0, 0)

    # The choice gets y mode only when running without modules, because it
    # defaults to m mode
    verify_visibility(c.syms["BOOL_CHOICE_Y"], 2, 0)
    c.syms["BOOL_CHOICE_Y"].choice.set_value(2)
    # When set to y mode, the choice symbol becomes visible both with and
    # without modules
    verify_visibility(c.syms["BOOL_CHOICE_Y"], 2, 2)

    verify_visibility(c.syms["TRISTATE_IF_N"],     0, 0)
    verify_visibility(c.syms["TRISTATE_IF_M"],     0, 1)
    verify_visibility(c.syms["TRISTATE_IF_Y"],     2, 2)
    verify_visibility(c.syms["TRISTATE_MENU_N"],   0, 0)
    verify_visibility(c.syms["TRISTATE_MENU_M"],   0, 1)
    verify_visibility(c.syms["TRISTATE_MENU_Y"],   2, 2)
    verify_visibility(c.syms["TRISTATE_CHOICE_N"], 0, 0)
    verify_visibility(c.syms["TRISTATE_CHOICE_M"], 0, 1)
    verify_visibility(c.syms["TRISTATE_CHOICE_Y"], 2, 2)

    verify_visibility(c.named_choices["BOOL_CHOICE_N"],     0, 0)
    verify_visibility(c.named_choices["BOOL_CHOICE_M"],     0, 2)
    verify_visibility(c.named_choices["BOOL_CHOICE_Y"],     2, 2)
    verify_visibility(c.named_choices["TRISTATE_CHOICE_N"], 0, 0)
    verify_visibility(c.named_choices["TRISTATE_CHOICE_M"], 0, 1)
    verify_visibility(c.named_choices["TRISTATE_CHOICE_Y"], 2, 2)

    verify_visibility(c.named_choices["TRISTATE_CHOICE_IF_M_AND_Y"],   0, 1)
    verify_visibility(c.named_choices["TRISTATE_CHOICE_MENU_N_AND_Y"], 0, 0)

    # Verify that 'visible if' visibility gets propagated to prompts

    verify_visibility(c.syms["VISIBLE_IF_N"], 0, 0)
    verify_visibility(c.syms["VISIBLE_IF_M"], 0, 1)
    verify_visibility(c.syms["VISIBLE_IF_Y"], 2, 2)
    verify_visibility(c.syms["VISIBLE_IF_M_2"], 0, 1)

    # Verify that string/int/hex symbols with m visibility accept a user value

    assign_and_verify("STRING_m", "foo bar")
    assign_and_verify("INT_m", "123")
    assign_and_verify("HEX_m", "0x123")


    print("Testing .assignable")

    c = Kconfig("Kconfiglib/tests/Kassignable")

    def verify_assignable_imp(item, assignable_no_modules, assignable_modules):
        # Verifies the assignable values for 'item', with and without modules.

        for modules_val, assignable in (0, assignable_no_modules), \
                                       (2, assignable_modules):

            c.modules.set_value(modules_val)
            module_msg = "without modules" if modules_val == 0 else \
                         "with modules"

            verify(item.assignable == assignable,
                   "Incorrect assignable values for {} {}. Should be {}, "
                   "was {}."
                   .format(item.name, module_msg, assignable, item.assignable))

            # Verify that the values can actually be assigned too

            for val in item.assignable:
                item.set_value(val)
                verify(item.tri_value == val,
                       "Unable to set {} to {} {}, even though it was in "
                       ".assignable".format(item.name, val, module_msg))

    def verify_assignable(sym_name, assignable_no_modules, assignable_modules):
        verify_assignable_imp(c.syms[sym_name],
                              assignable_no_modules,
                              assignable_modules)

    def verify_const_unassignable(sym_name):
        verify_assignable_imp(c.const_syms[sym_name], (), ())

    # Things that shouldn't be .assignable
    verify_const_unassignable("n")
    verify_const_unassignable("m")
    verify_const_unassignable("y")
    verify_const_unassignable("const")
    verify_assignable("UNDEFINED", (), ())
    verify_assignable("NO_PROMPT", (), ())
    verify_assignable("STRING", (), ())
    verify_assignable("INT", (), ())
    verify_assignable("HEX", (), ())

    # Non-selected symbols
    verify_assignable("Y_VIS_BOOL", (0, 2), (0,    2))
    verify_assignable("M_VIS_BOOL", (    ), (0,    2))  # Vis. promoted
    verify_assignable("N_VIS_BOOL", (    ), (       ))
    verify_assignable("Y_VIS_TRI",  (0, 2), (0, 1, 2))
    verify_assignable("M_VIS_TRI",  (    ), (0, 1   ))
    verify_assignable("N_VIS_TRI",  (    ), (       ))

    # Symbols selected to y
    verify_assignable("Y_SEL_Y_VIS_BOOL", (2,), (2,))
    verify_assignable("Y_SEL_M_VIS_BOOL", (  ), (2,))  # Vis. promoted
    verify_assignable("Y_SEL_N_VIS_BOOL", (  ), (  ))
    verify_assignable("Y_SEL_Y_VIS_TRI",  (2,), (2,))
    verify_assignable("Y_SEL_M_VIS_TRI",  (  ), (2,))
    verify_assignable("Y_SEL_N_VIS_TRI",  (  ), (  ))

    # Symbols selected to m
    verify_assignable("M_SEL_Y_VIS_BOOL", (2,), (   2,))  # Value promoted
    verify_assignable("M_SEL_M_VIS_BOOL", (  ), (   2,))  # Vis./value promoted
    verify_assignable("M_SEL_N_VIS_BOOL", (  ), (     ))
    verify_assignable("M_SEL_Y_VIS_TRI",  (2,), (1, 2 ))
    verify_assignable("M_SEL_M_VIS_TRI",  (  ), (1,   ))
    verify_assignable("M_SEL_N_VIS_TRI",  (  ), (     ))

    # Symbols implied to y
    verify_assignable("Y_IMP_Y_VIS_BOOL", (0, 2), (0, 2))
    verify_assignable("Y_IMP_M_VIS_BOOL", (    ), (0, 2))  # Vis. promoted
    verify_assignable("Y_IMP_N_VIS_BOOL", (    ), (    ))
    verify_assignable("Y_IMP_Y_VIS_TRI",  (0, 2), (0, 2))  # m removed by imply
    verify_assignable("Y_IMP_M_VIS_TRI",  (    ), (0, 2))  # m promoted to y by imply
    verify_assignable("Y_IMP_N_VIS_TRI",  (    ), (    ))

    # Symbols implied to m (never affects assignable values)
    verify_assignable("M_IMP_Y_VIS_BOOL", (0, 2), (0,    2))
    verify_assignable("M_IMP_M_VIS_BOOL", (    ), (0,    2))  # Vis. promoted
    verify_assignable("M_IMP_N_VIS_BOOL", (    ), (       ))
    verify_assignable("M_IMP_Y_VIS_TRI",  (0, 2), (0, 1, 2))
    verify_assignable("M_IMP_M_VIS_TRI",  (    ), (0, 1   ))
    verify_assignable("M_IMP_N_VIS_TRI",  (    ), (       ))

    # Symbols in y-mode choice
    verify_assignable("Y_CHOICE_BOOL",           (2,), (2,))
    verify_assignable("Y_CHOICE_TRISTATE",       (2,), (2,))
    verify_assignable("Y_CHOICE_N_VIS_TRISTATE", (  ), (  ))

    # Symbols in m/y-mode choice, starting out in m mode, or y mode when
    # running without modules
    verify_assignable("MY_CHOICE_BOOL",           (2,), (    ))
    verify_assignable("MY_CHOICE_TRISTATE",       (2,), (0, 1))
    verify_assignable("MY_CHOICE_N_VIS_TRISTATE", (  ), (    ))

    c.named_choices["MY_CHOICE"].set_value(2)

    # Symbols in m/y-mode choice, now in y mode
    verify_assignable("MY_CHOICE_BOOL",           (2,), (2,))
    verify_assignable("MY_CHOICE_TRISTATE",       (2,), (2,))
    verify_assignable("MY_CHOICE_N_VIS_TRISTATE", (  ), (  ))

    def verify_choice_assignable(choice_name, assignable_no_modules,
                                 assignable_modules):
        verify_assignable_imp(c.named_choices[choice_name],
                              assignable_no_modules,
                              assignable_modules)

    # Choices with various possible modes
    verify_choice_assignable("Y_CHOICE",   (2,  ), (      2,))
    verify_choice_assignable("MY_CHOICE",  (2,  ), (   1, 2 ))
    verify_choice_assignable("NMY_CHOICE", (0, 2), (0, 1, 2 ))
    verify_choice_assignable("NY_CHOICE",  (0, 2), (0,    2 ))
    verify_choice_assignable("NM_CHOICE",  (    ), (0, 1    ))
    verify_choice_assignable("M_CHOICE",   (    ), (   1,   ))
    verify_choice_assignable("N_CHOICE",   (    ), (        ))


    print("Testing object relations")

    c = Kconfig("Kconfiglib/tests/Krelation")

    verify(c.syms["A"].nodes[0].parent is c.top_node,
           "A's parent should be the top node")

    verify(c.syms["B"].nodes[0].parent.item is c.named_choices["CHOICE_1"],
           "B's parent should be the first choice")

    verify(c.syms["C"].nodes[0].parent.item is c.syms["B"],
           "C's parent should be B (due to auto menus)")

    verify(c.syms["E"].nodes[0].parent.item == MENU,
           "E's parent should be a menu")

    verify(c.syms["E"].nodes[0].parent.parent is c.top_node,
           "E's grandparent should be the top node")

    verify(c.syms["G"].nodes[0].parent.item is c.named_choices["CHOICE_2"],
           "G's parent should be the second choice")

    verify(c.syms["G"].nodes[0].parent.parent.item == MENU,
           "G's grandparent should be a menu")


    print("Testing hex/int ranges")

    c = Kconfig("Kconfiglib/tests/Krange", warn=False)

    for sym_name in "HEX_NO_RANGE", "INT_NO_RANGE", "HEX_40", "INT_40":
        sym = c.syms[sym_name]
        verify(not sym.ranges,
               "{} should not have ranges".format(sym_name))

    for sym_name in "HEX_ALL_RANGES_DISABLED", "INT_ALL_RANGES_DISABLED", \
                    "HEX_RANGE_10_20_LOW_DEFAULT", \
                    "INT_RANGE_10_20_LOW_DEFAULT":
        sym = c.syms[sym_name]
        verify(sym.ranges, "{} should have ranges".format(sym_name))

    # hex/int symbols without defaults should get no default value
    verify_value("HEX_NO_RANGE", "")
    verify_value("INT_NO_RANGE", "")
    # And neither if all ranges are disabled
    verify_value("HEX_ALL_RANGES_DISABLED", "")
    verify_value("INT_ALL_RANGES_DISABLED", "")
    # Make sure they are assignable though, and test that the form of the user
    # value is reflected in the value for hex symbols
    assign_and_verify("HEX_NO_RANGE", "0x123")
    assign_and_verify("HEX_NO_RANGE", "123")
    assign_and_verify("INT_NO_RANGE", "123")

    # Defaults outside of the valid range should be clamped
    verify_value("HEX_RANGE_10_20_LOW_DEFAULT", "0x10")
    verify_value("HEX_RANGE_10_20_HIGH_DEFAULT", "0x20")
    verify_value("INT_RANGE_10_20_LOW_DEFAULT", "10")
    verify_value("INT_RANGE_10_20_HIGH_DEFAULT", "20")
    # Defaults inside the valid range should be preserved. For hex symbols,
    # they should additionally use the same form as in the assignment.
    verify_value("HEX_RANGE_10_20_OK_DEFAULT", "0x15")
    verify_value("HEX_RANGE_10_20_OK_DEFAULT_ALTERNATE", "15")
    verify_value("INT_RANGE_10_20_OK_DEFAULT", "15")

    # hex/int symbols with no defaults but valid ranges should default to the
    # lower end of the range if it's > 0
    verify_value("HEX_RANGE_10_20", "0x10")
    verify_value("HEX_RANGE_0_10", "")
    verify_value("INT_RANGE_10_20", "10")
    verify_value("INT_RANGE_0_10", "")
    verify_value("INT_RANGE_NEG_10_10", "")

    # User values and dependent ranges

    # Avoid warnings for assigning values outside the active range
    c.warn = False

    def verify_range(sym_name, low, high, default):
        # Verifies that all values in the range 'low'-'high' can be assigned,
        # and that assigning values outside the range reverts the value back to
        # 'default' (None if it should revert back to "").

        is_hex = (c.syms[sym_name].type == HEX)

        for i in range(low, high + 1):
            assign_and_verify_user_value(sym_name, str(i), str(i), True)
            if is_hex:
                # The form of the user value should be preserved for hex
                # symbols
                assign_and_verify_user_value(sym_name, hex(i), hex(i), True)

        # Verify that assigning a user value just outside the range causes
        # defaults to be used

        if default is None:
            default_str = ""
        else:
            default_str = hex(default) if is_hex else str(default)

        if is_hex:
            too_low_str = hex(low - 1)
            too_high_str = hex(high + 1)
        else:
            too_low_str = str(low - 1)
            too_high_str = str(high + 1)

        assign_and_verify_value(sym_name, too_low_str, default_str)
        assign_and_verify_value(sym_name, too_high_str, default_str)

    verify_range("HEX_RANGE_10_20_LOW_DEFAULT",  0x10, 0x20,  0x10)
    verify_range("HEX_RANGE_10_20_HIGH_DEFAULT", 0x10, 0x20,  0x20)
    verify_range("HEX_RANGE_10_20_OK_DEFAULT",   0x10, 0x20,  0x15)

    verify_range("INT_RANGE_10_20_LOW_DEFAULT",  10,   20,    10)
    verify_range("INT_RANGE_10_20_HIGH_DEFAULT", 10,   20,    20)
    verify_range("INT_RANGE_10_20_OK_DEFAULT",   10,   20,    15)

    verify_range("HEX_RANGE_10_20",              0x10, 0x20,  0x10)

    verify_range("INT_RANGE_10_20",              10,  20,     10)
    verify_range("INT_RANGE_0_10",               0,   10,     None)
    verify_range("INT_RANGE_NEG_10_10",          -10, 10,     None)

    # Dependent ranges

    verify_value("HEX_40", "40")
    verify_value("INT_40", "40")

    c.syms["HEX_RANGE_10_20"].unset_value()
    c.syms["INT_RANGE_10_20"].unset_value()
    verify_value("HEX_RANGE_10_40_DEPENDENT", "0x10")
    verify_value("INT_RANGE_10_40_DEPENDENT", "10")
    c.syms["HEX_RANGE_10_20"].set_value("15")
    c.syms["INT_RANGE_10_20"].set_value("15")
    verify_value("HEX_RANGE_10_40_DEPENDENT", "0x15")
    verify_value("INT_RANGE_10_40_DEPENDENT", "15")
    c.unset_values()
    verify_range("HEX_RANGE_10_40_DEPENDENT", 0x10, 0x40,  0x10)
    verify_range("INT_RANGE_10_40_DEPENDENT", 10,   40,    10)

    # Ranges and symbols defined in multiple locations

    verify_value("INACTIVE_RANGE", "2")
    verify_value("ACTIVE_RANGE", "1")


    print("Testing defconfig_filename")

    c = Kconfig("Kconfiglib/tests/empty")
    verify(c.defconfig_filename is None,
           "defconfig_filename should be None with no defconfig_list symbol")

    c = Kconfig("Kconfiglib/tests/Kdefconfig_nonexistent")
    verify(c.defconfig_filename is None,
           "defconfig_filename should be None when none of the files in the "
           "defconfig_list symbol exist")

    # Referenced in Kdefconfig_existent(_but_n)
    os.environ["FOO"] = "defconfig_2"

    c = Kconfig("Kconfiglib/tests/Kdefconfig_existent_but_n")
    verify(c.defconfig_filename is None,
           "defconfig_filename should be None when the condition is n for all "
           "the defaults")

    c = Kconfig("Kconfiglib/tests/Kdefconfig_existent")
    verify(c.defconfig_filename == "Kconfiglib/tests/defconfig_2",
           "defconfig_filename should return the existing file "
           "Kconfiglib/tests/defconfig_2")

    # Should also look relative to $srctree if the specified defconfig is a
    # relative path and can't be opened

    c = Kconfig("Kconfiglib/tests/Kdefconfig_srctree")
    verify(c.defconfig_filename == "Kconfiglib/tests/defconfig_2",
           "defconfig_filename gave wrong file with $srctree unset")

    os.environ["srctree"] = "Kconfiglib/tests"
    c = Kconfig("Kdefconfig_srctree")
    verify(c.defconfig_filename == "Kconfiglib/tests/sub/defconfig_in_sub",
           "defconfig_filename gave wrong file with $srctree set")

    os.environ.pop("srctree", None)


    print("Testing mainmenu_text")

    c = Kconfig("Kconfiglib/tests/empty")
    verify(c.mainmenu_text == "Main menu",
           "An empty Kconfig should get a default main menu prompt")

    # Expanded in the mainmenu text
    os.environ["FOO"] = "bar baz"
    c = Kconfig("Kconfiglib/tests/Kmainmenu")
    verify(c.mainmenu_text == "---bar baz---",
           "Wrong mainmenu text")


    print("Testing user_value")

    # References undefined env. var. Disable warnings.
    c = Kconfig("Kconfiglib/tests/Kmisc", warn=False)

    # Avoid warnings from assigning invalid user values and assigning user
    # values to symbols without prompts
    c.warn = False

    syms = [c.syms[name] for name in
            ("BOOL", "TRISTATE", "STRING", "INT", "HEX")]

    for sym in syms:
        verify(sym.user_value is None,
               "{} should not have a user value to begin with")

    # Assign valid values for the types

    assign_and_verify_user_value("BOOL", 0, 0, True)
    assign_and_verify_user_value("BOOL", 2, 2, True)
    assign_and_verify_user_value("TRISTATE", 0, 0, True)
    assign_and_verify_user_value("TRISTATE", 1, 1, True)
    assign_and_verify_user_value("TRISTATE", 2, 2, True)
    assign_and_verify_user_value("STRING", "foo bar", "foo bar", True)
    assign_and_verify_user_value("INT", "123", "123", True)
    assign_and_verify_user_value("HEX", "0x123", "0x123", True)

    # Assign invalid values for the types. They should retain their old user
    # value.

    assign_and_verify_user_value("BOOL", 1, 2, False)
    assign_and_verify_user_value("BOOL", "foo", 2, False)
    assign_and_verify_user_value("BOOL", "1", 2, False)
    assign_and_verify_user_value("TRISTATE", "foo", 2, False)
    assign_and_verify_user_value("TRISTATE", "1", 2, False)
    assign_and_verify_user_value("STRING", 0, "foo bar", False)
    assign_and_verify_user_value("INT", "foo", "123", False)
    assign_and_verify_user_value("INT", 0, "123", False)
    assign_and_verify_user_value("HEX", "foo", "0x123", False)
    assign_and_verify_user_value("HEX", 0, "0x123", False)
    assign_and_verify_user_value("HEX", "-0x1", "0x123", False)

    for s in syms:
        s.unset_value()
        verify(s.user_value is None,
               "{} should not have a user value after being reset".
               format(s.name))


    print("Testing is_menuconfig")

    c = Kconfig("Kconfiglib/tests/Kmenuconfig")

    for not_menuconfig in c.syms["NOT_MENUCONFIG_1"].nodes[0], \
                          c.syms["NOT_MENUCONFIG_2"].nodes[0], \
                          c.syms["MENUCONFIG_MULTI_DEF"].nodes[0], \
                          c.syms["COMMENT_HOOK"].nodes[0].next:

        verify(not not_menuconfig.is_menuconfig,
               "'{}' should have is_menuconfig False".format(not_menuconfig))

    for menuconfig in c.top_node, \
                      c.syms["MENUCONFIG_1"].nodes[0], \
                      c.syms["MENUCONFIG_MULTI_DEF"].nodes[1], \
                      c.syms["MENU_HOOK"].nodes[0].next, \
                      c.syms["CHOICE_HOOK"].nodes[0].next:

        verify(menuconfig.is_menuconfig,
               "'{}' should have is_menuconfig True".format(menuconfig))


    print("Testing 'option env' semantics")

    os.environ["ENV_VAR"] = "ENV_VAR value"

    # References undefined env. var., so disable warnings
    c = Kconfig("Kconfiglib/tests/Kmisc", warn=False)

    # Verify that 'option env' is treated like a default
    verify_value("FROM_ENV", "ENV_VAR value")
    verify_value("FROM_ENV_MISSING", "missing")

    verify_value("FROM_ENV_WEIRD", "weird")


    print("Testing defined vs undefined symbols")

    for name in "A", "B", "C", "D", "BOOL", "TRISTATE", "STRING", "INT", "HEX":
        verify(c.syms[name].nodes,
               "{} should be defined".format(name))

    for name in "NOT_DEFINED_1", "NOT_DEFINED_2", "NOT_DEFINED_3", \
                "NOT_DEFINED_4":
        sym = c.syms[name]
        verify(not c.syms[name].nodes,
               "{} should not be defined".format(name))


    print("Testing Symbol.choice")

    for name in "A", "B", "C", "D":
        verify(c.syms[name].choice is not None,
               "{} should be a choice symbol".format(name))

    for name in "Q1", "Q2", "Q3", "BOOL", "TRISTATE", "STRING", "INT", "HEX", \
                "FROM_ENV", "FROM_ENV_MISSING", "NOT_DEFINED_1", \
                "NOT_DEFINED_2", "NOT_DEFINED_3", "NOT_DEFINED_4":
        verify(c.syms[name].choice is None,
               "{} should not be a choice symbol".format(name))


    print("Testing is_allnoconfig_y")

    verify(not c.syms["NOT_ALLNOCONFIG_Y"].is_allnoconfig_y,
           "NOT_ALLNOCONFIG_Y should not be allnoconfig_y")
    verify(c.syms["ALLNOCONFIG_Y"].is_allnoconfig_y,
           "ALLNOCONFIG_Y should be allnoconfig_y")


    print("Testing .config reading and writing")

    config_test_file = "Kconfiglib/tests/config_test"

    def verify_file_contents(fname, contents):
        with open(fname, "r") as f:
            file_contents = f.read()
            verify(file_contents == contents,
                   "{} contains '{}'. Expected '{}'."
                   .format(fname, file_contents, contents))

    # Writing/reading strings with characters that need to be escaped

    c = Kconfig("Kconfiglib/tests/Kescape")

    # Test the default value
    c.write_config(config_test_file + "_from_def")
    verify_file_contents(config_test_file + "_from_def",
                         r'''CONFIG_STRING="\"\\"''' "\n")
    # Write our own value
    c.syms["STRING"].set_value(r'''\"a'\\''')
    c.write_config(config_test_file + "_from_user")
    verify_file_contents(config_test_file + "_from_user",
                         r'''CONFIG_STRING="\\\"a'\\\\"''' "\n")

    # Read back the two configs and verify the respective values
    c.load_config(config_test_file + "_from_def")
    verify_value("STRING", '"\\')
    c.load_config(config_test_file + "_from_user")
    verify_value("STRING", r'''\"a'\\''')

    # Appending values from a .config

    c = Kconfig("Kconfiglib/tests/Kappend")

    # Values before assigning
    verify_value("BOOL", "n")
    verify_value("STRING", "")

    # Assign BOOL
    c.load_config("Kconfiglib/tests/config_set_bool", replace=False)
    verify_value("BOOL", "y")
    verify_value("STRING", "")

    # Assign STRING
    c.load_config("Kconfiglib/tests/config_set_string", replace=False)
    verify_value("BOOL", "y")
    verify_value("STRING", "foo bar")

    # Reset BOOL
    c.load_config("Kconfiglib/tests/config_set_string")
    verify_value("BOOL", "n")
    verify_value("STRING", "foo bar")

    # Loading a completely empty .config should reset values
    c.load_config("Kconfiglib/tests/empty")
    verify_value("STRING", "")

    # An indented assignment in a .config should be ignored
    c.load_config("Kconfiglib/tests/config_indented")
    verify_value("IGNOREME", "y")

    # Symbol order in headers and minimal configuration files should match
    # definition order, like in .config files

    c = Kconfig("Kconfiglib/tests/Korder")

    c.write_autoconf(config_test_file)
    verify_file_contents(config_test_file, """
#define CONFIG_O 0
#define CONFIG_R 1
#define CONFIG_D 2
#define CONFIG_E 3
#define CONFIG_R2 4
#define CONFIG_I 5
#define CONFIG_N 6
#define CONFIG_G 7
"""[1:])

    # Differs from defaults
    c.syms["O"].set_value("-1")
    c.syms["R"].set_value("-1")
    c.syms["E"].set_value("-1")
    c.syms["R2"].set_value("-1")
    c.syms["N"].set_value("-1")
    c.syms["G"].set_value("-1")
    c.write_min_config(config_test_file)
    verify_file_contents(config_test_file, """
CONFIG_O=-1
CONFIG_R=-1
CONFIG_E=-1
CONFIG_R2=-1
CONFIG_N=-1
CONFIG_G=-1
"""[1:])

    # Test header strings in configuration files and headers

    os.environ["KCONFIG_CONFIG_HEADER"] = "config header from env.\n"
    os.environ["KCONFIG_AUTOHEADER_HEADER"] = "header header from env.\n"

    c = Kconfig("Kconfiglib/tests/Kheader")
    c.write_config(config_test_file, header="config header from param\n")
    verify_file_contents(config_test_file, """\
config header from param
CONFIG_FOO=y
""")
    c.write_min_config(config_test_file, header="min. config header from param\n")
    verify_file_contents(config_test_file, """\
min. config header from param
""")
    c.write_config(config_test_file)
    verify_file_contents(config_test_file, """\
config header from env.
CONFIG_FOO=y
""")
    c.write_min_config(config_test_file)
    verify_file_contents(config_test_file, """\
config header from env.
""")
    c.write_autoconf(config_test_file, header="header header from param\n")
    verify_file_contents(config_test_file, """\
header header from param
#define CONFIG_FOO 1
""")
    c.write_autoconf(config_test_file)
    verify_file_contents(config_test_file, """\
header header from env.
#define CONFIG_FOO 1
""")

    del os.environ["KCONFIG_CONFIG_HEADER"]
    del os.environ["KCONFIG_AUTOHEADER_HEADER"]


    print("Testing Kconfig fetching and separation")

    for c in Kconfig("Kconfiglib/tests/Kmisc", warn=False), \
             Kconfig("Kconfiglib/tests/Kmisc", warn=False):
        for item in c.syms["BOOL"], \
                    c.syms["BOOL"].nodes[0], \
                    c.named_choices["OPTIONAL"], \
                    c.named_choices["OPTIONAL"].nodes[0], \
                    c.syms["MENU_HOOK"].nodes[0].next, \
                    c.syms["COMMENT_HOOK"].nodes[0].next:
            verify(item.kconfig is c,
                   ".kconfig not properly set for " + repr(item))


    print("Testing imply semantics")

    c = Kconfig("Kconfiglib/tests/Kimply")

    verify_value("IMPLY_DIRECT_DEPS", "y")
    verify_value("UNMET_DIRECT_1", "n")
    verify_value("UNMET_DIRECT_2", "n")
    verify_value("UNMET_DIRECT_3", "n")
    verify_value("MET_DIRECT_1", "y")
    verify_value("MET_DIRECT_2", "y")
    verify_value("MET_DIRECT_3", "y")
    verify_value("MET_DIRECT_4", "y")

    verify_value("IMPLY_COND", "y")
    verify_value("IMPLIED_N_COND", "n")
    verify_value("IMPLIED_M_COND", "m")
    verify_value("IMPLIED_Y_COND", "y")

    verify_value("IMPLY_N_1", "n")
    verify_value("IMPLY_N_2", "n")
    verify_value("IMPLIED_FROM_N_1", "n")
    verify_value("IMPLIED_FROM_N_2", "n")

    verify_value("IMPLY_M", "m")
    verify_value("IMPLIED_M", "m")
    verify_value("IMPLIED_M_BOOL", "y")

    verify_value("IMPLY_M_TO_Y", "y")
    verify_value("IMPLIED_M_TO_Y", "y")

    # Test user value semantics

    # Verify that IMPLIED_TRISTATE is invalidated if the direct
    # dependencies change

    assign_and_verify("IMPLY", 2)
    assign_and_verify("DIRECT_DEP", 2)
    verify_value("IMPLIED_TRISTATE", 2)
    assign_and_verify("DIRECT_DEP", 0)
    verify_value("IMPLIED_TRISTATE", 0)
    # Set back for later tests
    assign_and_verify("DIRECT_DEP", 2)

    # Verify that IMPLIED_TRISTATE can be set to anything when IMPLY has value
    # n, and that it gets the value n by default (for non-imply-related
    # reasons)

    assign_and_verify("IMPLY", 0)
    assign_and_verify("IMPLIED_TRISTATE", 0)
    assign_and_verify("IMPLIED_TRISTATE", 1)
    assign_and_verify("IMPLIED_TRISTATE", 2)
    c.syms["IMPLIED_TRISTATE"].unset_value()
    verify_value("IMPLIED_TRISTATE", "n")

    # Same as above for m. Anything still goes, but m by default now.

    assign_and_verify("IMPLY", 1)
    assign_and_verify("IMPLIED_TRISTATE", 0)
    assign_and_verify("IMPLIED_TRISTATE", 1)
    assign_and_verify("IMPLIED_TRISTATE", 2)
    c.syms["IMPLIED_TRISTATE"].unset_value()
    verify_value("IMPLIED_TRISTATE", 1)

    # Same as above for y. Only n and y should be accepted. m gets promoted to
    # y. Default should be y.

    assign_and_verify("IMPLY", 2)
    assign_and_verify("IMPLIED_TRISTATE", 0)
    assign_and_verify_value("IMPLIED_TRISTATE", 1, 2)
    assign_and_verify("IMPLIED_TRISTATE", 2)
    c.syms["IMPLIED_TRISTATE"].unset_value()
    verify_value("IMPLIED_TRISTATE", 2)

    # Being implied to either m or y should give a bool the value y

    c.syms["IMPLY"].unset_value()
    verify_value("IMPLIED_BOOL", 0)
    assign_and_verify("IMPLY", 0)
    verify_value("IMPLIED_BOOL", 0)
    assign_and_verify("IMPLY", 1)
    verify_value("IMPLIED_BOOL", 2)
    assign_and_verify("IMPLY", 2)
    verify_value("IMPLIED_BOOL", 2)

    # A bool implied to m or y can take the values n and y

    c.syms["IMPLY"].set_value(1)
    assign_and_verify("IMPLIED_BOOL", 0)
    assign_and_verify("IMPLIED_BOOL", 2)

    c.syms["IMPLY"].set_value(2)
    assign_and_verify("IMPLIED_BOOL", 0)
    assign_and_verify("IMPLIED_BOOL", 2)


    print("Testing choice semantics")

    # Would warn for choice value symbols defined without a type, even
    # though the type is automatically derived. This is probably more
    # helpful than ignoring those cases, as this feature isn't used
    # deliberately anywhere from what I've seen.
    c = Kconfig("Kconfiglib/tests/Kchoice", warn=False)

    for name in "BOOL", "BOOL_OPT", "BOOL_M", "DEFAULTS":
        verify(c.named_choices[name].orig_type == BOOL,
               "choice {} should have type bool".format(name))

    for name in "TRISTATE", "TRISTATE_OPT", "TRISTATE_M":
        verify(c.named_choices[name].orig_type == TRISTATE,
               "choice {} should have type tristate".format(name))

    def select_and_verify(sym):
        choice = sym.nodes[0].parent.item
        choice.set_value(2)

        sym.set_value(2)

        verify(sym.choice.selection is sym,
               sym.name + " should be the selected symbol")

        verify(choice.user_selection is sym,
               sym.name + " should be the user selection of the choice")

        verify(sym.tri_value == 2,
               sym.name + " should have value y when selected")

        verify(sym.user_value == 2,
               sym.name + " should have user value y when selected")

        for sibling in choice.syms:
            if sibling is not sym:
                verify(sibling.tri_value == 0,
                       sibling.name + " should be n when not selected")

    def select_and_verify_all(choice_name):
        choice = c.named_choices[choice_name]

        # Select in forward order
        for sym in choice.syms:
            select_and_verify(sym)

        # Select in reverse order
        for sym in reversed(choice.syms):
            select_and_verify(sym)

    def verify_mode(choice_name, no_modules_mode, modules_mode):
        choice = c.named_choices[choice_name]

        c.modules.set_value(0)
        verify(choice.tri_value == no_modules_mode,
               'Wrong mode for choice {} with no modules. Expected {}, got {}.'
               .format(choice.name, no_modules_mode, choice.tri_value))

        c.modules.set_value(2)
        verify(choice.tri_value == modules_mode,
               'Wrong mode for choice {} with modules. Expected {}, got {}.'
               .format(choice.name, modules_mode, choice.tri_value))

    verify_mode("BOOL",         2, 2)
    verify_mode("BOOL_OPT",     0, 0)
    verify_mode("TRISTATE",     2, 1)
    verify_mode("TRISTATE_OPT", 0, 0)
    verify_mode("BOOL_M",       0, 2)
    verify_mode("TRISTATE_M",   0, 1)

    # Test defaults

    choice = c.named_choices["DEFAULTS"]

    c.syms["TRISTATE_SYM"].set_value(0)
    verify(choice.selection is c.syms["OPT_4"],
           "Wrong choice default with TRISTATE_SYM = n")

    c.syms["TRISTATE_SYM"].set_value(2)
    verify(choice.selection is c.syms["OPT_2"],
           "Wrong choice default with TRISTATE_SYM = y")

    c.syms["OPT_1"].set_value(2)
    verify(choice.selection is c.syms["OPT_1"],
           "User selection should override defaults")

    verify(c.named_choices["DEFAULTS_NOT_VISIBLE"].selection
           is c.syms["OPT_8"],
           "Non-visible choice symbols should cause the next default to be "
           "considered")

    # Test y mode selection

    c.modules.set_value(2)

    select_and_verify_all("BOOL")
    select_and_verify_all("BOOL_OPT")
    select_and_verify_all("TRISTATE")
    select_and_verify_all("TRISTATE_OPT")
    # For BOOL_M, the mode should have been promoted
    select_and_verify_all("BOOL_M")

    # Test m mode selection

    c.named_choices["TRISTATE"].set_value(1)

    verify(c.named_choices["TRISTATE"].tri_value == 1,
           "TRISTATE choice should have mode m after explicit mode assignment")

    assign_and_verify_value("T_1", 0, 0)
    assign_and_verify_value("T_2", 0, 0)
    assign_and_verify_value("T_1", 1, 1)
    assign_and_verify_value("T_2", 1, 1)
    assign_and_verify_value("T_1", 2, 1)
    assign_and_verify_value("T_2", 2, 1)

    # Switching to y mode should cause T_2 to become selected
    c.named_choices["TRISTATE"].set_value(2)
    verify_value("T_1", 0)
    verify_value("T_2", 2)

    # Verify that choices with no explicitly specified type get the type of the
    # first contained symbol with a type

    verify(c.named_choices["NO_TYPE_BOOL"].orig_type == BOOL,
           "Expected first choice without explicit type to have type bool")

    verify(c.named_choices["NO_TYPE_TRISTATE"].orig_type == TRISTATE,
           "Expected second choice without explicit type to have type "
           "tristate")

    # Verify that symbols without a type in the choice get the type of the
    # choice

    for name in "MMT_1", "MMT_2", "MMT_4", "MMT_5":
        verify(c.syms[name].orig_type == BOOL,
               "Expected {} to get type bool".format(name))

    verify(c.syms["MMT_3"].orig_type == TRISTATE,
           "Expected MMT_3 to have type tristate")

    # Verify that the default selection can change depending on the
    # visibility of the choice symbols

    default_with_dep_choice = c.named_choices["DEFAULT_WITH_DEP"]

    verify(default_with_dep_choice.selection is c.syms["B"],
           "Wrong choice default with unsatisfied deps on default")

    c.syms["DEP"].set_value("y")

    verify(default_with_dep_choice.selection is c.syms["A"],
           "Wrong choice default with satisfied deps on default")

    c.syms["DEP"].set_value("n")

    verify(default_with_dep_choice.selection is c.syms["B"],
           "Wrong choice default with unsatisfied deps on default (round two)")

    # Verify that symbols in choices that depend on the preceding symbol aren't
    # considered choice symbols

    weird_choice = c.named_choices["WEIRD_SYMS"]

    def verify_is_normal_choice_symbol(name):
        sym = c.syms[name]
        verify(sym.choice is not None and
               sym in weird_choice.syms and
               sym.nodes[0].parent.item is weird_choice,
               "{} should be a normal choice symbol".format(sym.name))

    def verify_is_weird_choice_symbol(name):
        sym = c.syms[name]
        verify(sym.choice is None and
               sym not in weird_choice.syms,
               "{} should be a weird (non-)choice symbol"
               .format(sym.name))

    verify_is_normal_choice_symbol("WS1")
    verify_is_weird_choice_symbol("WS2")
    verify_is_weird_choice_symbol("WS3")
    verify_is_weird_choice_symbol("WS4")
    verify_is_weird_choice_symbol("WS5")
    verify_is_normal_choice_symbol("WS6")
    verify_is_weird_choice_symbol("WS7")
    verify_is_weird_choice_symbol("WS8")
    verify_is_normal_choice_symbol("WS9")


    print("Testing 'if' node removal")

    c = Kconfig("Kconfiglib/tests/Kifremoval", warn=False)

    nodes = tuple(c.node_iter())
    verify_equal(nodes[0].item.name, "A")
    verify_equal(nodes[1].item.name, "B")
    verify_equal(nodes[2].item.name, "C")
    verify_equal(nodes[3].item.name, "D")
    verify_equal(nodes[4].prompt[0], "E")
    verify_equal(nodes[5].prompt[0], "F")
    verify_equal(nodes[6].prompt[0], "G")
    verify_equal(nodes[7].item.name, "H")
    verify_equal(nodes[8].item.name, "I")
    verify_equal(nodes[9].item.name, "J")
    verify(len(nodes) == 10,
           "Wrong number of nodes after 'if' removal")


    print("Testing multi.def. property copying")

    c = Kconfig("Kconfiglib/tests/Kdepcopy", warn=False)

    def verify_props(desc, props, prop_names):
        actual = [prop[0].name for prop in props]
        expected = prop_names.split()

        verify(actual == expected,
               "Wrong {} properties, expected '{}', got '{}'"
               .format(desc, expected, actual))

    verify_props("default", c.syms["MULTIDEF"].defaults,
                 "A B C D E F G H I J K L M N O P Q R")

    verify_props("select", c.syms["MULTIDEF"].selects,
                 "AA BB CC DD EE FF GG HH II JJ")

    verify_props("imply", c.syms["MULTIDEF"].selects,
                 "AA BB CC DD EE FF GG HH II JJ")

    verify_props("select", c.syms["MULTIDEF_CHOICE"].selects,
                 "A B C")

    verify_props("range", c.syms["MULTIDEF_RANGE"].ranges,
                 "A B C D E F")

    verify_props("default", c.choices[1].defaults,
                 "A B C D E")


    print("Testing dependency loop detection")

    # These are all expected to raise dependency loop errors
    for i in range(11):
        filename = "Kconfiglib/tests/Kdeploop" + str(i)
        try:
            Kconfig(filename)
        except KconfigError as e:
            if "Dependency loop" not in str(e):
                fail("dependency loop in {} raised wrong KconfigError"
                     .format(filename))
        except:
            fail("dependency loop in {} raised wrong exception"
                 .format(filename))
        else:
            fail("dependency loop in {} not detected".format(filename))

    # Check the most complicated message completely
    try:
        Kconfig("Kconfiglib/tests/Kdeploop10")
    except KconfigError as e:
        verify_equal(str(e), """
Dependency loop
===============

A (defined at Kconfiglib/tests/Kdeploop10:1), with definition...

config A
	bool
	depends on B

...depends on B (defined at Kconfiglib/tests/Kdeploop10:5), with definition...

config B
	bool
	depends on C = 7

...depends on C (defined at Kconfiglib/tests/Kdeploop10:9), with definition...

config C
	int
	range D 8

...depends on D (defined at Kconfiglib/tests/Kdeploop10:13), with definition...

config D
	int
	default 3 if E
	default 8

...depends on E (defined at Kconfiglib/tests/Kdeploop10:18), with definition...

config E
	bool

(select-related dependencies: F && G)

...depends on G (defined at Kconfiglib/tests/Kdeploop10:25), with definition...

config G
	bool
	depends on H

...depends on the choice symbol H (defined at Kconfiglib/tests/Kdeploop10:32), with definition...

config H
	bool "H"
	depends on I && <choice>

...depends on the choice symbol I (defined at Kconfiglib/tests/Kdeploop10:41), with definition...

config I
	bool "I"
	depends on <choice>

...depends on <choice> (defined at Kconfiglib/tests/Kdeploop10:38), with definition...

choice
	bool "choice" if J

...depends on J (defined at Kconfiglib/tests/Kdeploop10:46), with definition...

config J
	bool
	depends on A

...depends again on A (defined at Kconfiglib/tests/Kdeploop10:1)
"""[:-1])
    except:
        fail("Loop detection message check raised wrong exception")
    else:
        fail("Loop detection message check did not raise exception")


    print("Testing preprocessor")

    os.environ["ENV_1"] = "env_1"
    os.environ["ENV_2"] = "env_2"
    os.environ["ENV_3"] = "env_3"
    os.environ["ENV_4"] = "env_4"
    os.environ["ENV_5"] = "n"
    os.environ["ENV_6"] = "Kconfiglib/tests/empty"
    os.environ["ENV_7"] = "env_7"
    # We verify warnings manually
    c = Kconfig("Kconfiglib/tests/Kpreprocess", warn_to_stderr=False)

    def verify_variable(name, unexp_value, exp_value, recursive, *args):
        var = c.variables[name]

        verify(var.value == unexp_value,
               "expected variable '{}' to have the unexpanded value '{}', had "
               "the value '{}'".format(name, unexp_value, var.value))

        if not args:
            verify(var.expanded_value == exp_value,
                   "expected expanded_value for {} to be '{}', was '{}'"
                   .format(name, exp_value, var.expanded_value))

        verify(var.expanded_value_w_args(*args) == exp_value,
               "expected expanded_value_w_args() for '{}' to be '{}', was '{}'"
               .format(name, exp_value, var.expanded_value_w_args(*args)))

        verify(var.is_recursive == recursive,
               "{} was {}, shouldn't be"
               .format(name, "recursive" if var.is_recursive else "simple"))

    verify_variable("simple-recursive", "foo", "foo", True)
    verify_variable("simple-immediate", "bar", "bar", False)
    verify_variable("simple-recursive-2", "baz", "baz", True)

    verify_variable("whitespaced", "foo", "foo", True)

    verify_variable("preserve-recursive", "foo bar", "foo bar", True)
    verify_variable("preserve-immediate", "foo bar", "foo bar", False)

    verify_variable("recursive",
                    "$(foo) $(bar) $($(b-char)a$(z-char)) $(indir)",
                    "abc def ghi jkl mno",
                    True)

    verify_variable("immediate", "foofoo", "foofoo", False)

    verify_variable("messy-fn-res",
                    "$($(fn-indir)-unused-arg, a  b (,) , c  d )",
                    'surround-rev-quote " c  d " " a  b (,) " surround-rev-quote ',
                    True)

    verify_variable("special-chars-fn-res",
                    "$(fn,$(comma)$(dollar)$(left-paren)foo$(right-paren))",
                    '",$(foo)"',
                    True)

    verify_variable("quote", '"$(1)" "$(2)"', '"" ""', True)
    verify_variable("quote", '"$(1)" "$(2)"', '"one" ""', True,
                    "one")
    verify_variable("quote", '"$(1)" "$(2)"', '"one" "two"', True,
                    "one", "two")
    verify_variable("quote", '"$(1)" "$(2)"', '"one" "two"', True,
                    "one", "two", "three")

    verify_str(c.syms["PRINT_ME"], r"""
config PRINT_ME
	string "env_1" if (FOO && BAR) || !BAZ || !QAZ
	default "\"foo\"" if "foo \"bar\" baz" = ""
""")

    verify_str(c.syms["PRINT_ME_TOO"], r"""
config PRINT_ME_TOO
	bool "foo"
	default FOOBARBAZQAZ if QAZ && QAZFOO && xxx
""")

    def verify_repr(name, s):
        verify_equal(repr(c.variables[name]), s)

    verify_repr(
        "simple-immediate",
        "<variable simple-immediate, immediate, value 'bar'>")

    verify_repr(
        "messy-fn-res",
        "<variable messy-fn-res, recursive, value '$($(fn-indir)-unused-arg, a  b (,) , c  d )'>")

    def verify_recursive(name):
        try:
            c.variables[name].expanded_value
        except KconfigError:
            pass
        else:
            fail("Expected '{}' expansion to flag recursive expansion, didn't"
                 .format(name))

    verify_recursive("rec-1")
    # Indirectly verifies that it's not recursive
    verify_variable("safe-fn-rec-res",
                    "$(safe-fn-rec,safe-fn-rec-2)",
                    "foo",
                    True)
    verify_recursive("unsafe-fn-rec")

    verify_variable("foo-bar-baz", "$(rhs)", "value", True)

    verify_variable("space-var-res", "$(foo bar)", "value", True)

    verify_variable("shell-res",
                    "$(shell,false && echo foo bar || echo baz qaz)",
                    "baz qaz",
                    True)

    verify_variable("shell-stderr-res", "", "", False)

    verify_variable("parens-res",
                    "pre-$(shell,echo '(a,$(b-char),(c,d),e)')-post",
                    "pre-(a,b,(c,d),e)-post",
                    True)

    verify_variable("location-res",
                    "Kconfiglib/tests/Kpreprocess:129",
                    "Kconfiglib/tests/Kpreprocess:129",
                    False)

    verify_variable("warning-res", "", "", False)
    verify_variable("error-n-res", "", "", False)

    try:
        c.variables["error-y-res"].expanded_value
    except KconfigError:
        pass
    else:
        fail("expanding error-y-res didn't raise an exception")

    # Check Kconfig.env_vars
    verify_equal(c.env_vars,
                 set(("ENV_1", "ENV_2", "ENV_3", "ENV_4", "ENV_5", "ENV_6")))

    # Check that the expected warnings were generated
    verify_equal(c.warnings, [
        "Kconfiglib/tests/Kpreprocess:122: warning: 'echo message on stderr >&2' wrote to stderr: message on stderr",
        "Kconfiglib/tests/Kpreprocess:134: warning: a warning"
    ])


    print("Testing user-defined preprocessor functions")

    # Make Kconfiglib/tests/kconfigfunctions.py importable
    sys.path.insert(0, "Kconfiglib/tests")

    c = Kconfig("Kconfiglib/tests/Kuserfunctions")

    verify_variable("add-zero",  "$(add)",          "0", True)
    verify_variable("add-one",   "$(add,1)",        "1", True)
    verify_variable("add-three", "$(add,1,-1,2,1)", "3", True)

    verify_variable("one-one", "$(one,foo bar)", "onefoo barfoo bar", True)

    verify_variable("one-or-more-one", "$(one-or-more,foo)", "foo + ", True)
    verify_variable("one-or-more-three", "$(one-or-more,foo,bar,baz)",
                    "foo + bar,baz", True)

    verify_variable("location-1", "Kconfiglib/tests/Kuserfunctions:13",
                    "Kconfiglib/tests/Kuserfunctions:13", False)
    verify_variable("location-2", "Kconfiglib/tests/Kuserfunctions:14",
                    "Kconfiglib/tests/Kuserfunctions:14", False)

    def verify_bad_argno(name):
        try:
            c.variables[name].expanded_value
        except KconfigError:
            pass
        else:
            fail("Expected '{}' expansion to flag wrong number of arguments, "
                 "didn't".format(name))

    verify_bad_argno("one-zero")
    verify_bad_argno("one-two")
    verify_bad_argno("one-or-more-zero")

    sys.path.pop(0)

    # This test can fail on older Python 3.x versions, because they don't
    # preserve dict insertion order during iteration. The output is still
    # correct, just different.
    if not (3, 0) <= sys.version_info <= (3, 5):
        print("Testing KCONFIG_WARN_UNDEF")

        os.environ["KCONFIG_WARN_UNDEF"] = "y"
        c = Kconfig("Kconfiglib/tests/Kundef", warn_to_stderr=False)

        verify_equal("\n".join(c.warnings), """
warning: the int symbol INT (defined at Kconfiglib/tests/Kundef:8) has a non-int range [UNDEF_2 (undefined), 8 (undefined)]
warning: undefined symbol UNDEF_1:

- Referenced at Kconfiglib/tests/Kundef:4:

config BOOL
	bool "foo" if DEF || !UNDEF_1
	default UNDEF_2

- Referenced at Kconfiglib/tests/Kundef:19:

menu "menu"
	depends on UNDEF_1
	visible if UNDEF_3
warning: undefined symbol UNDEF_2:

- Referenced at Kconfiglib/tests/Kundef:4:

config BOOL
	bool "foo" if DEF || !UNDEF_1
	default UNDEF_2

- Referenced at Kconfiglib/tests/Kundef:8:

config INT
	int
	range UNDEF_2 8
	range 5 15
	default 10
warning: undefined symbol UNDEF_3:

- Referenced at Kconfiglib/tests/Kundef:19:

menu "menu"
	depends on UNDEF_1
	visible if UNDEF_3
"""[1:-1])

        os.environ.pop("KCONFIG_WARN_UNDEF")


    print("\nAll selftests passed\n" if all_passed else
          "\nSome selftests failed\n")


def run_compatibility_tests():
    # Runs tests on configurations from the kernel. Tests compability with the
    # C implementation by comparing outputs.

    # Referenced inside the kernel Kconfig files.
    #
    # The str() makes the type of the value 'str' on both Python 2 and Python 3,
    # which is nice for some later dictionary key sanity checks.

    os.environ["KERNELVERSION"] = str(
        subprocess.check_output("make kernelversion", shell=True)
            .decode("utf-8").rstrip()
    )

    os.environ["CC_VERSION_TEXT"] = str(
        subprocess.check_output("gcc --version | head -n1", shell=True)
            .decode("utf-8").rstrip()
    )

    os.environ["srctree"] = "."
    os.environ["CC"] = "gcc"
    os.environ["LD"] = "ld"


    if not os.path.exists("scripts/kconfig/conf"):
        print("\nscripts/kconfig/conf does not exist -- running "
              "'make allnoconfig' to build it...")
        shell("make allnoconfig")


    print("Running compatibility tests...\n")

    test_fns = (test_defconfig,
                # Fails for a few defconfigs due to a bug in the C tools. Will
                # be enabled once patches get in.
                #test_min_config,
                test_alldefconfig,
                test_allnoconfig,
                test_allnoconfig_walk,
                test_allmodconfig,
                test_allyesconfig,
                test_sanity)

    for test_fn in test_fns:
        # The test description is taken from the docstring of the corresponding
        # function
        print(textwrap.dedent(test_fn.__doc__))

        for arch, srcarch in all_arch_srcarch():
            # Referenced inside the Kconfig files
            os.environ["ARCH"] = arch
            os.environ["SRCARCH"] = srcarch

            rm_configs()

            test_fn(arch, srcarch)

    if all_passed:
        print("All selftests and compatibility tests passed")
    else:
        sys.exit("Some tests failed")


def all_arch_srcarch():
    for srcarch in os.listdir("arch"):
        # arc and h8300 are currently broken with the C tools on linux-next as
        # well. Perhaps they require cross-compilers to be installed.
        #
        # User-mode Linux has an unorthodox Kconfig setup that would require a
        # different testing setup. Skip it too.
        if srcarch in ("arc", "h8300", "um"):
            continue

        if os.path.exists(os.path.join("arch", srcarch, "Kconfig")):
            yield (srcarch, srcarch)

    # Some arches define additional ARCH settings with ARCH != SRCARCH
    # (search for "Additional ARCH settings for" in the top-level Makefile)

    yield ("i386", "x86")
    yield ("x86_64", "x86")

    yield ("sparc32", "sparc")
    yield ("sparc64", "sparc")

    yield ("sh64", "sh")


def test_allnoconfig(arch, srcarch):
    """
    Verify that allnoconfig.py generates the same .config as
    'make allnoconfig', for each architecture. Runs the script via
    'make scriptconfig'.
    """
    shell("make scriptconfig SCRIPT=Kconfiglib/allnoconfig.py "
          "PYTHONCMD='{}'".format(sys.executable))
    shell("mv .config ._config")
    shell("scripts/kconfig/conf --allnoconfig Kconfig")

    compare_configs(arch)


def test_allnoconfig_walk(arch, srcarch):
    """
    Verify that examples/allnoconfig_walk.py generates the same .config as
    'make allnoconfig', for each architecture. Runs the script via
    'make scriptconfig'.
    """
    shell("make scriptconfig SCRIPT=Kconfiglib/examples/allnoconfig_walk.py "
          "PYTHONCMD='{}'".format(sys.executable))
    shell("mv .config ._config")
    shell("scripts/kconfig/conf --allnoconfig Kconfig")

    compare_configs(arch)


def test_allmodconfig(arch, srcarch):
    """
    Verify that allmodconfig.py generates the same .config as
    'make allmodconfig', for each architecture. Runs the script via
    'make scriptconfig'.
    """
    shell("make scriptconfig SCRIPT=Kconfiglib/allmodconfig.py "
          "PYTHONCMD='{}'".format(sys.executable))
    shell("mv .config ._config")
    shell("scripts/kconfig/conf --allmodconfig Kconfig")

    compare_configs(arch)


def test_allyesconfig(arch, srcarch):
    """
    Verify that allyesconfig.py generates the same .config as
    'make allyesconfig', for each architecture. Runs the script via
    'make scriptconfig'.
    """
    shell("make scriptconfig SCRIPT=Kconfiglib/allyesconfig.py "
          "PYTHONCMD='{}'".format(sys.executable))
    shell("mv .config ._config")
    shell("scripts/kconfig/conf --allyesconfig Kconfig")

    compare_configs(arch)


def test_sanity(arch, srcarch):
    """
    Do sanity checks on each configuration and call all public methods on all
    symbols, choices, and menu nodes for all architectures to make sure we
    never crash or hang.
    """
    print("For {}...".format(arch))

    kconf = Kconfig()

    for sym in kconf.defined_syms:
        verify(sym._visited == 2,
               "{} has broken dependency loop detection (_visited = {})"
               .format(sym.name, sym._visited))

    kconf.modules
    kconf.defconfig_list
    kconf.defconfig_filename

    # Legacy warning functions
    kconf.enable_redun_warnings()
    kconf.disable_redun_warnings()
    kconf.enable_undef_warnings()
    kconf.disable_undef_warnings()
    kconf.enable_warnings()
    kconf.disable_warnings()
    kconf.enable_stderr_warnings()
    kconf.disable_stderr_warnings()

    kconf.mainmenu_text
    kconf.unset_values()

    kconf.write_autoconf("/dev/null")

    # No tempfile.TemporaryDirectory in Python 2
    tmpdir = tempfile.mkdtemp()
    kconf.sync_deps(os.path.join(tmpdir, "deps"))  # Create
    kconf.sync_deps(os.path.join(tmpdir, "deps"))  # Update
    shutil.rmtree(tmpdir)

    # Python 2/3 compatible
    for key, sym in kconf.syms.items():
        verify(isinstance(key, str), "weird key '{}' in syms dict".format(key))

        verify(not sym.is_constant, sym.name + " in 'syms' and constant")

        verify(sym not in kconf.const_syms,
               sym.name + " in both 'syms' and 'const_syms'")

        for dep in sym._dependents:
            verify(not dep.is_constant,
                   "the constant symbol {} depends on {}"
                   .format(dep.name, sym.name))

        sym.__repr__()
        sym.__str__()
        sym.assignable
        kconf.disable_warnings()
        sym.set_value(2)
        sym.set_value("foo")
        sym.unset_value()
        kconf.enable_warnings()  # Legacy warning function
        sym.str_value
        sym.tri_value
        sym.type
        sym.user_value
        sym.visibility

    for sym in kconf.defined_syms:
        verify(sym.nodes, sym.name + " is defined but lacks menu nodes")

        verify(not (sym.orig_type not in (BOOL, TRISTATE) and sym.choice),
               sym.name + " is a choice symbol but not bool/tristate")

    for key, sym in kconf.const_syms.items():
        verify(isinstance(key, str),
               "weird key '{}' in const_syms dict".format(key))

        verify(sym.is_constant,
               '"{}" is in const_syms but not marked constant'
               .format(sym.name))

        verify(not sym.nodes,
               '"{}" is constant but has menu nodes'.format(sym.name))

        verify(not sym._dependents,
               '"{}" is constant but is a dependency of some symbol'
               .format(sym.name))

        verify(not sym.choice,
               '"{}" is constant and a choice symbol'.format(sym.name))

        sym.__repr__()
        sym.__str__()
        sym.assignable
        kconf.disable_warnings()
        sym.set_value(2)
        sym.set_value("foo")
        sym.unset_value()
        kconf.enable_warnings()  # Legacy warning function
        sym.str_value
        sym.tri_value
        sym.type
        sym.visibility

    for choice in kconf.choices:
        for sym in choice.syms:
            verify(sym.choice is choice,
                   "{0} is in choice.syms but 'sym.choice' is not the choice"
                   .format(sym.name))

            verify(sym.type in (BOOL, TRISTATE),
                   "{} is a choice symbol but is not a bool/tristate"
                   .format(sym.name))

        choice.__str__()
        choice.__repr__()
        choice.str_value
        choice.tri_value
        choice.user_value
        choice.assignable
        choice.selection
        choice.type
        choice.visibility

    # Menu nodes

    node = kconf.top_node

    while 1:
        # Everything else should be well exercised elsewhere
        node.__repr__()
        node.__str__()
        verify(isinstance(node.item, (Symbol, Choice)) or \
               node.item in (MENU, COMMENT),
               "'{}' appeared as a menu item".format(node.item))

        if node.list is not None:
            node = node.list

        elif node.next is not None:
            node = node.next

        else:
            while node.parent is not None:
                node = node.parent
                if node.next is not None:
                    node = node.next
                    break
            else:
                break


def test_alldefconfig(arch, srcarch):
    """
    Verify that alldefconfig.py generates the same .config as
    'make alldefconfig', for each architecture. Runs the script via
    'make scriptconfig'.
    """
    shell("make scriptconfig SCRIPT=Kconfiglib/alldefconfig.py "
          "PYTHONCMD='{}'".format(sys.executable))
    shell("mv .config ._config")
    shell("scripts/kconfig/conf --alldefconfig Kconfig")

    compare_configs(arch)


def test_defconfig(arch, srcarch):
    """
    Verify that Kconfiglib generates the same .config as scripts/kconfig/conf,
    for each architecture/defconfig pair. In obsessive mode, this test includes
    nonsensical groupings of arches with defconfigs from other arches (every
    arch/defconfig combination) and takes an order of magnitude longer time to
    run.

    With logging enabled, this test appends any failures to a file
    test_defconfig_fails in the root.
    """
    kconf = Kconfig()

    if obsessive:
        defconfigs = []

        # Collect all defconfigs. This could be done once instead, but it's
        # a speedy operation comparatively.
        for srcarch_ in os.listdir("arch"):
            defconfigs.extend(defconfig_files(srcarch_))
    else:
        defconfigs = defconfig_files(srcarch)

    # Test architecture for each defconfig

    for defconfig in defconfigs:
        rm_configs()

        kconf.load_config(defconfig)
        kconf.write_config("._config")
        shell("scripts/kconfig/conf --defconfig='{}' Kconfig".
              format(defconfig))

        arch_defconfig_str = "  {:14}with {:60} ".format(arch, defconfig)

        if equal_configs():
            print(arch_defconfig_str + "OK")
        else:
            print(arch_defconfig_str + "FAIL")
            fail()
            if log:
                with open("test_defconfig_fails", "a") as fail_log:
                    fail_log.write("{} with {} did not match\n"
                                   .format(arch, defconfig))


def test_min_config(arch, srcarch):
    """
    Verify that Kconfiglib generates the same .config as 'make savedefconfig'
    for each architecture/defconfig pair.
    """
    kconf = Kconfig()

    if obsessive_min_config:
        defconfigs = []
        for srcarch_ in os.listdir("arch"):
            defconfigs.extend(defconfig_files(srcarch_))
    else:
        defconfigs = defconfig_files(srcarch)

    for defconfig in defconfigs:
        rm_configs()

        kconf.load_config(defconfig)
        kconf.write_min_config("._config")

        shell("cp {} .config".format(defconfig))

        shell("scripts/kconfig/conf --savedefconfig=.config Kconfig")

        arch_defconfig_str = "  {:14}with {:60} ".format(arch, defconfig)

        if equal_configs():
            print(arch_defconfig_str + "OK")
        else:
            print(arch_defconfig_str + "FAIL")


#
# Helper functions
#


def defconfig_files(srcarch):
    # Yields a list of defconfig file filenames for a particular srcarch
    # subdirectory (arch/<srcarch>/)

    srcarch_dir = os.path.join("arch", srcarch)

    # Some arches have a defconfig in the root of their arch/<arch>/ directory
    root_defconfig = os.path.join(srcarch_dir, "defconfig")
    if os.path.exists(root_defconfig):
        yield root_defconfig

    # Assume all files in the arch/<arch>/configs/ directory (if it exists) are
    # configurations
    defconfigs_dir = os.path.join(srcarch_dir, "configs")

    if not os.path.isdir(defconfigs_dir):
        return

    for dirpath, _, filenames in os.walk(defconfigs_dir):
        for filename in filenames:
            yield os.path.join(dirpath, filename)


def rm_configs():
    # Delete any old ".config" (generated by the C implementation) and
    # "._config" (generated by us), if present.

    def rm_if_exists(f):
        if os.path.exists(f):
            os.remove(f)

    rm_if_exists(".config")
    rm_if_exists("._config")


def compare_configs(arch):
    if equal_configs():
        print("{:14}OK".format(arch))
    else:
        print("{:14}FAIL".format(arch))
        fail()


def equal_configs():
    with open(".config") as f:
        their = f.readlines()

    # Strip the header generated by 'conf'
    i = 0
    for line in their:
        if not line.startswith("#") or \
           re.match(r"# CONFIG_(\w+) is not set", line):
            break
        i += 1
    their = their[i:]

    try:
        f = open("._config")
    except EnvironmentError as e:
        if e.errno != errno.ENOENT:
            raise
        print("._config not found. Did you forget to apply the Makefile patch?")
        return False
    else:
        with f:
            our = f.readlines()

    if their == our:
        return True

    # Print a unified diff to help debugging
    print("Mismatched .config's! Unified diff:")
    sys.stdout.writelines(difflib.unified_diff(their, our, fromfile="their",
                                               tofile="our"))

    return False


if __name__ == "__main__":
    run_tests()

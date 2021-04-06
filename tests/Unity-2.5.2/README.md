Unity Test ![CI](https://github.com/ThrowTheSwitch/Unity/workflows/CI/badge.svg)
==========
__Copyright (c) 2007 - 2021 Unity Project by Mike Karlesky, Mark VanderVoord, and Greg Williams__

Welcome to the Unity Test Project, one of the main projects of ThrowTheSwitch.org. Unity Test is a 
unit testing framework built for C, with a focus on working with embedded toolchains. 

This project is made to test code targetting microcontrollers big and small. The core project is a 
single C file and a pair of headers, allowing it to the added to your existing build setup without 
too much headache. You may use any compiler you wish, and may use most existing build systems
including make, cmake, etc. If you'd like to leave the hard work to us, you might be interested
in Ceedling, a build tool also by ThrowTheSwitch.org. 

If you're new to Unity, we encourage you to tour the [getting started guide](docs/UnityGettingStartedGuide.md)

Getting Started
===============
The [docs](docs/) folder contains a [getting started guide](docs/UnityGettingStartedGuide.md)
and much more tips about using Unity. 

Unity Assertion Summary
=======================
For the full list, see [UnityAssertionsReference.md](docs/UnityAssertionsReference.md).

Basic Validity Tests
--------------------

    TEST_ASSERT_TRUE(condition)

Evaluates whatever code is in condition and fails if it evaluates to false

    TEST_ASSERT_FALSE(condition)

Evaluates whatever code is in condition and fails if it evaluates to true

    TEST_ASSERT(condition)

Another way of calling `TEST_ASSERT_TRUE`

    TEST_ASSERT_UNLESS(condition)

Another way of calling `TEST_ASSERT_FALSE`

    TEST_FAIL()
    TEST_FAIL_MESSAGE(message)

This test is automatically marked as a failure. The message is output stating why.

Numerical Assertions: Integers
------------------------------

    TEST_ASSERT_EQUAL_INT(expected, actual)
    TEST_ASSERT_EQUAL_INT8(expected, actual)
    TEST_ASSERT_EQUAL_INT16(expected, actual)
    TEST_ASSERT_EQUAL_INT32(expected, actual)
    TEST_ASSERT_EQUAL_INT64(expected, actual)

Compare two integers for equality and display errors as signed integers. A cast will be performed
to your natural integer size so often this can just be used. When you need to specify the exact size,
like when comparing arrays, you can use a specific version:

    TEST_ASSERT_EQUAL_UINT(expected, actual)
    TEST_ASSERT_EQUAL_UINT8(expected, actual)
    TEST_ASSERT_EQUAL_UINT16(expected, actual)
    TEST_ASSERT_EQUAL_UINT32(expected, actual)
    TEST_ASSERT_EQUAL_UINT64(expected, actual)

Compare two integers for equality and display errors as unsigned integers. Like INT, there are
variants for different sizes also.

    TEST_ASSERT_EQUAL_HEX(expected, actual)
    TEST_ASSERT_EQUAL_HEX8(expected, actual)
    TEST_ASSERT_EQUAL_HEX16(expected, actual)
    TEST_ASSERT_EQUAL_HEX32(expected, actual)
    TEST_ASSERT_EQUAL_HEX64(expected, actual)

Compares two integers for equality and display errors as hexadecimal. Like the other integer comparisons,
you can specify the size... here the size will also effect how many nibbles are shown (for example, `HEX16`
will show 4 nibbles).

    TEST_ASSERT_EQUAL(expected, actual)

Another way of calling TEST_ASSERT_EQUAL_INT

    TEST_ASSERT_INT_WITHIN(delta, expected, actual)

Asserts that the actual value is within plus or minus delta of the expected value. This also comes in
size specific variants.


    TEST_ASSERT_GREATER_THAN(threshold, actual)

Asserts that the actual value is greater than the threshold. This also comes in size specific variants.


    TEST_ASSERT_LESS_THAN(threshold, actual)

Asserts that the actual value is less than the threshold. This also comes in size specific variants.


Arrays
------

    _ARRAY

You can append `_ARRAY` to any of these macros to make an array comparison of that type.  Here you will
need to care a bit more about the actual size of the value being checked.  You will also specify an
additional argument which is the number of elements to compare.  For example:

    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, elements)

    _EACH_EQUAL

Another array comparison option is to check that EVERY element of an array is equal to a single expected
value. You do this by specifying the EACH_EQUAL macro. For example:

    TEST_ASSERT_EACH_EQUAL_INT32(expected, actual, elements)

Numerical Assertions: Bitwise
-----------------------------

    TEST_ASSERT_BITS(mask, expected, actual)

Use an integer mask to specify which bits should be compared between two other integers.  High bits in the mask are compared, low bits ignored.

    TEST_ASSERT_BITS_HIGH(mask, actual)

Use an integer mask to specify which bits should be inspected to determine if they are all set high.  High bits in the mask are compared, low bits ignored.

    TEST_ASSERT_BITS_LOW(mask, actual)

Use an integer mask to specify which bits should be inspected to determine if they are all set low.  High bits in the mask are compared, low bits ignored.

    TEST_ASSERT_BIT_HIGH(bit, actual)

Test a single bit and verify that it is high.  The bit is specified 0-31 for a 32-bit integer.

    TEST_ASSERT_BIT_LOW(bit, actual)

Test a single bit and verify that it is low.  The bit is specified 0-31 for a 32-bit integer.

Numerical Assertions: Floats
----------------------------

    TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual)

Asserts that the actual value is within plus or minus delta of the expected value.

    TEST_ASSERT_EQUAL_FLOAT(expected, actual)
    TEST_ASSERT_EQUAL_DOUBLE(expected, actual)

Asserts that two floating point values are "equal" within a small % delta of the expected value.

String Assertions
-----------------

    TEST_ASSERT_EQUAL_STRING(expected, actual)

Compare two null-terminate strings.  Fail if any character is different or if the lengths are different.

    TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, len)

Compare two strings.  Fail if any character is different, stop comparing after len characters.

    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual, message)

Compare two null-terminate strings.  Fail if any character is different or if the lengths are different. Output a custom message on failure.

    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE(expected, actual, len, message)

Compare two strings. Fail if any character is different, stop comparing after len characters. Output a custom message on failure.

Pointer Assertions
------------------

Most pointer operations can be performed by simply using the integer comparisons above. However, a couple of special cases are added for clarity.

    TEST_ASSERT_NULL(pointer)

Fails if the pointer is not equal to NULL

    TEST_ASSERT_NOT_NULL(pointer)

Fails if the pointer is equal to NULL

Memory Assertions
-----------------

    TEST_ASSERT_EQUAL_MEMORY(expected, actual, len)

Compare two blocks of memory.  This is a good generic assertion for types that can't be coerced into acting like
standard types... but since it's a memory compare, you have to be careful that your data types are packed.

\_MESSAGE
---------

you can append \_MESSAGE to any of the macros to make them take an additional argument.  This argument
is a string that will be printed at the end of the failure strings.  This is useful for specifying more
information about the problem.


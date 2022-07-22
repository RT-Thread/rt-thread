README
======

This folder is containing two files imported, and slightly modified, from the ComputeLibrary:

    NEMath.h and arm_cl_tables.c 

In the original compute library, there are instead two other files:

    NEMath.h and NEMath.inl

NEMath.inl is included from NEMath.h whereas in this CMSIS DSP implementation, there is no NEMath.inl and its content is copied into NEMath.h

The tables contained in NEMath.inl have been moved to arm_cl_tables.c and finally the files are in C for the CMSIS DSP library and in C++ in the original Compute Library.

Otherwise, the features and implementations are the same : a few optimized Neon functions.

The license covering those files is different : It is a MIT license.
Other parts of the CMSIS-DSP are covered with an Apache-2.0 license.

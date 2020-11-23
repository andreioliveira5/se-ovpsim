 
  Copyright (c) 2005-2013 Imperas Software Ltd. All Rights Reserved.

  The contents of this file are provided under the Software License
  Agreement that you accepted before downloading this file.

  This source forms part of the Software and can be used for educational,
  training, and demonstration purposes but cannot be used for derivative
  works except in cases where the derivative works require OVP technology
  to run.

  For open source models released under licenses that you can use for
  derivative works, please visit www.OVPworld.org or www.imperas.com
  for the location of the open source models.


FILE:Imperas/Examples/Platforms/multiprocessor/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the OVPsim and CPUManager
User guide.
It should be used in conjunction with the user guide but is briefly described 
here.

This example shows how more than one processor can be instanced and how 
shared memory can be defined and used for inter-processor communication.

FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/application.c
2. An ICM Platform; this is found as platform/platform.c
3. A makefile to build 1 and 2; this is found as Makefile

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=<CROSS>

To build the ICM Platform

> make -C platform

RUNNING THE EXAMPLE ------------------------------------------------

> platform/platform.<IMPERAS_ARCH>.exe application/application.<CROSS>.elf


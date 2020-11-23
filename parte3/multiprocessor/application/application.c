/*
 *
 * Copyright (c) 2005-2013 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulatorIntercepts.h"

#define NUM_VALUES 35

static volatile int flag = 0;
static volatile int fibres = 0;

int fib(int i) {
    return (i>1) ? fib(i-1) + fib(i-2) : i;
}

int munge(int mungeIn) {

    int result = 0;
    int i;

    for(i=0; i<mungeIn; i++) {
        result += i;
    }
    return result;
}

int writer(int id) {

    int i;

    for(i=0; i<NUM_VALUES; i++) {
        int result = fib(i);
        while(flag) {}
        printf("CPU %d: fib(%d) = %d\n", id, i, result);
        fibres = result;
        flag = (i==(NUM_VALUES-1)) ? 2 : 1;
    }

    while(flag) {}

    return 1;
}

int reader(int id) {

    int done = 0;

    do {
        int mungeIn;
        while(!flag) {}
        mungeIn = fibres;
        done    = (flag==2);
        printf("CPU %d: munge(%d) = %d\n", id, mungeIn, munge(mungeIn));
        flag    = 0;
    } while(!done);

    return 1;
}

int main(int argc, char **argv) {

    int id = impProcessorId();

    printf("CPU %d starting...\n", id);

    switch(id) {

        case 0:
            writer(id);
            break;

        case 1:
            reader(id);
            break;

        case 2:
            break;
    }

    return 1;
}

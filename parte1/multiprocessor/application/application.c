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

#define NUM_VALUES 34

static volatile int flag = 0;
static volatile int flag1 = 0; 
static volatile int fibres = 0;
static volatile int flagend =0;
static volatile int num;
static volatile int proc;
int fib(int i) {
    return (i>1) ? fib(i-1) + fib(i-2) : i;
}

int par(int id) {

    int i;

    for(i=0; i<NUM_VALUES; i=i+2) {
        int result = fib(i);
      
        while(flag1){}
        
        while(flag) {}
    
        fibres = result;
        num = i;
        proc = id;
        flag = (i==(NUM_VALUES-1)) ? 2 : 1;
        flag1 = 1;
      
    }

    while(!flagend){}
    return 1;
}

int impar(int id) {

    int i;

    for(i=1; i<NUM_VALUES; i=i+2) {
        int result = fib(i);
      
        while(!flag1){}
      
        while(flag) {}
       
        fibres = result;
        num = i;
        proc = id;
        flag1 = (i==(NUM_VALUES-1)) ? 2 : 0;;
        flag = 1;

    }
 
    while(!flagend){}
    return 1;
}

int writer(int id) {

    int done =0;
    int done1 =0;
    do { 
        
        while(!flag) {}
            done = (flag==2);
            done1 = (flag1==2);
            printf("CPU(%d)fib(%d) = %d\n",proc ,num, fibres);
            flag    = 0;            
    } while(!done && !done1);
    flagend = 1;
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
            par(id);
            break;

        case 2:
            impar(id);
            break;
    }

    return 1;
}

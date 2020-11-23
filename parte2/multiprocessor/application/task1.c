#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulatorIntercepts.h"

#define NUM_VALUES 35

static volatile int* v_um = (int *) 0xd5d0;
static volatile int* v_zero = (int *) 0xd5cc;
static volatile int* liberado = (int *) 0xf0000300;

void printVars() {
	while(&liberado==0);
	printf("\n-1 *v_zero: %d  *v_um: %d\n", &v_zero, &v_um);
}

int main(int argc, char **argv) {
	printf("\n\nStarting task 1... zero: %p um: %p \n\n", (void*)&v_zero, (void*)&v_um);

	printVars();
	*liberado = 0;
	printVars();
	*liberado = 0;
	printVars();
	*liberado = 0;
	printVars();

	while(*liberado!=70);
    return 1;
}

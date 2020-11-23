#include "../software/include/task.h"
#include "../software/include/stdlib.h"
#include "../software/include/services.h"
#include "../software/include/plasma.h"

static volatile unsigned int * v_test0 = (unsigned int *)0x00000000;
static volatile unsigned int * v_test1 = (unsigned int *)0x00000000;

int main(int argc, char **argv) {
    MemoryWrite(INITIALIZE_ROUTER, 3);
	printf("\n- v_test0: %d \n-v_test1: %d\n\n", v_test0, v_test1);
	v_test0 = 5;
	printf("\n- v_test0: %d \n-v_test1: %d\n\n", v_test0, v_test1);
	v_test1 = 8;
	printf("\n- v_test0: %d \n-v_test1: %d\n\n", v_test0, v_test1);


	printf("\n\n1- Passou\n");
    unsigned int *ptr = (unsigned int *)0x00400000;
	printf("\n\n2- Passou\n");
    unsigned int readVal = *ptr;
	printf("\n\n3- Passou\n");

    *ptr = (unsigned int *)0x00400000;
	printf("\n\n4- Passou\n");


    printf("\n\n<~~~~~~~ Starting Shared Memory Router ~~~~~~~>CA\n\n");
    MemoryWrite(END_SIM, 3);
    return 0;
}

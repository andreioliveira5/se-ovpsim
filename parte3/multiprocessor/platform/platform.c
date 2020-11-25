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

#include <stdlib.h>

#include "icm/icmCpuManager.h"

#define SIM_ATTRS 0

//
// Main simulation routine
//
int main(int argc, char ** argv) {

    // check for the application program name argument


    // initialize ICM - require Imperas intercepts because the
    // application uses impProcessorId() to get processor id
    icmInit(ICM_VERBOSE | ICM_STOP_ON_CTRLC | ICM_ENABLE_IMPERAS_INTERCEPTS, 0, 0);

    // select library components
	const char *vlnvRoot = NULL; //When NULL use default library
    const char *model       = icmGetVlnvString(vlnvRoot, "ovpworld.org", "processor", "or1k", "1.0", "model");
    const char *semihosting = icmGetVlnvString(vlnvRoot, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", "model");

    // create processor cpu0
    icmProcessorP processor0 = icmNewProcessor(
        "cpu0",             // CPU name
        "or1k",             // CPU type
        0,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        SIM_ATTRS,          // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create processor cpu1
    icmProcessorP processor1 = icmNewProcessor(
        "cpu1",             // CPU name
        "or1k",             // CPU type
        1,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        SIM_ATTRS,          // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create processor cpu2
    icmProcessorP processor2 = icmNewProcessor(
        "cpu2",             // CPU name
        "or1k",             // CPU type
        2,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        SIM_ATTRS,          // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create processor cpu3
    icmProcessorP processor3 = icmNewProcessor(
        "cpu3",             // CPU name
        "or1k",             // CPU type
        3,                  // CPU cpuId
        0,                  // CPU model flags
        32,                 // address bits
        model,              // model file
        "modelAttrs",       // morpher attributes
        SIM_ATTRS,          // simulation attributes
        0,                  // user-defined attributes
        semihosting,        // semi-hosting file
        "modelAttrs"        // semi-hosting attributes
    );

    // create the processor busses
    icmBusP bus1 = icmNewBus("bus1", 32);
    icmBusP bus2 = icmNewBus("bus2", 32);
    icmBusP bus3 = icmNewBus("bus3", 32);
    icmBusP bus4 = icmNewBus("bus4", 32);

    // connect the processor busses
    icmConnectProcessorBusses(processor0, bus1, bus1);
    icmConnectProcessorBusses(processor1, bus2, bus2);
    icmConnectProcessorBusses(processor2, bus3, bus3);
    icmConnectProcessorBusses(processor3, bus4, bus4);

    // create memories
    icmMemoryP local1 = icmNewMemory("local1", ICM_PRIV_RWX, 0xefffffff);
    icmMemoryP local2 = icmNewMemory("local2", ICM_PRIV_RWX, 0xefffffff);
    icmMemoryP local3 = icmNewMemory("local3", ICM_PRIV_RWX, 0xefffffff);
    icmMemoryP local4 = icmNewMemory("local4", ICM_PRIV_RWX, 0xefffffff);
    icmMemoryP shared = icmNewMemory("shared", ICM_PRIV_RWX, 0x0fffffff);

    // connect memories
    icmConnectMemoryToBus(bus1, "mp1", shared, 0x00000000);
    icmConnectMemoryToBus(bus2, "mp2", shared, 0x00000000);
    icmConnectMemoryToBus(bus3, "mp3", shared, 0x00000000);
    icmConnectMemoryToBus(bus4, "mp4", shared, 0x00000000);
    icmConnectMemoryToBus(bus1, "mp1", local1, 0x10000000);
    icmConnectMemoryToBus(bus2, "mp1", local2, 0x10000000);
    icmConnectMemoryToBus(bus3, "mp1", local3, 0x10000000);
    icmConnectMemoryToBus(bus4, "mp1", local4, 0x10000000);

    // show the bus connections
    icmPrintf("\nbus1 CONNECTIONS\n");
    icmPrintBusConnections(bus1);
    icmPrintf("\nbus2 CONNECTIONS\n");
    icmPrintBusConnections(bus2);
    icmPrintf("\nbus3 CONNECTIONS\n");
    icmPrintBusConnections(bus3);
    icmPrintf("\nbus4 CONNECTIONS\n");
    icmPrintBusConnections(bus4);
    icmPrintf("\n");

    // load the application executable file into each processor memory space
    // (so that each processor sees application symbols and has the correct
    // start address)
    if(
        !icmLoadProcessorMemory(processor0, "C:/Users/PICHAU/Desktop/Faculdade/VIII_semestre/Sistemas_embarcados/OVP/Aula3/Atividade3/multiprocessor/application/application.OR1K.elf", False, False, True) ||
        !icmLoadProcessorMemory(processor1, "C:/Users/PICHAU/Desktop/Faculdade/VIII_semestre/Sistemas_embarcados/OVP/Aula3/Atividade3/multiprocessor/application/application.OR1K.elf", False, False, True) ||
        !icmLoadProcessorMemory(processor2, "C:/Users/PICHAU/Desktop/Faculdade/VIII_semestre/Sistemas_embarcados/OVP/Aula3/Atividade3/multiprocessor/application/application.OR1K.elf", False, False, True) ||
        !icmLoadProcessorMemory(processor3, "C:/Users/PICHAU/Desktop/Faculdade/VIII_semestre/Sistemas_embarcados/OVP/Aula3/Atividade3/multiprocessor/application/application.OR1K.elf", False, False, True)
    ) {
        return -1;
    }

    // run simulation
    icmSimulatePlatform();

    // report the total number of instructions executed
    icmPrintf(
        "processor0 has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(processor0)
    );
    icmPrintf(
        "processor1 has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(processor1)
    );
    icmPrintf(
        "processor2 has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(processor2)
    );
    icmPrintf(
        "processor3 has executed " FMT_64u " instructions\n",
        icmGetProcessorICount(processor3)
    );

    // free simulation data structures
    icmTerminate();

    return 0;
}

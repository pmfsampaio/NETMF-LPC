@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@
@  Licensed under the Apache License, Version 2.0 (the "License")@
@  you may not use this file except in compliance with the License.
@  You may obtain a copy of the License at http:@www.apache.org/licenses/LICENSE-2.0
@
@  Copyright (c) Microsoft Corporation. All rights reserved.
@  Implementation for STM32: Copyright (c) Oberon microsystems, Inc.
@
@  CORTEX-M3 Standard Entry Code
@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    .global  EntryPoint

    .global  PreStackInit_Exit_Pointer
    .global  ARM_Vectors

    .global StackBottom
    .global StackTop
    .global HeapBegin
    .global HeapEnd
    .global CustomHeapBegin
    .global CustomHeapEnd

    .extern  PreStackInit


	.syntax unified

@    #IF HAL_REDUCESIZE = "1"
@        .extern BootEntryLoader
@    #ELSE
        .extern BootEntry
@    #ENDIF
    .extern  BootstrapCode


    @PRESERVE8

    @*************************************************************************

    .section SectionForStackBottom,       "a", %progbits
StackBottom:
    .word   0
    .section SectionForStackTop,          "a", %progbits
StackTop:
    .word   0
    .section SectionForHeapBegin,         "a", %progbits
HeapBegin:
    .word   0
    .section SectionForHeapEnd,           "a", %progbits
HeapEnd:
    .word   0
    .section SectionForCustomHeapBegin,   "a", %progbits
ARM_Vectors: .space 84*4 @ exception vector table (max 84 entries)
CustomHeapBegin:
    .word   0
    .section SectionForCustomHeapEnd,     "a", %progbits
CustomHeapEnd:
    .word   0


@    AREA ||i.EntryPoint||, CODE, READONLY
.section i.EntryPoint, "xa", %progbits
@    ENTRY

EntryPoint:

@ The first word has several functions:
@ - It is the entry point of the application
@ - it contains a signature word used to identify application blocks
@ - out of reset it contains the initial stack pointer value
@ - it is the first entry of the initial exception handler table
@ The actual word used is 0x2000E00C

    b       Start         @ 0xE00C
    .hword    0x2000        @ Booter signature is 0x2000E00C
    .word     Start         @ Reset
    .word     Fault_Handler @ NMI
    .word     Fault_Handler @ Hard Fault
    .word     Fault_Handler @ MMU Fault
    .word     Fault_Handler @ Bus Fault
    .word     Fault_Handler @ Usage Fault

Start:

    @ allow per processor pre-stack initialization

PreStackEntry:
    b       PreStackInit

PreStackInit_Exit_Pointer:

    ldr     sp,StackTop_Ptr
    bl      BootstrapCode

@    #IF HAL_REDUCESIZE = "1"
@        b   BootEntryLoader
@    #ELSE
        b   BootEntry
@    #ENDIF


    .align   4

StackTop_Ptr:
    .word     StackTop

Fault_Handler:
    b       Fault_Handler


    .end

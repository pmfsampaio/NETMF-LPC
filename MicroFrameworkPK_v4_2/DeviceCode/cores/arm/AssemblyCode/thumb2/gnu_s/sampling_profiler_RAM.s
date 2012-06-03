@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Copyright (c) Microsoft Corporation.  All rights reserved.
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    .ifdef FIQ_SAMPLING_PROFILER

    .global Profiler_FIQ_Initialize

    .extern  EntryPoint
    .extern  HeapBegin
    .extern  ProfilerBufferBegin
    .extern  ProfilerBufferEnd

    .cpu cortex-m3
    .code 16

    .section    i.Profiler_FIQ_Initialize, "ax", %progbits

    .thumb_func

Profiler_FIQ_Initialize:

    stmfd   r13!, {r14}                                 @ save r14 (lr), since we will use it when branching

;; something else for cortex

    ldmfd   r13!, {pc}                                  @ return to caller, restore link register in to pc

    .endif


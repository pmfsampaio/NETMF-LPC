using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;

namespace NXP.Interop
{
    public class ADC
    {
            /// <summary>
            /// Initializes internal ADC buffers and sets output frequency.
            /// </summary>
            /// <param name="inputFrequency">Sample inpuy frequency (Hz)</param>
            [MethodImpl(MethodImplOptions.InternalCall)]
            public extern void Initialize(Int16 inputFrequency);

            /// <summary>
            /// Mark the ADC as disabled
            /// </summary>
            [MethodImpl(MethodImplOptions.InternalCall)]
            public extern void Uninitialize();

            /// <summary>
            /// Start
            /// </summary>
            [MethodImpl(MethodImplOptions.InternalCall)]
            public extern void On();

            /// <summary>
            /// Stop
            /// </summary>
            [MethodImpl(MethodImplOptions.InternalCall)]
            public extern void Off();

            /// <summary>
            /// Get frames left in the buffer
            /// </summary>
            /// <returns>Number of frames left in the buffer</returns>
            [MethodImpl(MethodImplOptions.InternalCall)]
            public extern Int32 GetSample();

    }
}

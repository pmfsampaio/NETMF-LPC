////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _TSC2007_DRIVER_H_
#define _TSC2007_DRIVER_H_ 1


#include <tinyhal.h>

struct TSC2007_Driver
{
    static BOOL Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc);
    static BOOL Disable();
    static void GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY );
    static HRESULT GetDeviceCaps(unsigned int iIndex, void* lpOutput);

private:
    static BOOL CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT *pTCP);
    static int Transfer(I2C_WORD *txBuffer, int txBufferLen, I2C_WORD *rxBuffer, int rxBufferLen);


};

#endif

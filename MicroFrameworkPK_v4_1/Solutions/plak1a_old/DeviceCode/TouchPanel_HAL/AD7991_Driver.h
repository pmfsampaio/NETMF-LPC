/*
 * AD7991_Driver.h
 *
 *  Created on: May 20, 2011
 *      Author: psampaio
 */

#ifndef AD7991_DRIVER_H_
#define AD7991_DRIVER_H_


#include <tinyhal.h>

struct AD7991_Driver
{
    static BOOL Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc);
    static BOOL Disable();
    static void GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState, int* pSource, int* pUnCalX, int* pUnCalY );
    static HRESULT GetDeviceCaps(unsigned int iIndex, void* lpOutput);

private:
    static BOOL CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT *pTCP);

};


#endif /* AD7991_DRIVER_H_ */

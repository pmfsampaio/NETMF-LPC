////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for STM32: Copyright (c) Oberon microsystems, Inc.
//
//  *** I2C Driver ***
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cores\arm\include\cpu.h>
#include "..\LPC1788_Devices.h"


#ifdef STM32_USE_I2C2
#define I2Cx                   I2C2 
#define I2Cx_EV_IRQn           I2C2_EV_IRQn
#define I2Cx_ER_IRQn           I2C2_ER_IRQn
#define RCC_APB1ENR_I2CxEN     RCC_APB1ENR_I2C2EN
#define RCC_APB1RSTR_I2CxRST   RCC_APB1RSTR_I2C2RST
#define I2Cx_SCL_Pin           (16 + 10) // PB10
#define I2Cx_SDA_Pin           (16 + 11) // PB11
#else
#define I2Cx                   I2C1 
#define I2Cx_EV_IRQn           I2C1_EV_IRQn
#define I2Cx_ER_IRQn           I2C1_ER_IRQn
#define RCC_APB1ENR_I2CxEN     RCC_APB1ENR_I2C1EN
#define RCC_APB1RSTR_I2CxRST   RCC_APB1RSTR_I2C1RST
#define I2Cx_SCL_Pin           (16 + 6) // PB6
#define I2Cx_SDA_Pin           (16 + 7) // PB7
#endif

static I2C_HAL_XACTION* currentI2CXAction;
static I2C_HAL_XACTION_UNIT* currentI2CUnit;


void STM32_I2C_ER_Interrupt (void* param) // Error Interrupt Handler
{
#if 0
	INTERRUPT_START
    
    I2C_HAL_XACTION* xAction = currentI2CXAction;

    I2Cx->SR1 = 0; // reset errors
    xAction->Signal(I2C_HAL_XACTION::c_Status_Aborted); // calls XActionStop()

    INTERRUPT_END
#endif
    }
    
void STM32_I2C_EV_Interrupt (void* param) // Event Interrupt Handler
{
#if 0
	INTERRUPT_START
    
    I2C_HAL_XACTION* xAction = currentI2CXAction;
    I2C_HAL_XACTION_UNIT* unit = currentI2CUnit;

    int todo = unit->m_bytesToTransfer;
    int sr1 = I2Cx->SR1;  // read status register
    int sr2 = I2Cx->SR2;  // clear ADDR bit
    int cr1 = I2Cx->CR1;  // initial control register
    
    if (unit->IsReadXActionUnit()) { // read transaction
        if (todo > 0) {
            if (sr1 & I2C_SR1_SB) { // start bit
                if (todo == 2) {
                    I2Cx->CR1 = (cr1 |= I2C_CR1_POS); // prepare 2nd byte nack
                }
                UINT8 addr = xAction->m_address << 1; // address bits
                I2Cx->DR = addr + 1; // send header byte with read bit;
            } else {
                if (sr1 & I2C_SR1_ADDR) { // address sent
                    if (todo <= 2) {
                        if (todo == 1) cr1 |= I2C_CR1_STOP; // send stop after single byte
                        I2Cx->CR1 = (cr1 &= ~I2C_CR1_ACK); // last byte nack
                    }
                } else {
                    int n = 0;
                    if (sr1 & I2C_SR1_BTF) { // two bytes available
                        n = (todo & 1) + 1; // todo odd => read two bytes
                        if (todo == 2) n = 2; // todo = 2 => read all
                        if (todo == 3) {
                            I2Cx->CR1 = (cr1 &= ~I2C_CR1_ACK); // last byte nack
                        }
                    } else if (todo == 1 && sr1 & I2C_SR1_RXNE) { // last byte
                        n = 1;
                        I2Cx->CR2 &= ~I2C_CR2_ITBUFEN; // disable I2C_SR1_RXNE interrupts
                    }
                    while (n != 0) {
                        if (todo == 2) {
                            I2Cx->CR1 = (cr1 |= I2C_CR1_STOP); // stop after last byte
                        }
                        UINT8 data = I2Cx->DR; // read data
                        *(unit->m_dataQueue.Push()) = data; // save data
                        unit->m_bytesTransferred++;
                        unit->m_bytesToTransfer = --todo; // update todo
                        n--;
                    }
                }
                if (todo == 1) {
                    I2Cx->CR2 |= I2C_CR2_ITBUFEN; // enable I2C_SR1_RXNE interrupt
                }
            }
        }
    } else { // write transaction
        if (sr1 & I2C_SR1_SB) { // start bit
            UINT8 addr = xAction->m_address << 1; // address bits
            I2Cx->DR = addr; // send header byte with write bit;
        } else if (sr1 & I2C_SR1_ADDR || sr1 & I2C_SR1_BTF) { // tx idle
            int n = todo < 2 ? todo : 2; // write at most 2 bytes
            while (n != 0) {
                I2Cx->DR = *(unit->m_dataQueue.Pop()); // next data byte;
                unit->m_bytesTransferred++;
                unit->m_bytesToTransfer--; // no todo update!
                n--;
            }
        }
    }
    
    if (todo == 0) {
        if (!xAction->ProcessingLastUnit()) { // start next unit
            currentI2CUnit = xAction->m_xActionUnits[ xAction->m_current++ ];
            I2Cx->CR1 = I2C_CR1_PE | I2C_CR1_START | I2C_CR1_ACK; // send restart
        } else {
            xAction->Signal(I2C_HAL_XACTION::c_Status_Completed); // calls XActionStop()
        }
    }

    INTERRUPT_END
#endif
 }


BOOL I2C_Internal_Initialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();
#if 0
    if (!(RCC->APB1ENR & RCC_APB1ENR_I2CxEN)) { // only once
        currentI2CXAction = NULL;
        currentI2CUnit = NULL;
        
        CPU_GPIO_DisablePin( I2Cx_SDA_Pin, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_3 ); // open drain
        CPU_GPIO_DisablePin( I2Cx_SCL_Pin, RESISTOR_DISABLED, 0, GPIO_ALT_MODE_3 ); // open drain
        
        RCC->APB1ENR |= RCC_APB1ENR_I2CxEN; // enable I2C clock
        RCC->APB1RSTR = RCC_APB1RSTR_I2CxRST; // reset I2C peripheral
        RCC->APB1RSTR = 0;
        
        I2Cx->CR2 = SYSTEM_APB1_CLOCK_HZ / 1000000; // APB1 clock in MHz
        I2Cx->CCR = (SYSTEM_APB1_CLOCK_HZ / 1000 / 2 - 1) / 100 + 1; // 100KHz
        I2Cx->TRISE = SYSTEM_APB1_CLOCK_HZ / (1000 * 1000) + 1; // 1ns;
        I2Cx->OAR1 = 0x4000; // init address register
        
        I2Cx->CR1 = I2C_CR1_PE; // enable peripheral
        
        CPU_INTC_ActivateInterrupt(I2Cx_EV_IRQn, STM32_I2C_EV_Interrupt, 0);
        CPU_INTC_ActivateInterrupt(I2Cx_ER_IRQn, STM32_I2C_ER_Interrupt, 0);
    }
#endif
    return TRUE;
}

BOOL I2C_Internal_Uninitialize()
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();
#if 0
    CPU_INTC_DeactivateInterrupt(I2Cx_EV_IRQn);
    CPU_INTC_DeactivateInterrupt(I2Cx_ER_IRQn);
    I2Cx->CR1 = 0; // disable peripheral
    RCC->APB1ENR &= ~RCC_APB1ENR_I2CxEN; // disable I2C clock
#endif
    return TRUE;
}

void I2C_Internal_XActionStart( I2C_HAL_XACTION* xAction, bool repeatedStart )
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();

    currentI2CXAction = xAction;
    currentI2CUnit = xAction->m_xActionUnits[ xAction->m_current++ ];
#if 0
    UINT32 ccr = xAction->m_clockRate + (xAction->m_clockRate2 << 8);
    if (I2Cx->CCR != ccr) { // set clock rate and rise time
        UINT32 trise;
        if (ccr & I2C_CCR_FS) { // fast => 0.3ns rise time
            trise = SYSTEM_APB1_CLOCK_HZ / (1000 * 3333) + 1; // PCLK1 / 3333kHz
        } else { // slow => 1.0ns rise time
            trise = SYSTEM_APB1_CLOCK_HZ / (1000 * 1000) + 1; // PCLK1 / 1000kHz
        }
        I2Cx->CR1 = 0; // disable peripheral
        I2Cx->CCR = ccr;
        I2Cx->TRISE = trise;
    }
    
    I2Cx->CR1 = I2C_CR1_PE; // enable and reset special flags
    I2Cx->SR1 = 0; // reset error flags
    I2Cx->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITERREN; // enable interrupts
    I2Cx->CR1 = I2C_CR1_PE | I2C_CR1_START | I2C_CR1_ACK; // send start
#endif
}

void I2C_Internal_XActionStop()
{
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();
#if 0
    if (I2Cx->SR2 & I2C_SR2_BUSY && !(I2Cx->CR1 & I2C_CR1_STOP)) {
        I2Cx->CR1 |= I2C_CR1_STOP; // send stop
    }
    I2Cx->CR2 &= ~(I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN | I2C_CR2_ITERREN); // disable interrupts
    currentI2CXAction = NULL;
    currentI2CUnit = NULL;
#endif
}

void I2C_Internal_GetClockRate( UINT32 rateKhz, UINT8& clockRate, UINT8& clockRate2)
{
#if 0
    NATIVE_PROFILE_HAL_PROCESSOR_I2C();
    if (rateKhz > 400) rateKhz = 400; // upper limit
    UINT32 ccr;
    if (rateKhz <= 100) { // slow clock
        ccr = (SYSTEM_APB1_CLOCK_HZ / 1000 / 2 - 1) / rateKhz + 1; // round up
        if (ccr > 0xFFF) ccr = 0xFFF; // max divider
    } else { // fast clock
        ccr = (SYSTEM_APB1_CLOCK_HZ / 1000 / 3 - 1) / rateKhz + 1; // round up
        ccr |= 0x8000; // set fast mode (duty cycle 1:2)
    }
    clockRate = (UINT8)ccr; // low byte
    clockRate2 = (UINT8)(ccr >> 8); // high byte
#endif
}

void I2C_Internal_GetPins(GPIO_PIN& scl, GPIO_PIN& sda)
{
    scl = I2Cx_SCL_Pin;
    sda = I2Cx_SDA_Pin;
}


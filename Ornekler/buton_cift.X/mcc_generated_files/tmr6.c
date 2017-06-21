/**
  TMR6 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr6.c

  @Summary
    This is the generated driver implementation file for the TMR6 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for TMR6.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.1
        Device            :  PIC16F1827
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr6.h"

/**
  Section: Global Variables Definitions
*/

void (*TMR6_InterruptHandler)(void);

/**
  Section: TMR6 APIs
*/

void TMR6_Initialize(void)
{
    // Set TMR6 to the options selected in the User Interface

    // T6CKPS 1:16; T6OUTPS 1:2; TMR6ON off; 
    T6CON = 0x0A;

    // PR6 249; 
    PR6 = 0xF9;

    // TMR6 0; 
    TMR6 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR3bits.TMR6IF = 0;

    // Enabling TMR6 interrupt.
    PIE3bits.TMR6IE = 1;

    // Set Default Interrupt Handler
    TMR6_SetInterruptHandler(TMR6_DefaultInterruptHandler);

    // Start TMR6
    TMR6_StartTimer();
}

void TMR6_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T6CONbits.TMR6ON = 1;
}

void TMR6_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T6CONbits.TMR6ON = 0;
}

uint8_t TMR6_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR6;

    return readVal;
}

void TMR6_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer6 register
    TMR6 = timerVal;
}

void TMR6_LoadPeriodRegister(uint8_t periodVal)
{
   PR6 = periodVal;
}

void TMR6_ISR(void)
{

    // clear the TMR6 interrupt flag
    PIR3bits.TMR6IF = 0;

    if(TMR6_InterruptHandler)
    {
        TMR6_InterruptHandler();
    }
}


void TMR6_SetInterruptHandler(void* InterruptHandler){
    TMR6_InterruptHandler = InterruptHandler;
}

void TMR6_DefaultInterruptHandler(void){
    // add your TMR6 interrupt custom code
    // or set custom function using TMR6_SetInterruptHandler()
}

/**
  End of File
*/
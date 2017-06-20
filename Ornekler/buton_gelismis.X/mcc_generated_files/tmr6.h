/**
  TMR6 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr6.h

  @Summary
    This is the generated header file for the TMR6 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for TMR6.
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

#ifndef _TMR6_H
#define _TMR6_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif


/**
  Section: Macro Declarations
*/

/**
  Section: TMR6 APIs
*/

/**
  @Summary
    Initializes the TMR6 module.

  @Description
    This function initializes the TMR6 Registers.
    This function must be called before any other TMR6 function is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    main()
    {
        // Initialize TMR6 module
        TMR6_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR6_Initialize(void);

/**
  @Summary
    This function starts the TMR6.

  @Description
    This function starts the TMR6 operation.
    This function must be called after the initialization of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR6 module

    // Start TMR6
    TMR6_StartTimer();

    // Do something else...
    </code>
*/
void TMR6_StartTimer(void);

/**
  @Summary
    This function stops the TMR6.

  @Description
    This function stops the TMR6 operation.
    This function must be called after the start of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR6 module

    // Start TMR6
    TMR6_StartTimer();

    // Do something else...

    // Stop TMR6;
    TMR6_StopTimer();
    </code>
*/
void TMR6_StopTimer(void);

/**
  @Summary
    Reads the TMR6 register.

  @Description
    This function reads the TMR6 register value and return it.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    None

  @Returns
    This function returns the current value of TMR6 register.

  @Example
    <code>
    // Initialize TMR6 module

    // Start TMR6
    TMR6_StartTimer();

    // Read the current value of TMR6
    if(0 == TMR6_ReadTimer())
    {
        // Do something else...

        // Reload the TMR value
        TMR6_Reload();
    }
    </code>
*/
uint8_t TMR6_ReadTimer(void);

/**
  @Summary
    Writes the TMR6 register.

  @Description
    This function writes the TMR6 register.
    This function must be called after the initialization of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    timerVal - Value to write into TMR6 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR6 register
        if(ZERO == TMR6_ReadTimer())
        {
            // Do something else...

            // Write the TMR6 register
            TMR6_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR6_WriteTimer(uint8_t timerVal);

/**
  @Summary
    Load value to Period Register.

  @Description
    This function writes the value to PR6 register.
    This function must be called after the initialization of TMR6.

  @Preconditions
    Initialize  the TMR6 before calling this function.

  @Param
    periodVal - Value to load into TMR6 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD1 0x80
    #define PERIOD2 0x40
    #define ZERO    0x00

    while(1)
    {
        // Read the TMR6 register
        if(ZERO == TMR6_ReadTimer())
        {
            // Do something else...

            if(flag)
            {
                flag = 0;

                // Load Period 1 value
                TMR6_LoadPeriodRegister(PERIOD1);
            }
            else
            {
                 flag = 1;

                // Load Period 2 value
                TMR6_LoadPeriodRegister(PERIOD2);
            }
        }

        // Do something else...
    }
    </code>
*/
void TMR6_LoadPeriodRegister(uint8_t periodVal);

/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR6 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void TMR6_ISR(void);

/**
  @Summary
    Set Timer Interrupt Handler

  @Description
    This sets the function to be called during the ISR

  @Preconditions
    Initialize  the TMR6 module with interrupt before calling this.

  @Param
    Address of function to be set

  @Returns
    None
*/
 void TMR6_SetInterruptHandler(void *InterruptHandler);

/**
  @Summary
    Timer Interrupt Handler

  @Description
    This is a function pointer to the function that will be called during the ISR

  @Preconditions
    Initialize  the TMR6 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
extern void (*TMR6_InterruptHandler)(void);

/**
  @Summary
    Default Timer Interrupt Handler

  @Description
    This is the default Interrupt Handler function

  @Preconditions
    Initialize  the TMR6 module with interrupt before calling this isr.

  @Param
    None

  @Returns
    None
*/
void TMR6_DefaultInterruptHandler(void);


 #ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _TMR6_H
/**
 End of File
*/


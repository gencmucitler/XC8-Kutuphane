/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
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

#include "mcc_generated_files/mcc.h"
#include "zaman.h"
#include "buton.h"


/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    
    // Set Default Interrupt Handler
    TMR6_SetInterruptHandler(_miliSaat);
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    led1_SetHigh();
    led2_SetHigh();
    led3_SetHigh();
    led4_SetHigh();
    __delay_ms(500);
    led1_SetLow();
    led2_SetLow();
    led3_SetLow();
    led4_SetLow();

    while (1) {
        // Add your application code
        //1 nolu butona basýldý mý?
        switch (buton_oku()) {

            case 1: //buton 1
                switch (butonDurumu) {
                    case BASILDI:
                        led1_Toggle();
                        break;
                    case UZUN_BASILDI:
                        led2_Toggle();
                        break;
                    case BIRAKILDI:
                        led1_Toggle();
                        led2_SetLow();
                        break;
                }
                break;
                //--------------------------------

            case 2: //buton 2
                switch (butonDurumu) {
                    case BASILDI:
                        led3_Toggle();
                        break;
                    case UZUN_BASILDI:
                        led4_Toggle();
                        break;
                    case BIRAKILDI:
                        led3_Toggle();
                        led4_SetLow();
                        break;
                }
                break;
                //--------------------------------


        }
    }
}
/**
 End of File
*/
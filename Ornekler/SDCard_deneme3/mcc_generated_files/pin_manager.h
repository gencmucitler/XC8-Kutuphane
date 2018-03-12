/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC18F46K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SD_CS aliases
#define SD_CS_TRIS               TRISCbits.TRISC0
#define SD_CS_LAT                LATCbits.LATC0
#define SD_CS_PORT               PORTCbits.RC0
#define SD_CS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define SD_CS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define SD_CS_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define SD_CS_GetValue()           PORTCbits.RC0
#define SD_CS_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define SD_CS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set SCK1 aliases
#define SCK1_TRIS               TRISCbits.TRISC3
#define SCK1_LAT                LATCbits.LATC3
#define SCK1_PORT               PORTCbits.RC3
#define SCK1_ANS                ANSELCbits.ANSC3
#define SCK1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define SCK1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define SCK1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define SCK1_GetValue()           PORTCbits.RC3
#define SCK1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define SCK1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define SCK1_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define SCK1_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set SDI1 aliases
#define SDI1_TRIS               TRISCbits.TRISC4
#define SDI1_LAT                LATCbits.LATC4
#define SDI1_PORT               PORTCbits.RC4
#define SDI1_ANS                ANSELCbits.ANSC4
#define SDI1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SDI1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SDI1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SDI1_GetValue()           PORTCbits.RC4
#define SDI1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SDI1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SDI1_SetAnalogMode()  do { ANSELCbits.ANSC4 = 1; } while(0)
#define SDI1_SetDigitalMode() do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set SDO1 aliases
#define SDO1_TRIS               TRISCbits.TRISC5
#define SDO1_LAT                LATCbits.LATC5
#define SDO1_PORT               PORTCbits.RC5
#define SDO1_ANS                ANSELCbits.ANSC5
#define SDO1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SDO1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SDO1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SDO1_GetValue()           PORTCbits.RC5
#define SDO1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SDO1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SDO1_SetAnalogMode()  do { ANSELCbits.ANSC5 = 1; } while(0)
#define SDO1_SetDigitalMode() do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode() do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()    do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()   do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()   do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()         PORTCbits.RC7
#define RC7_SetDigitalInput()   do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()  do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode() do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set LED_TEST aliases
#define LED_TEST_TRIS               TRISDbits.TRISD0
#define LED_TEST_LAT                LATDbits.LATD0
#define LED_TEST_PORT               PORTDbits.RD0
#define LED_TEST_ANS                ANSELDbits.ANSD0
#define LED_TEST_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define LED_TEST_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define LED_TEST_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define LED_TEST_GetValue()           PORTDbits.RD0
#define LED_TEST_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define LED_TEST_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define LED_TEST_SetAnalogMode()  do { ANSELDbits.ANSD0 = 1; } while(0)
#define LED_TEST_SetDigitalMode() do { ANSELDbits.ANSD0 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
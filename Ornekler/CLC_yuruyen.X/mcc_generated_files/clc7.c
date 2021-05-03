 /**
   CLC7 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     clc7.c
 
   @Summary
     This is the generated driver implementation file for the CLC7 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for CLC7.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
         Device            :  PIC18F46Q10
         Driver Version    :  2.11
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.31 and above or later
         MPLAB             :  MPLAB X 5.45
 */ 

 /*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include "clc7.h"

/**
  Section: CLC7 APIs
*/

void CLC7_Initialize(void)
{
    // Set the CLC7 to the options selected in the User Interface

    // LC7G1POL not_inverted; LC7G2POL not_inverted; LC7G3POL not_inverted; LC7G4POL inverted; LC7POL not_inverted; 
    CLC7POL = 0x08;
    // LC7D1S T0_overflow; 
    CLC7SEL0 = 0x11;
    // LC7D2S CLC4_OUT; 
    CLC7SEL1 = 0x24;
    // LC7D3S CLCIN0 (CLCIN0PPS); 
    CLC7SEL2 = 0x00;
    // LC7D4S CLC4_OUT; 
    CLC7SEL3 = 0x24;
    // LC7G1D3N disabled; LC7G1D2N disabled; LC7G1D4N disabled; LC7G1D1T enabled; LC7G1D3T disabled; LC7G1D2T disabled; LC7G1D4T disabled; LC7G1D1N disabled; 
    CLC7GLS0 = 0x02;
    // LC7G2D2N disabled; LC7G2D1N disabled; LC7G2D4N disabled; LC7G2D3N disabled; LC7G2D2T enabled; LC7G2D1T disabled; LC7G2D4T disabled; LC7G2D3T disabled; 
    CLC7GLS1 = 0x08;
    // LC7G3D1N disabled; LC7G3D2N disabled; LC7G3D3N disabled; LC7G3D4N disabled; LC7G3D1T disabled; LC7G3D2T disabled; LC7G3D3T disabled; LC7G3D4T disabled; 
    CLC7GLS2 = 0x00;
    // LC7G4D1N disabled; LC7G4D2N disabled; LC7G4D3N disabled; LC7G4D4N disabled; LC7G4D1T disabled; LC7G4D2T disabled; LC7G4D3T disabled; LC7G4D4T enabled; 
    CLC7GLS3 = 0x80;
    // LC7EN enabled; INTN disabled; INTP disabled; MODE JK flip-flop with R; 
    CLC7CON = 0x86;

}


bool CLC7_OutputStatusGet(void)
{
    return(CLC7CONbits.LC7OUT);
}
/**
 End of File
*/

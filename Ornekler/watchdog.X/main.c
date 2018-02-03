/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC16F1827
        Driver Version    :  2.00
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
#include "pcf8574.h"
#include "softi2c.h"
#include "seri_lcd.h"

#include <stdio.h>

__persistent volatile unsigned int Sayi;
volatile unsigned int Sayi2; 

char sayac;

void Sayi_Say(void)
{
    Sayi++;
    Sayi2++;
}

/*
                         Main application
 */

void main(void)
{
    char i;
    
    // initialize the device
    SYSTEM_Initialize();

    TMR1_SetInterruptHandler(Sayi_Say);
    
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
        
    softi2c_kur();   
    lcd_baslat();   
    
    //if(!RCONbits.TO)      //pic18 için
    if(__timeout == 0)
    {
        //watchdog tarafýndan resetlenince çalýþýr.
        lcd_mesajyaz(2,1,"Watchdog Reset");
        __delay_ms(500);
    }
    else
    {   //sadece ilk enerji verildiðinde çalýþýr.
        Sayi=0;
        Sayi2=0;

    }

    
    lcd_mesajyaz(1,1,"Merhaba");
    
    for(i=0;i<2;i++)
    {
        Led_Test_Toggle();
        __delay_ms(250);
    }
        
    while (1)
    {        
        // Add your application code
        lcd_git(2,1);
        printf("S1:%04d S2:%04d",Sayi,Sayi2);
        __delay_ms(100);    
        
        //__delaywdt_ms(100);     //beklerken ayný zamanda da watchdog u sýfýrlar
                                //sadece PIC18 de bu fonksiyon vardýr.
        CLRWDT();
                
        sayac++;
        if(sayac==50)
        {
            while(1);   //sonsuz döngü sistemi kilitler
        }
    }
}
/**
 End of File
*/
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
#include "lcd.h"
#include "zaman.h"
#include "tustakimi.h"
#include <stdio.h>

char tusno;
/*
                         Main application
 */


void tusbilgilerini_yaz(void) {
    lcd_mesajyaz(2, 1, "               ");  //2.Satýrý sil
    lcd_git(2, 1);
    lcd_harfyaz(tusno); //basýlan tuþu yaz.
    lcd_harfyaz(':');
}
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    TMR6_SetInterruptHandler(_miliSaat);
    
    lcd_baslat();
    lcd_sil();
    
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

    lcd_mesajyaz(1,1,"4x4 Tus Takimi");
    while (1)
    {

        
        tusno=tustakimi_oku();
        
        //herhangi bir tusa basýldý ise
        if(tusno)
        {

            
            //buton durumunu yaz.
            switch(butonDurumu)
            {
                case BASILDI:
                    tusbilgilerini_yaz();
                    lcd_mesajyaz(2,3,"BASILDI");
                    break;
                case BASILI_TUTULUYOR:
                    //tusbilgilerini_yaz();
                    //lcd_mesajyaz(2,3,"BASILI TUTULUYOR");
                    break;
                case CIFT_TIKLAMA:
                    tusbilgilerini_yaz();
                    lcd_mesajyaz(2,3,"CIFT TIKLAMA");
                    break;
                case KISA_BASILDI:
                    tusbilgilerini_yaz();
                    lcd_mesajyaz(2,3,"KISA BASILDI");
                    break;
                case UZUN_BASILDI:
                    tusbilgilerini_yaz();
                    lcd_mesajyaz(2,3,"UZUN BASILDI");
                    break;
                case BIRAKILDI:
                    tusbilgilerini_yaz();
                    lcd_mesajyaz(2,3,"BIRAKILDI");
                    break;
            }
        }
        
        /* Örnek Kullaným
        if(tusno=='1' && butonDurumu==BASILDI)
        {
          //iþlem yap..  
        }
        
        if(tusno=='A' && butonDurumu=CIFT_TIKLAMA)
        {
            //iþlem yap.
        }
         */ 
    }
}
/**
 End of File
*/
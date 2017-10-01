
// PIC12F675 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "softusart.h"

#define Led_SetHigh()            do { GPIObits.GP2 = 1; } while(0)
#define Led_SetLow()             do { GPIObits.GP2 = 0; } while(0)

char temp;

/*
 * 
 */
void main(void) {

    //OSCCAL = __osccal_val();

    CMCON = 0x07; //hepsi dijital I/O
    ANSEL = 0x00;

    
 //a   softusart_yaz('a');
//    temp=softusart_oku();
    
    TRISIObits.TRISIO2 = 0; //çýkýþ
       Led_SetHigh();
        __delay_ms(250);
        Led_SetLow();
        __delay_ms(250);
        
        
    softusart_baslat();
    
    printf("Yazýlýmsal UART test.\n");

    while (1) {


        temp = softusart_oku();
        softusart_yaz(temp);

        switch (temp) {
            case 'a':
            case 'A':
                Led_SetHigh();
                break;
            case 'b':
            case 'B':
                Led_SetLow();
                break;
        }


    }
}


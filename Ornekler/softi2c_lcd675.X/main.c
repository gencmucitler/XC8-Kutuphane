
// PIC12F675 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "seri_lcd.h"
#include "softi2c.h"

#define _XTAL_FREQ 4000000

void main(void)
{
    OSCCAL=__osccal_val();
    //giriþ çýkýþ portlarýný ayarla
    CMCON=0x07;
    ANSEL=0x00; //dijital giriþ/çýkýþ
    TRISIObits.TRISIO2=0;
    
    softi2c_kur();
    
    __delay_ms(500);
    lcd_baslat();
    lcd_mesajyaz(1,1,"Selam Millet");
    lcd_mesajyaz(2,1,"PIC12F675 softI2C");
    
    //sonsuz döngü
    while(1)
    {
        GPIObits.GP2=1;
        __delay_ms(500);
        GPIObits.GP2=0;
        __delay_ms(500);
            
    }
}


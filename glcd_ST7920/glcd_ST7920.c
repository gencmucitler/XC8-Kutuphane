/**********************************************************
*  Yazar 	: sigmoid
*  Web 		: http://www.gencmucitler.com
*  Ýlk		: Ocak 2018
*  Düzenleme: Þubat 2018  
*  Versiyon : 0.11
*  Açýklama : ST7920 chipli 128x64 grafik lcd için seri haberleþme 
*  kütüphanesi
***********************************************************/
// v0.11 ufak hata düzeltme

#include "mcc_generated_files/mcc.h"
#include "glcd_ST7920.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char display_kursor_blink;


/******************************************************************************
 * 8 bitlik veriyi seri olarak lcd'ye gönderir.
 *****************************************************************************/
void lcd_seriverigonder(char veri)
{
//    char i;           
//	for(i=0;i<8;i++)
//	{
//        LCD_CLK=1;
//        __delay_us(5);
//		veri=veri<<1;
//		LCD_DI=CARRY;   //PRO mode da bu kod çalýþmýyor..!!!
//        LCD_CLK=0;
//        __delay_us(5);
//
//	}	

    
//    char i;
//	for(i=8;i>0;i--)
//	{
//        LCD_CLK=1;
//        __delay_us(5);		
//		LCD_DI=(veri & (1 << i-1))>>i-1;
//        LCD_CLK=0;
//        __delay_us(5);
//
//	}	
        
    char i;
	for(i=0;i<8;i++)
	{
        LCD_CLK=1;
        __delay_us(25);
        
        if(veri & 0x80)
            LCD_DI=1;
        else
            LCD_DI=0;
        
		veri=veri << 1;
        LCD_CLK=0;
        __delay_us(25);

	}	
}

/******************************************************************************
 * LCD ekran kullanýlmadan önce bu fonksiyon ile çalýþtýrýlmalýdýr.
 *****************************************************************************/
void lcd_baslat()
{
    LCD_CLK=0;
    LCD_CS=0;
    LCD_DI=0;
    __delay_ms(50);    
  
    lcd_komut(0x30);
    __delay_us(50);
    lcd_komut(0x30);
    __delay_us(50);   
    lcd_komut(0x0C);    //display açýk, kürsör ve blink kapalý.
    __delay_us(50);
    lcd_komut(0x01);    //ekraný sil
    __delay_ms(10);
    lcd_komut(0x06);    //entry mode, saða doðru yazýlacak.


    display_kursor_blink=0x0C;
}

/******************************************************************************
 * LCD ekrana 1 bytelýk veri göndermek için 3 bytelýk paketler kullanýlýr.
 * datasheet içinde nasýl olduðu açýklanýyor.
 * RS=1; ekrana yazýlacak veri gönderir.
 *****************************************************************************/
void lcd_harf(char harf)
{
    LCD_CS=1;
    lcd_seriverigonder(0b11111010);     //rs=1 harf gönder.
    lcd_seriverigonder(harf & 0xF0);
    lcd_seriverigonder((harf<<4)&0xf0); 
    LCD_CS=0;
}

/******************************************************************************
 * LCD ekrana 1 bytelýk veri göndermek için 3 bytelýk paketler kullanýlýr.
 * datasheet içinde nasýl olduðu açýklanýyor.
 * RS=0; lcd ekran komutu gönderir.
 *****************************************************************************/
void lcd_komut(char komut)
{
    LCD_CS=1;
    lcd_seriverigonder(0b11111000);     //rs=0 harf gönder.
    lcd_seriverigonder(komut & 0xF0);
    lcd_seriverigonder((komut<<4)&0xf0); 
    LCD_CS=0;
    __delay_us(100);
}


/********************************************************************************
 * Lcdyi siler.                                                                 *
 * Örnek : lcd_sil();                                                           *
 *******************************************************************************/
void lcd_sil()
{
    lcd_komut(0x01);
    __delay_ms(10);
    lcd_display_ac();
}

/********************************************************************************
 * 1. satýr 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satirbasi()
{
    lcd_komut(0x02);
}

/*******************************************************************************
 * Ýstenilen pozisyona gider.                                                   *
 * Örnek: lcd_git(2,5);                                                         *
 *******************************************************************************/
void lcd_git(char satir, char sutun) {
    char temp;          
    switch (satir) {
        case 1:
            temp = sutun - 1 + 0x80;
            break;
        case 2:
            temp = sutun - 1 + 0x90;
            break;
        case 3:
            temp = (sutun - 1 + 0x88);
            break;
        case 4:
            temp = (sutun - 1 + 0x98);
            break;
    }
    lcd_komut(0x30);
    lcd_komut(temp);
}

/*******************************************************************************
 * Ýstenilen poziyonda ekrana yazý yazar.                                       *
 * Örnek : lcd_mesajyaz(1,4,"Deneme");                                          *
 *******************************************************************************/
void lcd_mesajyaz(char satir, char sutun, const char *mesaj) {
    lcd_git(satir, sutun);
    do {
        lcd_harf(*mesaj++);
    } while (*mesaj);
    lcd_display_ac();
}


/*******************************************************************************
 * Lcd ekrana en son kaldýðý pozisyondan itibaren yazý yazar.                   *
 * Örnek : lcd_mesajyaz_cp("deneme");                                           *
 *******************************************************************************/
void lcd_mesajyaz_cp(const char *mesaj) {
    do {
        lcd_harf(*mesaj++);
    } while (*mesaj);
    lcd_display_ac();
}


/*******************************************************************************
 * LCD ekraný saða kaydýrýr.                                                    *
 *******************************************************************************/
void lcd_ekransagakaydir()
{
    lcd_komut(0x1C);
}

/*******************************************************************************
 * LCD ekraný sola kaydýrýr.                                                    *
 *******************************************************************************/
void lcd_ekransolakaydir()
{
    lcd_komut(0x18);
}

/*******************************************************************************
 * Kürsörü saða   kaydýrýr.                                                    *
 *******************************************************************************/
void lcd_kursorsagakaydir()
{
        lcd_komut(0x14);
}

/*******************************************************************************
 * Kürsörü sola   kaydýrýr.                                                    *
 *******************************************************************************/
void lcd_kursorsolakaydir()
{    
        lcd_komut(0x10);
}


/*******************************************************************************
 * Kursörü aktif yapar                                                          *
 *******************************************************************************/
void lcd_kursor_ac(void) {
    display_kursor_blink |= 0x02;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * Kürsörü kapatýr.                                                             *
 *******************************************************************************/
void lcd_kursor_kapat(void) {
    display_kursor_blink &= 0xfd;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * LCD Displayi açar.                                                           *
 *******************************************************************************/
void lcd_display_ac(void) {
    display_kursor_blink |= 0x04;
    lcd_komut(display_kursor_blink);

}

/*******************************************************************************
 * LCD Displayi kapatýr.                                                        *
 * nasýl çalýþtýðýný çözmedim.
 *******************************************************************************/
void lcd_display_kapat(void) {
    display_kursor_blink &= 0xfb;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * Kürsör ekranda yanýp söner                                                   *
 *******************************************************************************/
void lcd_blink_ac(void) {
    display_kursor_blink |= 0x01;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * Kürsörün ekranda yanýp sönme özelliðini kapatýr.                             *
 *******************************************************************************/
void lcd_blink_kapat(void) {
    display_kursor_blink &= 0xfe;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * 1. satýr 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir1(void) {
    lcd_komut(0x80);
}

/*******************************************************************************
 * 2. satýr 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir2(void) {
    lcd_komut(0x90);
}

/*******************************************************************************
 * 3. satýr 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir3(void) {
    lcd_komut(0x88);
}

/*******************************************************************************
 * 4. satýr 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir4(void) {
    lcd_komut(0x98);
}


void lcd_temel_komutseti(void)
{
    lcd_komut(0x30);
}

void lcd_gelismis_komutseti(void)
{
    lcd_komut(0x34);
}

void lcd_satir_tersle(char satirno)
{
    lcd_gelismis_komutseti();
    lcd_komut(0x04-1+satirno);
   // lcd_temel_komutseti();
}
/*******************************************************************************
 * printf fonksiyonu için                                                       *
 *******************************************************************************/
#ifdef lcdprintf_aktif

void putch(unsigned char byte) {
    lcd_harf(byte);
}
#endif
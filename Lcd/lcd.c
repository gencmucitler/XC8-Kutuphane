/*******************************************************************************
 * Kütüphane     : xsLCD                                                       *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 01 Mayýs 2014                                               *
 * Son Düzenleme : 04 Mayýs 2014                                               *
 * Versiyon      : 0.21                                                         *
 *                                                                             *
 * HD44780 karakter LCD kütüphanesi (4bit ve 8 bit modlu)                      *
 ******************************************************************************/
#include "mcc_generated_files/mcc.h"
#include "lcd.h"

//Deðiþkenler
char display_kursor_blink; //display,kursor ve blink aç kapat komutlarý için.

/*******************************************************************************
 *  LCD ekraný çalýþtýrýr. Ýlk önce bu fonksiyon çalýþtýrýlmalýdýr.             *
 *******************************************************************************/
#ifdef LCDBIT8

void lcd_baslat(void) {
    char _i;
    lcd_tris = 0x00; //lcd'nin baðlandýðý pinler çýkýþ
    lcd_tris_rs = 0;
    lcd_tris_e = 0;
#ifdef lcd_rw_aktif
    lcd_tris_rw = 0;
#endif
    __delay_ms(20);
    lcd_rs = 0;
#ifdef lcd_rw_aktif
    lcd_rw = 0;
#endif
    lcd_e = 0;

    lcd_data = 0x38; //8 bit mod
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_us(1);
    __delay_ms(5);

    __delay_us(40);
    lcd_komut(0x0C); //display on
    display_kursor_blink = 0x0C;
    __delay_us(40);
    lcd_komut(0x06); //cursor ileri
    __delay_ms(2);
}
#endif

#ifdef LCDBIT4

void lcd_baslat(void) {
    char i;
#ifdef LCDustpin
    lcd_tris = lcd_tris & 0x0f;
#endif
#ifdef LCDaltpin
    lcd_tris = lcd_tris & 0xf0;
#endif

    lcd_tris_e = 0;
    lcd_tris_rs = 0;
#ifdef lcd_rw_aktif
    lcd_tris_rw = 0;
    lcd_rw = 0;
#endif

    __delay_ms(20);
    lcd_rs = 0;
    lcd_e = 0;
    
    //3 kere 8 bit modda çalýþ diye komut gönder.
    for(i=0;i<3;i++)
    {
 #ifdef LCDustpin
    lcd_data = 0x30 | (lcd_data & 0x0f); //4 bit mod
#endif
#ifdef LCDaltpin
    lcd_data = 0x03 | (lcd_data & 0xf0); //4 bit mod
#endif
        lcd_e = 1;
        __delay_us(1);
        lcd_e = 0;
        __delay_ms(5);
    }
    
    //4 bit modunda çalýþtýr.
#ifdef LCDustpin
    lcd_data = 0x20 | (lcd_data & 0x0f); //4 bit mod
#endif
#ifdef LCDaltpin
    lcd_data = 0x02 | (lcd_data & 0xf0); //4 bit mod
#endif
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_ms(5);
    lcd_komut(0x28);
    __delay_us(40);
    lcd_komut(0x0C); //display on
    __delay_us(40);
    lcd_komut(0x06); //cursor ileri
    __delay_ms(2);
    lcd_komut(0x01); //ekraný sil
}
#endif

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
            temp = sutun - 1 + 0xc0;
            break;
        case 3:
            temp = (sutun - 1 + 0x94);
            break;
        case 4:
            temp = (sutun - 1 + 0xd4);
            break;
    }
    lcd_komut(temp);
    __delay_us(100);
}

/*******************************************************************************
 * Ýstenilen poziyonda ekrana yazý yazar.                                       *
 * Örnek : lcd_mesajyaz(1,4,"Deneme");                                          *
 *******************************************************************************/
void lcd_mesajyaz(char satir, char sutun, const char *mesaj) {
    lcd_git(satir, sutun);
    do {
        lcd_harfyaz(*mesaj++);
    } while (*mesaj);
}

/*******************************************************************************
 * Lcd ekrana en son kaldýðý pozisyondan itibaren yazý yazar.                   *
 * Örnek : lcd_mesajyaz_cp("deneme");                                           *
 *******************************************************************************/
void lcd_mesajyaz_cp(const char *mesaj) {
    do {
        lcd_harfyaz(*mesaj++);
    } while (*mesaj);
}

/*******************************************************************************
 * Lcd meþgul olduðu sürece bu fonksiyon içinde bekler..                        *
 * Lcd_komut ve lcd_harfyaz fonksiyonlarý bu fonksiyonu kullanýr.               *
 *******************************************************************************/
#ifdef lcd_rw_aktif

#ifdef LCDBIT8

void lcd_mesgulmu(void) {
    char temp;
    lcd_rs = 0;
    lcd_rw = 1;
    lcd_tris = 0xff;
    do {
        __delay_us(1);
        lcd_e = 1;
        __delay_us(1);
        lcd_e = 0;
        temp = lcd_read & 0x80;
    } while (temp);
    lcd_tris = 0x00;
}
#endif

#ifdef LCDBIT4

void lcd_mesgulmu(void) {
    char temp, temp2;
    lcd_rs = 0;
    lcd_rw = 1;
#ifdef LCDustpin
    lcd_tris = 0xf0 | lcd_tris;
#endif
#ifdef LCDaltpin
    lcd_tris = 0x0f | lcd_tris;
#endif
    do {
        __delay_us(1);
        lcd_e = 1;
        __delay_us(1);
        lcd_e = 0; //high byte oku
#ifdef LCDustpin
        temp = lcd_read & 0x80;
#endif
#ifdef LCDaltpin
        temp = lcd_read & 0x08;
#endif
        __delay_us(1);
        lcd_e = 1;
        __delay_us(1);
        lcd_e = 0; //low byte oku, ama herhangi bir deðiþkene kaydetmeye gerek yok.
    } while (temp);
#ifdef LCDustpin
    lcd_tris = lcd_tris & 0x0f;
#endif
#ifdef LCDaltpin
    lcd_tris = lcd_tris & 0xf0;
#endif
}
#endif

#else

void lcd_mesgulmu(void) {
    __delay_us(100); //bekle.
}
#endif

/*******************************************************************************
 * Lcd ekrana tek bir harf yazar.                                               *
 * Örnek : lcd_harfyaz('A');                                                    *
 *******************************************************************************/
#ifdef LCDBIT8

void lcd_harfyaz(char harf) {
    lcd_mesgulmu();
    lcd_rs = 1;
#ifdef lcd_rw_aktif
    lcd_rw = 0;
#endif
    lcd_data = harf;
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_us(200);
}
#endif

#ifdef LCDBIT4

void lcd_harfyaz(char harf) {
    lcd_mesgulmu();
    lcd_rs = 1;
#ifdef lcd_rw_aktif
    lcd_rw = 0;
#endif
#ifdef LCDustpin
    lcd_data = (lcd_data & 0x0f) | (harf & 0xf0); //high verisini gönder.
#endif
#ifdef LCDaltpin
    lcd_data = (lcd_data & 0xf0) | (harf >> 4);
#endif
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_us(200);
#ifdef LCDustpin
    lcd_data = (lcd_data & 0x0f) | (harf << 4); //low verisini gönder.
#endif
#ifdef LCDaltpin
    lcd_data = (lcd_data & 0xf0) | (harf & 0x0f);
#endif
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_us(200);
}
#endif

/*******************************************************************************
 * Lcd ekrandan tek bir harf okur                                               *
 *******************************************************************************/
#ifdef lcd_rw_aktif

#ifdef LCDBIT8

char lcd_harfoku(void) {
    char temp;
    lcd_mesgulmu();
    lcd_rs = 1;
    lcd_rw = 1;

    lcd_tris = 0xff;
    lcd_e = 1;
    __delay_us(1);
    temp = lcd_read;
    lcd_e = 0;
    __delay_us(1);
    lcd_tris = 0x00;
    return temp;
}
#endif

#ifdef LCDBIT4
//task: yazýlacak

char lcd_harfoku(void) {
    char temp, harf1, harf2;

    lcd_mesgulmu();
#ifdef LCDustpin
    lcd_tris = 0xf0 | lcd_tris;
#endif
#ifdef LCDaltpin
    lcd_tris = 0x0f | lcd_tris;
#endif

    lcd_rs = 1;
    lcd_rw = 1;

    lcd_e = 1;
    __delay_us(1);
#ifdef LCDustpin
    harf1 = (lcd_read & 0xf0); //high verisini al.
#endif
#ifdef LCDaltpin
    harf1 = (lcd_read & 0x0f) << 4;
#endif
    lcd_e = 0;
    __delay_us(1);

    lcd_e = 1;
    __delay_us(1);
#ifdef LCDustpin
    harf2 = (lcd_read & 0xf0) >> 4; //low verisini al.
#endif
#ifdef LCDaltpin
    harf2 = (lcd_read & 0x0f);
#endif
    lcd_e = 0;
    __delay_us(1);

    temp = harf1 | harf2; //üst ve alt veriyi birleþtir.

#ifdef LCDustpin
    lcd_tris = lcd_tris & 0x0f;
#endif
#ifdef LCDaltpin
    lcd_tris = lcd_tris & 0xf0;
#endif
    return temp;
}
#endif

#endif

/*******************************************************************************
 * Lcd komutlarýný gönderir.                                                    *
 *******************************************************************************/
#ifdef LCDBIT8

void lcd_komut(char komut) {
    lcd_mesgulmu();
    lcd_rs = 0;
#ifdef lcd_rw_aktif
    lcd_rw = 0;
#endif
    lcd_data = komut;
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_ms(5);
}
#endif

#ifdef LCDBIT4

void lcd_komut(char komut) {
    lcd_mesgulmu();
    lcd_rs = 0;
#ifdef lcd_rw_aktif
    lcd_rw = 0;
#endif
#ifdef LCDustpin
    lcd_data = (lcd_data & 0x0f) | (komut & 0xf0); //high verisini gönder.
#endif
#ifdef LCDaltpin
    lcd_data = (lcd_data & 0xf0) | (komut >> 4);
#endif
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_ms(5);
#ifdef LCDustpin
    lcd_data = (lcd_data & 0x0f) | (komut << 4); //low verisini gönder.
#endif
#ifdef LCDaltpin
    lcd_data = (lcd_data & 0xf0) | (komut & 0x0f);
#endif
    lcd_e = 1;
    __delay_us(1);
    lcd_e = 0;
    __delay_ms(5);
}
#endif

/*******************************************************************************
 * Lcd ekranda özel karakter oluþturur.                                         *
 * Örnek:
 * char kalp[8]={
 * 0b00000,
 * 0b01010,
 * 0b10101,
 * 0b10001,
 * 0b01010,
 * 0b00100,
 * 0b00000,
 * 0b00000};
 * 
 * lcd_ozelkarakter(0,kalp);   //kalp sembolü lcd ekrana tanýmlar
 * lcd_harfyaz(0); // kalp sembölünü çiz..
 *******************************************************************************/
void lcd_ozelkarakter(char karakterno, char patern[8]) {
    char temp, i;
    temp = 0x40 | (karakterno << 3);
    lcd_komut(temp);

    for (i = 0; i < 8; i++) {
        lcd_harfyaz(patern[i]);
    }
    lcd_satirbasi();
}

/*******************************************************************************
 * Lcdyi siler.                                                                 *
 * Örnek : lcd_sil();                                                           *
 *******************************************************************************/
void lcd_sil(void) {
    lcd_komut(0x01);
}

/*******************************************************************************
 * 1. sat?r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satirbasi(void) {
    lcd_komut(0x02);
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
 * LCD ekraný sola kaydýrýr.                                                    *
 *******************************************************************************/
void lcd_sola_kaydir(void) {
    lcd_komut(0x18);
}

/*******************************************************************************
 * LCD ekraný saða kaydýrýr.                                                    *
 *******************************************************************************/
void lcd_saga_kaydir(void) {
    lcd_komut(0x1C);
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
    lcd_komut(0xc0);
}

/*******************************************************************************
 * 3. satýr 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir3(void) {
    lcd_komut(0x94);
}

/*******************************************************************************
 * 4. satýr 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir4(void) {
    lcd_komut(0xd4);
}

/*******************************************************************************
 * printf fonksiyonu için                                                       *
 *******************************************************************************/
#ifdef lcdprintf_aktif

void putch(unsigned char byte) {
    lcd_harfyaz(byte);
}
#endif

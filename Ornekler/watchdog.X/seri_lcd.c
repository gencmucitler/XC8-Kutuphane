/*******************************************************************************
 * Kütüphane     : I2C LCD                                                     *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 05 Temmuz 2017                                              *
 * Düzenleme     : 9 Temmuz 2017
 * Versiyon      : 0.31                                                      *
 *                                                                             *
 * PCF8574 modülü ile I2C Lcd kullanım kütüphanesi                             *
 ******************************************************************************/

//v0.31 lcd_baslat içindeki ufak bir data düzeltildi.
//v0.3 softI2C ile de çalışabilecek şekilde düzenleme yapıldı.

#include "mcc_generated_files/mcc.h"
#include "seri_lcd.h"
#include "pcf8574.h"

#ifdef softI2C
#include "softi2c.h"
#endif

//Değişkenler
char display_kursor_blink; //display,kursor ve blink aç kapat komutları için.

//PORT bilgisi
typedef union
{
    //bit düzeyi
    struct{
        char P0:1;      //RS
        char P1:1;      //RW
        char P2:1;      //E
        char P3:1;      //arka aydınlatma
        char P4:1;      //D4
        char P5:1;      //D5
        char P6:1;      //D6
        char P7:1;      //D7
    }pin;
    //bit düzeyi
    struct{
        char RS:1;      //RS
        char RW:1;      //RW
        char E:1;      //E
        char LED:1;      //arka aydınlatma
        char D4:1;      //D4
        char D5:1;      //D5
        char D6:1;      //D6
        char D7:1;      //D7       
    }lcd;
    //byte
    char port;
}_PCF_PORT;


_PCF_PORT pcf_port;

/*******************************************************************************
 *  PCF8574 üzerinden veriyi gönderdikten sonra enable pinini high-low yapar.  *
 *******************************************************************************/
void pcf8574_yaz_wEnable() {

    #ifdef softI2C
    
    softi2c_baslat();
    softi2c_yaz(pcf_adres <<1);
    softi2c_yaz(lcd_data);
    pcf_port.lcd.E=1;
    softi2c_yaz(lcd_data);
    pcf_port.lcd.E=0;
    softi2c_yaz(lcd_data);
    softi2c_durdur();  
    
#else
    
    I2C1_MESSAGE_STATUS status;
    uint8_t writeBuffer[3];
    uint16_t timeOut;

    writeBuffer[0] = lcd_data;
    pcf_port.lcd.E = 1;
    writeBuffer[1] = lcd_data;
    pcf_port.lcd.E = 0;
    writeBuffer[2] = lcd_data;
    
    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        
        //3 byte gönder
        I2C1_MasterWrite(writeBuffer,
                3,
                pcf_adres,
                &status);

        // veri gönderilene kadar bekle.
        while (status == I2C1_MESSAGE_PENDING);

        //başarılı olarak gönderildi isi çık
        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        //Veri gönderilmediyse tekrar gönder.
        //Başarısız tekrar sayısına ulaşıldıysa da çık.
        if (timeOut == pcf_tekrar)
            break;
        else
            timeOut++;
    }
#endif
    
}

/*******************************************************************************
 *  LCD ekranı çalıştırır. İlk önce bu fonksiyon çalıştırılmalıdır.             *
 *******************************************************************************/
void lcd_baslat(void) {
    char i;
    
    __delay_ms(15);
    
    pcf8574_yaz(0x00);
    lcd_data=0x00;

    for(i=0;i<3;i++)
    {
        lcd_data=0x00;
        lcd_data = 0x30 | (lcd_data & 0x0f); //8 bit mod
        pcf8574_yaz_wEnable();
        __delay_ms(5);
    }   //2 kere 4bit modunda çalışacağını duyur. Garantiye al :)    
    
    __delay_us(150);
    
    lcd_data=0x00;
    lcd_data = 0x20 | (lcd_data & 0x0f); //4 bit mod
    pcf8574_yaz_wEnable();
    __delay_ms(5);
            
    lcd_komut(0x28);
    __delay_us(40);
    lcd_komut(0x0C); //display on
    __delay_us(40);
    lcd_komut(0x06); //cursor ileri
    __delay_ms(2);
        
    lcd_sil();
    lcd_aydinlatma_ac();
}


/*******************************************************************************
 * İstenilen pozisyona gider.                                                   *
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
 * İstenilen poziyonda ekrana yazı yazar.                                       *
 * Örnek : lcd_mesajyaz(1,4,"Deneme");                                          *
 *******************************************************************************/
void lcd_mesajyaz(char satir, char sutun, const char *mesaj) {
    lcd_git(satir, sutun);
    do {
        lcd_harfyaz(*mesaj++);
    } while (*mesaj);
}

/*******************************************************************************
 * Lcd ekrana en son kaldığı pozisyondan itibaren yazı yazar.                   *
 * Örnek : lcd_mesajyaz_cp("deneme");                                           *
 *******************************************************************************/
void lcd_mesajyaz_cp(const char *mesaj) {
    do {
        lcd_harfyaz(*mesaj++);
    } while (*mesaj);
}

/*******************************************************************************
 * Lcd meşgul olduğu sürece bu fonksiyon içinde bekler..                        *
 * Lcd_komut ve lcd_harfyaz fonksiyonları bu fonksiyonu kullanır.               *
 *******************************************************************************/
void lcd_mesgulmu(void) {
    __delay_us(100); //bekle.
}

/*******************************************************************************
 * Lcd ekrana tek bir harf yazar.                                               *
 * Örnek : lcd_harfyaz('A');                                                    *
 *******************************************************************************/
void lcd_harfyaz(char harf) {
    lcd_mesgulmu();
    lcd_rs = 1;     //harf

    lcd_data = (lcd_data & 0x0f) | (harf & 0xf0); //high verisini gönder.
    pcf8574_yaz_wEnable();
    __delay_us(200);

    lcd_data = (lcd_data & 0x0f) | (harf << 4); //low verisini gönder.
    pcf8574_yaz_wEnable();
    __delay_us(200);
}


/*******************************************************************************
 * Lcd komutlarını gönderir.                                                    *
 *******************************************************************************/
void lcd_komut(char komut) {
    lcd_mesgulmu();
    lcd_rs = 0;     //komut

    lcd_data = (lcd_data & 0x0f) | (komut & 0xf0); //high verisini gönder.
    pcf8574_yaz_wEnable();
    __delay_ms(5);
    
    lcd_data = (lcd_data & 0x0f) | (komut << 4); //low verisini gönder.
    pcf8574_yaz_wEnable();
    __delay_ms(5);
}

/*******************************************************************************
 * Lcd ekranda özel karakter oluşturur.                                         *
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
 * lcd_ozelkarakter(0,kalp);   //kalp sembolü lcd ekrana tanımlar
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
 * Kürsörü kapatır.                                                             *
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
 * LCD Displayi kapatır.                                                        *
 *******************************************************************************/
void lcd_display_kapat(void) {
    display_kursor_blink &= 0xfb;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * Kürsör ekranda yanıp söner                                                   *
 *******************************************************************************/
void lcd_blink_ac(void) {
    display_kursor_blink |= 0x01;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * Kürsörün ekranda yanıp sönme özelliğini kapatır.                             *
 *******************************************************************************/
void lcd_blink_kapat(void) {
    display_kursor_blink &= 0xfe;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * LCD ekranı sola kaydırır.                                                    *
 *******************************************************************************/
void lcd_sola_kaydir(void) {
    lcd_komut(0x18);
}

/*******************************************************************************
 * LCD ekranı sağa kaydırır.                                                    *
 *******************************************************************************/
void lcd_saga_kaydir(void) {
    lcd_komut(0x1C);
}

/*******************************************************************************
 * 1. satır 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir1(void) {
    lcd_komut(0x80);
}

/*******************************************************************************
 * 2. satır 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir2(void) {
    lcd_komut(0xc0);
}

/*******************************************************************************
 * 3. satır 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir3(void) {
    lcd_komut(0x94);
}

/*******************************************************************************
 * 4. satır 1. sutuna gider                                                     *
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

/*******************************************************************************
 * LCD arkaplan aydınlatmayı aç                                                *
 *******************************************************************************/
void lcd_aydinlatma_ac(void)
{
    pcf_port.lcd.LED=1;
    pcf8574_yaz(pcf_port.port);
}

/*******************************************************************************
 * LCD arkaplan aydınlatmayı kapat                                             *
 *******************************************************************************/
void lcd_aydinlatma_kapat(void)
{
    pcf_port.lcd.LED=0;
    pcf8574_yaz(pcf_port.port);
}

/*******************************************************************************
 * Kütüphane     : I2C LCD                                                     *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 05 Temmuz 2017                                              *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 * PCF8574 modülü ile I2C Lcd kullanım kütüphanesi                             *
 ******************************************************************************/

/*      Standart LCD ayak bağlantıları
1: Gnd  2: Vcc  3: Vee - Kontras ayağı
4: RS   5: RW   6: E
7: D0   8: D1   9: D2   10: D3  11: D4  12: D5  13: D6  14: D7
15: Backlight Vcc       16: Backlight Gnd                                     */

/*PCF8574A entegresinin lcd ekran bağlantısı
 * 
 * P0: RS
 * P1: RW
 * P2: E
 * P3: aydınlatma
 * P4: D4
 * P5: D5
 * P6: D6
 * P7: D7
 */

#define pcf_adres   0x3F    //i2c entegresinin adresi

//printf fonksiyonu lcd'ye yazacak mı?
#define lcdprintf_aktif

// kullanılacak lcd ayaklar?
#define lcd_data	pcf_port.port

#define lcd_rs          pcf_port.lcd.RS
#define lcd_e           pcf_port.lcd.E
#define lcd_rw           pcf_port.lcd.RW


//fonksiyon prototipleri
void lcd_baslat(void);
void lcd_git(char satir, char sutun);
void lcd_mesajyaz(char satir, char sutun, const char *mesaj);
void lcd_mesajyaz_cp(const char *mesaj);
void lcd_mesgulmu(void);
void lcd_harfyaz(char harf);
void lcd_ozelkarakter(char karakterno,char patern[8]);
void lcd_komut(char komut);
void lcd_sil(void);
void lcd_satirbasi(void);
void lcd_kursor_ac(void);
void lcd_kursor_kapat(void);
void lcd_display_ac(void);
void lcd_display_kapat(void);
void lcd_blink_ac(void);
void lcd_blink_kapat(void);
void lcd_sola_kaydir(void);
void lcd_saga_kaydir(void);
void lcd_satir1(void);
void lcd_satir2(void);
void lcd_satir3(void);
void lcd_satir4(void);
void lcd_aydinlatma_ac(void);
void lcd_aydinlatma_kapat(void);
#ifdef lcdprintf_aktif
void putch(unsigned char byte);
#endif

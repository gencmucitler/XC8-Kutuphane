/*******************************************************************************
 * Yazar     : sigmoid                                                         *
 * Web       : http://www.gencmucitler.com                                     *
 * Tarih     : 01 Mayýs 2014                                                   *
 * Düzenleme : 20 Mayýs 2017                                                   *
 * Versiyon  : 0.2                                                             *
 *                                                                             *
 * HD44780 karakter LCD  kütüphanesi                                           *
 ******************************************************************************/

/*      Standart LCD ayak baðlantýlarý
1: Gnd  2: Vcc  3: Vee - Kontras ayaðý
4: RS   5: RW   6: E
7: D0   8: D1   9: D2   10: D3  11: D4  12: D5  13: D6  14: D7
15: Backlight Vcc       16: Backlight Gnd                                     */


//#define LCDBIT8    //lcd ekrana 8bit mi eriþilecek
#define LCDBIT4    //yoksa 4 bit mi?

#ifdef LCDBIT4
//#define LCDustpin     //4bit eriþilecekse hangi pinler kullanýlacak
#define LCDaltpin
#endif

//RW pini PIC'e mi yoksa Topraða mý baðlý
//#define lcd_rw_aktif

//printf fonksiyonu lcd'ye yazacak mý?
#define lcdprintf_aktif

// kullanýlacak lcd ayaklar?
#define lcd_data	LATB
#define lcd_read    PORTB
#define lcd_tris	TRISB

#define lcd_rs          LATA6
#define lcd_tris_rs     TRISA6
#define lcd_e           LATA7
#define lcd_tris_e      TRISA7

#ifdef lcd_rw_aktif
#define lcd_rw          LATA1
#define lcd_tris_rw     TRISA1
#endif

//fonksiyon prototipleri
void lcd_baslat(void);
void lcd_git(char satir, char sutun);
void lcd_mesajyaz(char satir, char sutun, const char *mesaj);
void lcd_mesajyaz_cp(const char *mesaj);
#ifdef lcd_rw_aktif
    void lcd_mesgulmu(void);
    char lcd_harfoku(void);
#endif
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
#ifdef lcdprintf_aktif
void putch(unsigned char byte);
#endif

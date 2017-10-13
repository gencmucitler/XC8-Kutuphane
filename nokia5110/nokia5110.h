/**********************************************************
*  Yazar 	: sigmoid
*  Web 		: http://www.gencmucitler.com
*  ?lk		: Ekim 2017
*  Düzenleme: Yok 
*  Versiyon : 0.2
*  Açýklama : Nokia 5110 Kütüphanesi  (pcd8544)
***********************************************************/

#include "mcc_generated_files/mcc.h"
//printf kullanmak için
#define lcdprintf_aktif

//Nokia LCD Ekran PIN Tanýmlamalarý
#define LCD_RST         LATB7
#define LCD_RST_TRIS    TRISB7
#define LCD_CE          LATB6
#define LCD_CE_TRIS     TRISB6
#define LCD_DC          LATB3
#define LCD_DC_TRIS     TRISB3
#define LCD_DATA        LATB4
#define LCD_DATA_TRIS   TRISB4
#define LCD_CLK         LATB5
#define LCD_CLK_TRIS    TRISB5

//rakam font büyüklüðü
#define BUYUK   1
#define NORMAL  0

//fonksiyon prototipleri
void lcd_veriyaz(char veri);
void lcd_baslat(void);
void lcd_git(char satir, char sutun);
void lcd_mesajyaz(char satir, char sutun, const char *mesaj);
void lcd_mesajyaz_cp(const char *mesaj);
void lcd_harfyaz(char harf);
void lcd_sil();
void lcd_satirsil(char satir);
void lcd_kontrast_artir(void);
void lcd_kontrast_azalt(void);
void lcd_ekrani_tersle(void);
void lcd_normalmode(void);

void lcd_sayiyaz(char satir, char sutun,char* sayi,char font);
void lcd_resimciz(char satir,char sutun,const char *resim);

#ifdef lcdprintf_aktif
void putch(unsigned char byte);
#endif
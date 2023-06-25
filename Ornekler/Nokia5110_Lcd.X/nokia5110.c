/**********************************************************
*  Yazar 	: sigmoid
*  İlk		: Ekim 2017
*  Düzenleme: Yok 
*  Versiyon : 0.1
*  Açıklama : Nokia 5110 Kütüphanesi (pcd8544)
***********************************************************/

#include "nokia5110.h"
char lcd_kontrast=0xB1; //lcd kontrastı B1 ile BF arasında ayarlayınızç

/*******************************************************************************
 *  LCD ekran için karakter tanımlamaları. Standart Font                       *
 *******************************************************************************/
const char harftablo[] ={0x00, 0x00, 0x00, 0x00, 0x00, // SPACE  0
                         0x00, 0x00, 0x5F, 0x00, 0x00, // !	1
                         0x00, 0x03, 0x00, 0x03, 0x00, // "	2
                         0x14, 0x3E, 0x14, 0x3E, 0x14, // #	3
                         0x24, 0x2A, 0x7F, 0x2A, 0x12, // $	4
                         0x43, 0x33, 0x08, 0x66, 0x61, // %	5
                         0x36, 0x49, 0x55, 0x22, 0x50, // &	6
                         0x00, 0x05, 0x03, 0x00, 0x00, // '	7
                         0x00, 0x1C, 0x22, 0x41, 0x00, // (	8
                         0x00, 0x41, 0x22, 0x1C, 0x00, // )	9
                         0x14, 0x08, 0x3E, 0x08, 0x14, // *	10
                         0x08, 0x08, 0x3E, 0x08, 0x08, // +	11
                         0x00, 0x50, 0x30, 0x00, 0x00, // ,	12
                         0x08, 0x08, 0x08, 0x08, 0x08, // -	13	
                         0x00, 0x60, 0x60, 0x00, 0x00, // .	14
                         0x20, 0x10, 0x08, 0x04, 0x02, // /	15
                         0x3E, 0x51, 0x49, 0x45, 0x3E, // 0	16
                         0x04, 0x02, 0x7F, 0x00, 0x00, // 1	17
                         0x42, 0x61, 0x51, 0x49, 0x46, // 2	18
                         0x22, 0x41, 0x49, 0x49, 0x36, // 3	19
                         0x18, 0x14, 0x12, 0x7F, 0x10, // 4	20
                         0x27, 0x45, 0x45, 0x45, 0x39, // 5	21
                         0x3E, 0x49, 0x49, 0x49, 0x32, // 6	22
                         0x01, 0x01, 0x71, 0x09, 0x07, // 7	23
                         0x36, 0x49, 0x49, 0x49, 0x36, // 8	24
                         0x26, 0x49, 0x49, 0x49, 0x3E, // 9	25
                         0x00, 0x36, 0x36, 0x00, 0x00, // :	26
                         0x00, 0x56, 0x36, 0x00, 0x00, // ;	27
                         0x08, 0x14, 0x22, 0x41, 0x00, // <	28
                         0x14, 0x14, 0x14, 0x14, 0x14, // =	29
                         0x00, 0x41, 0x22, 0x14, 0x08, // >	30
                         0x02, 0x01, 0x51, 0x09, 0x06, // ?	31
                         0x3E, 0x41, 0x59, 0x55, 0x5E, // @	32
                         0x7E, 0x09, 0x09, 0x09, 0x7E, // A	33
                         0x7F, 0x49, 0x49, 0x49, 0x36, // B	34
                         0x3E, 0x41, 0x41, 0x41, 0x22, // C	35
                         0x7F, 0x41, 0x41, 0x41, 0x3E, // D	36
                         0x7F, 0x49, 0x49, 0x49, 0x41, // E	37
                         0x7F, 0x09, 0x09, 0x09, 0x01, // F	38
                         0x3E, 0x41, 0x41, 0x49, 0x3A, // G	39
                         0x7F, 0x08, 0x08, 0x08, 0x7F, // H	40
                         0x00, 0x41, 0x7F, 0x41, 0x00, // I	41
                         0x30, 0x40, 0x40, 0x40, 0x3F, // J	42
                         0x7F, 0x08, 0x14, 0x22, 0x41, // K	43
                         0x7F, 0x40, 0x40, 0x40, 0x40, // L	44
                         0x7F, 0x02, 0x0C, 0x02, 0x7F, // M	45
                         0x7F, 0x02, 0x04, 0x08, 0x7F, // N	46
                         0x3E, 0x41, 0x41, 0x41, 0x3E, // O	47
                         0x7F, 0x09, 0x09, 0x09, 0x06, // P	48
                         0x1E, 0x21, 0x21, 0x21, 0x5E, // Q	49
                         0x7F, 0x09, 0x09, 0x09, 0x76,// R	50
                         0x26, 0x49, 0x49, 0x49, 0x32, // S	51
                         0x01, 0x01, 0x7F, 0x01, 0x01, // T	52
                         0x3F, 0x40, 0x40, 0x40, 0x3F, // U	53
                         0x1F, 0x20, 0x40, 0x20, 0x1F, // V	54
                         0x7F, 0x20, 0x10, 0x20, 0x7F, // W	55
                         0x41, 0x22, 0x1C, 0x22, 0x41, // X	56
                         0x07, 0x08, 0x70, 0x08, 0x07, // Y	57
                         0x61, 0x51, 0x49, 0x45, 0x43, // Z	58
                         0x00, 0x7F, 0x41, 0x00, 0x00, // [	59
                         0x02, 0x04, 0x08, 0x10, 0x20, // \	60
                         0x00, 0x00, 0x41, 0x7F, 0x00, // ]	61
                         0x04, 0x02, 0x01, 0x02, 0x04, // ^	62
                         0x40, 0x40, 0x40, 0x40, 0x40, // _	63
                         0x00, 0x01, 0x02, 0x04, 0x00, // `	64
                         0x20, 0x54, 0x54, 0x54, 0x78, // a	65
                         0x7F, 0x44, 0x44, 0x44, 0x38, // b	66
                         0x38, 0x44, 0x44, 0x44, 0x44, // c	67
                         0x38, 0x44, 0x44, 0x44, 0x7F, // d	68
                         0x38, 0x54, 0x54, 0x54, 0x18, // e	69
                         0x04, 0x04, 0x7E, 0x05, 0x05, // f	70
                         0x08, 0x54, 0x54, 0x54, 0x3C, // g	71
                         0x7F, 0x08, 0x04, 0x04, 0x78, // h	72
                         0x00, 0x44, 0x7D, 0x40, 0x00, // i	73
                         0x20, 0x40, 0x44, 0x3D, 0x00, // j	74
                         0x7F, 0x10, 0x28, 0x44, 0x00, // k	75
                         0x00, 0x41, 0x7F, 0x40, 0x00, // l	76
                         0x7C, 0x04, 0x78, 0x04, 0x78, // m	77
                         0x7C, 0x08, 0x04, 0x04, 0x78, // n	78
                         0x38, 0x44, 0x44, 0x44, 0x38, // o	79
                         0x7C, 0x14, 0x14, 0x14, 0x08, // p	80
                         0x08, 0x14, 0x14, 0x14, 0x7C, // q	81
                         0x00, 0x7C, 0x08, 0x04, 0x04, // r	82
                         0x48, 0x54, 0x54, 0x54, 0x20, // s	83
                         0x04, 0x04, 0x3F, 0x44, 0x44, // t	84
                         0x3C, 0x40, 0x40, 0x20, 0x7C, // u	85
                         0x1C, 0x20, 0x40, 0x20, 0x1C, // v	86
                         0x3C, 0x40, 0x30, 0x40, 0x3C, // w	87
                         0x44, 0x28, 0x10, 0x28, 0x44, // x	88
                         0x0C, 0x50, 0x50, 0x50, 0x3C, // y	89
                         0x44, 0x64, 0x54, 0x4C, 0x44, // z	90
                         0x00, 0x08, 0x36, 0x41, 0x41, // {	91
                         0x00, 0x00, 0x7F, 0x00, 0x00, // |	92
                         0x41, 0x41, 0x36, 0x08, 0x00, // }	93
                         0x02, 0x01, 0x02, 0x04, 0x02, // ~	94
		     0x1E, 0x21, 0x61, 0x21, 0x12, // Ç 199	95      //türkçe karakterler
			 0x3D, 0x42, 0x52, 0x52, 0x75, // Ğ 208	96
			 0x3C, 0x43, 0x42, 0x43, 0x3C, // Ö 214	97
			 0x3C, 0x41, 0x40, 0x41, 0x3C, // Ü 220	98
			 0x00, 0x42, 0x7F, 0x42, 0x00, // İ 221	99
			 0x46, 0x49, 0x69, 0x49, 0x31, // Ş 222	100
			 0x1C, 0x22, 0x62, 0x22, 0x10, // ç 231	101
			 0x0D, 0x52, 0x52, 0x52, 0x3D, // ğ 240	102
			 0x38, 0x46, 0x44, 0x46, 0x38, // ö 246	103
			 0x3C, 0x41, 0x40, 0x21, 0x7C, // ü 252	104
			 0x00, 0x44, 0x7C, 0x40, 0x00, // ı 253	105
			 0x24, 0x2A, 0x6A, 0x2A, 0x10};// ş 254	106

/*******************************************************************************
 *  LCD ekranı çalıştırır. İlk önce bu fonksiyon çalıştırılmalıdır.             *
 *******************************************************************************/
void lcd_baslat(void) {    
    LCD_CE_TRIS = 0;    //çıkış olarak tanımla
    LCD_CLK_TRIS = 0;
    LCD_DATA_TRIS = 0;
    LCD_DC_TRIS = 0;
    LCD_RST_TRIS = 0;
    
    LCD_DATA=0;
    LCD_CLK=0;
    LCD_DC=0;
    
    //Lcd ekranı resetle
    LCD_RST=0;    
    LCD_RST=1;
    
    LCD_DC=0;   //KOMUT setini seç
    lcd_veriyaz(0x21);              //chip aktif, yatay adresleme, uzatılmış komut seti
    lcd_veriyaz(lcd_kontrast);      //LCD kontrastı düşük olarak ayarla.
    lcd_veriyaz(0x04);              //Temp coefficent ayarı
    lcd_veriyaz(0x14);              //LCD bias mode 1:48: Try 0x13 or 0x14
    lcd_veriyaz(0x20);              //temel komut seti
    lcd_veriyaz(0x0C);              //normal mode aktif     
}

/*******************************************************************************
 * İstenilen pozisyona gider.                                                   *
 * Örnek: lcd_git(2,5);                                                         *
 *******************************************************************************/
void lcd_git(char satir, char sutun)
{
    LCD_DC=0;
    lcd_veriyaz(0x40 | satir);
    lcd_veriyaz(0x80 | (sutun*6));
}

/*******************************************************************************
 * İstenilen poziyonda ekrana yazı yazar.                                       *
 * Örnek : lcd_mesajyaz(1,4,"Deneme");                                          *
 *******************************************************************************/
void lcd_mesajyaz(char satir, char sutun, const char *mesaj)
{
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
 * Lcd ekrana tek bir harf yazar.                                               *
 * Örnek : lcd_harfyaz('A');                                                    *
 *******************************************************************************/
void lcd_harfyaz(char harf) 
{
    int adres;
    LCD_DC=1;   //veri modu
   
    switch(harf)
	{
		case 'Ç':   //türkçe karakterler için adres bilgisini yeniden tanımla
			adres=475;
			break;
		case 'Ğ':
			adres=480;
			break;
		case 'Ö':
			adres=485;
			break;
		case 'Ü':
			adres=490;
			break;
		case 'İ':
			adres=495;
			break;			
		case 'Ş':
			adres=500;
			break;
		case 'ç':
			adres=505;
			break;
		case 'ğ':
			adres=510;
			break;
		case 'ö':
			adres=515;
			break;
		case 'ü':
			adres=520;		
			break;	
		case 'ı':
			adres=525;
			break;					
		case 'ş':
			adres=530;
			break;
		default:
			adres=(harf-' ')*5;   //ASCII Tablosuna göre space karakteri 
                                  //tablonun ilk karakteri
			break;			
	}	

	lcd_veriyaz(harftablo[adres++]);
	lcd_veriyaz(harftablo[adres++]);
	lcd_veriyaz(harftablo[adres++]);
	lcd_veriyaz(harftablo[adres++]);
	lcd_veriyaz(harftablo[adres++]);
    lcd_veriyaz( 0x00); //boşluk ekle
}

/*******************************************************************************
 * Lcd ekranı tamamen siler                                                    *
 *******************************************************************************/
void lcd_sil()
{
    int i;
    lcd_git(0,0);
 
    LCD_DC=1;
    for(i=0;i<504;i++)
    {
        lcd_veriyaz(0x00);  //tüm ekranı boşlukla doldur.
    }
   
    lcd_git(0,0);
}

/*******************************************************************************
 * Lcd ekranda istenilen satırı siler.                                         *
 *******************************************************************************/
void lcd_satirsil(char satir)
{
     char i;
    lcd_git(satir,0);
 
    LCD_DC=1;
    for(i=0;i<84;i++)
    {
        lcd_veriyaz(0x00);  //tüm ekranı boşlukla doldur.
    }
   
    lcd_git(satir,0);   
}

/*******************************************************************************
 * Lcd ekran kontrastını artırır     .                                         *
 *******************************************************************************/
void lcd_kontrast_artir(void)
{
//  b1 ile bf arasında değişsin.
//    LCD_DC=0;   //KOMUT setini seç
//    lcd_veriyaz(0x21);              //chip aktif, yatay adresleme, uzatılmış komut seti
//    lcd_veriyaz(lcd_kontrast++);
    lcd_veriyaz(0x20);              //temel komut seti
}

/*******************************************************************************
 * Lcd ekran kontrastını azaltır                                               *
 *******************************************************************************/
void lcd_kontrast_azalt(void)
{
//    LCD_DC=0;   //KOMUT setini seç
//    lcd_veriyaz(0x21);              //chip aktif, yatay adresleme, uzatılmış komut seti
//    lcd_veriyaz(lcd_kontrast--);
 //   lcd_veriyaz(0x20);              //temel komut seti
}

/*******************************************************************************
 * Lcd ekrandaki grafikleri ters gösterir.                                     *
 *******************************************************************************/
void lcd_ekrani_tersle(void)
{
    LCD_DC=0;
    lcd_veriyaz(0x0D);              //inverse video mode aktif
    
}

/*******************************************************************************
 * Lcd ekran normal mode çalıştır                                              *
 *******************************************************************************/
void lcd_normalmode(void)
{
    LCD_DC=0;
    lcd_veriyaz(0x0C);              //normal video mode aktif
}



/*******************************************************************************
 * Lcd ekrana 1 bytelık veriyi göderir.                                        *
 *******************************************************************************/
void lcd_veriyaz(char veri)
{
    char i;
    
    LCD_CE=0;   //lcd yi seç
    
    for(i=0;i<8;i++)
    {
        veri=veri<<1;   //ilk önce MSB gönderilir.
        LCD_DATA=CARRY;
        LCD_CLK=1;
        __delay_us(1);
        LCD_CLK=0;
    }
    
    LCD_CE=1;
}

/*******************************************************************************
 * printf fonksiyonu için                                                      *
 *******************************************************************************/
#ifdef lcdprintf_aktif
void putch(unsigned char byte) {
    lcd_harfyaz(byte);
}
#endif

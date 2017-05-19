/**********************************************************
*  Web 		: http://www.gencmucitler.com
*  Ýlk		: Aðustos 2008
*  Düzenleme: Mayýs 2017 
*  Versiyon : 0.4
*  Açýklama : Piyasada rahatlýkla bulunan HD44780 karakter lcd ekran kütüphanesi.
*			  Lcd ye 4 bit modda eriþim saðlanýr.
 *            XC8 için gerekli düzenlemeler yapýldý.
***********************************************************/

#include "mcc_generated_files/mcc.h"
#include "lcd4bit.h"


/*
*  Standart LCD ayak baðlantýlarý
*  1: Gnd
*  2: Vcc
*  3: Vee : Kontras ayaðý. 10K pot veya 1K direnç ile þaseye baðla.
*  4: RS
*  5: RW
*  6: E
*  7: D0 - gnd ye baðla
*  8: D1 - gnd ye baðla
*  9: D2 - gnd ye baðla
* 10: D3 - gnd ye baðla
* 11: D4 highport aktifse 4 e deðilse 0 a baðla.
* 12: D5 highport aktifse 5 e deðilse 1 a baðla.
* 13: D6 highport aktifse 6 e deðilse 2 a baðla.
* 14: D7 highport aktifse 7 e deðilse 3 a baðla.
* 15: Backlight Vcc
* 16: Backlight Gnd
*/



/***********************************************************
*  Lcd ekraný çalýþtýrýr. Diðer fonksiyonlar kullanýlmadan önce ilk olarak bu çalýþtýrýlmalýdýr.
*/
void lcd_baslat(void)
{
    //lcd_tris=0x00;
#ifdef lcd_highport
    lcd_tris = 0x0F & lcd_tris; //4 bit mod
#else
    lcd_tris = 0xF0 & lcd_tris; //4 bit mod
#endif

    tris_lcd_e = 0;
    tris_lcd_rs = 0;
	
	__delay_ms(15);
	lcd_rs=0;
    
#ifdef mesgulbitioku
	lcd_rw=0;
    tris_lcd_rw=0;
#endif
    
	lcd_e=0;
	#ifdef lcd_highport
		lcd_data=0x20 | (lcd_data & 0x0f);	//4 bit mod
	#else
		lcd_data=0x02 | (lcd_data &0xf0);	//4 bit mod
	#endif
	lcd_e=1;
	__delay_us(1);
	lcd_e=0;
	__delay_us(40);
	lcd_komut(0x28);
	__delay_us(40);
    lcd_komut(0x0C);  //display on
	__delay_us(40);    
    lcd_komut(0x06);  //cursor ileri	
	__delay_ms(1);
}

/*********************************************************
* Ýstenilen pozisyona gider.
* Örnek lcd_git(2,5);
*/
void lcd_git(char satir, char sutun)
{
	char temp;
	switch(satir)
	{
		case 1:
			temp=sutun-1+ 0x80;
			break;
		case 2:
			temp= sutun-1+0xc0;
			break;
		case 3:
			temp= (sutun-1+0x94);
			break;
		case 4:
			temp= (sutun-1+0xd4);
			break;
	}	
	lcd_komut(temp);
	__delay_us(100);
}
	
/***********************************************************
* Ýstenilen posziyonda ekrana string yazar.
* Örnek : lcd_mesajyaz(1,4,"Deneme");
*/
void lcd_mesajyaz(char satir, char sutun, const char *mesaj)
{
	char temp;
	switch(satir)
	{
		case 1:
			temp=sutun-1+ 0x80;
			break;
		case 2:
			temp= sutun-1+0xc0;
			break;
		case 3:
			temp= (sutun-1+0x94);
			break;
		case 4:
			temp= (sutun-1+0xd4);
			break;
	}	
	lcd_komut(temp);
	__delay_us(100);;
	do
	{
		lcd_harfyaz(*mesaj++);
	}while(*mesaj);
}


/***********************************************************
* Lcd ekrana en son kaldýðý pozisyondan itibaren string yazar. 
* Örnek : lcd_mesajyaz_cp("deneme");
*/
void lcd_mesajyaz_cp(const char *mesaj)
{
	do
	{
		lcd_harfyaz(*mesaj++);
	}while(*mesaj);
}

/***********************************************************
* Lcd meþgul olduðu sürece bu fonksiyon içinde bekler..
* Lcd_komut ve lcd_harfyaz fonksiyonlarý bu fonksiyonu kullanýr.
*/
#ifdef mesgulbitioku

void lcd_mesgulmu(void)
{
	char temp,temp2;
	lcd_rs=0;
	lcd_rw=1;
	#ifdef lcd_highport
		lcd_tris=0xf0 | lcd_tris;
	#else
		lcd_tris=0x0f | lcd_tris;	
	#endif
	do
	{
		__delay_us(1);		
		lcd_e=1;
		__delay_us(1);
		lcd_e=0;	//high byte oku
		#ifdef lcd_highport
			temp=lcd_read & 0x80;
		#else
			temp=lcd_read & 0x08;
		#endif
		__delay_us(1);		
		lcd_e=1;
		__delay_us(1);
		lcd_e=0;	//low byte oku, ama herhangi bir deðiþkene kaydetmeye gerek yok.
	}while(temp);
	#ifdef lcd_highport	
		lcd_tris=lcd_tris & 0x0f;	
	#else
		lcd_tris=lcd_tris & 0xf0;
	#endif
}
#else

void lcd_mesgulmu(void)
{
	__delay_us(100);
}

#endif

/***********************************************************
* Lcd ekrana tek bir harf yazar.
* Örnek : lcd_harfyaz('A');
*/
void lcd_harfyaz(char harf)
{
	lcd_mesgulmu();
	lcd_rs=1;
#ifdef mesgulbitioku
    lcd_rw = 0;
#endif
	#ifdef lcd_highport
		lcd_data = (lcd_data & 0x0f) | (harf & 0xf0);	//high verisini gönder.
	#else
		lcd_data = (lcd_data & 0xf0) | (harf >>4);
	#endif	
	lcd_e=1;
	__delay_us(1);
	lcd_e=0;	
	__delay_us(1);
	#ifdef lcd_highport
		lcd_data = (lcd_data & 0x0f) | (harf << 4);  //low verisini gönder.
	#else
		lcd_data = (lcd_data & 0xf0) | (harf & 0x0f);
	#endif	
	lcd_e=1;
	__delay_us(1);
	lcd_e=0;	
	__delay_us(1);
}

/***********************************************************
* Lcd komutlarýný gönderir.
*/	
void lcd_komut(char komut)
{
	lcd_mesgulmu();
	lcd_rs=0;
#ifdef mesgulbitioku
    lcd_rw = 0;
#endif
	#ifdef lcd_highport
		lcd_data = (lcd_data & 0x0f) | (komut & 0xf0);	//high verisini gönder.
	#else
		lcd_data = (lcd_data & 0xf0) | (komut >>4);
	#endif	
	lcd_e=1;
	__delay_us(1);	
	lcd_e=0;	
	__delay_us(1);
	#ifdef lcd_highport
		lcd_data = (lcd_data & 0x0f) | (komut << 4);  //low verisini gönder.
	#else
		lcd_data = (lcd_data & 0xf0) | (komut & 0x0f);
	#endif	
	lcd_e=1;
	__delay_us(1);	
	lcd_e=0;	
	__delay_us(1);
}
	
/***********************************************************
* Lcdyi siler.
* Örnek : lcd_sil();
*/
void lcd_sil(void)
{
	lcd_komut(0x01);
#ifndef mesgulbitioku
	__delay_ms(2);
#endif
}

/***********************************************************
* Kursörü aktif yapar
* Örnek : lcd_kursorac();
*/
void lcd_kursorac(void)
{
	lcd_komut(0x0F);
}

/***********************************************************
* Kürsörü kapatýr.
*/
void lcd_kursorkapat(void)
{
	lcd_komut(0x0C);
}

/***********************************************************
* 1. satýr 1. sutuna gider
*/
void lcd_satirbasi(void)
{
	lcd_komut(0x02);
}

/***********************************************************
* 1. satýr 1. sutuna gider
*/
void lcd_satir1(void)
{
	lcd_komut(0x80);
}

/***********************************************************
* 2. satýr 1. sutuna gider
*/
void lcd_satir2(void)
{
	lcd_komut(0xc0);
}

/***********************************************************
* 3. satýr 1. sutuna gider 
*/
void lcd_satir3(void)
{
	lcd_komut(0x94);
}

/***********************************************************
* 4. satýr 1. sutuna gider
*/
void lcd_satir4(void)
{
	lcd_komut(0xd4);
}

/* Printf fonksiyonu için.
*/
void putch(unsigned char byte)
{
	lcd_harfyaz(byte);
}


/*
v0.3 #define mesgulbitioku parametresi eklendi. Bu sayede meþgul biti okunarak mý yoksa
sabit bir süremi bekleneceði belirleniyor. Proteusta Meþgul biti özelliði çalýþmýyor.

v0.2 lcd_git() fonksiyonu eklendi.
*/
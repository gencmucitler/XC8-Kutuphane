/**********************************************************
*  Yazar 	: sigmoid
*  Web 		: http://www.gencmucitler.com
*  İlk		: 9 Temmuz 2017
*  Düzenleme: Yok 
*  Versiyon : 0.1
*  Açıklama :  software i2c master mode
*  100KHz bağlantı hızı..
***********************************************************/
#include "mcc_generated_files/mcc.h"
#include "softi2c.h"



//diğer fonksiyonlar çalıştırılmadan önce ilk olarak bu çalıştırılmalı
void __attribute__((optimize(0))) softi2c_kur(void)
{
	SOFT_SCL=1;
	SOFT_SDA=1;
	SOFT_SCL_TRIS=0;	//çıkış
	SOFT_SDA_TRIS=1;	//high empedans - giriş
}	

//start sinyalini gönderir
void __attribute__((optimize(0))) softi2c_baslat(void)
{
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SDA_TRIS=0;	//çıkış
	SOFT_SDA=0;	// Clock high konumda iken 1 den 0 a düş.
	__delay_us(4);
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;	//giriş	
}
	
//stop sinyalini gönderir
void __attribute__((optimize(0))) softi2c_durdur(void)
{
	SOFT_SDA_TRIS=0;
	SOFT_SDA=0;
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SDA_TRIS=1;	//Clock high konumunda iken 0 dan 1e çık.
	__delay_us(4);
}

//restart sinyalini gönderir	
void __attribute__((optimize(0))) softi2c_yenidenbaslat(void)
{
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SDA_TRIS=0;	//çıkış
	SOFT_SDA=0;	// Clock high konumda iken 1 den 0 a düş.
	__delay_us(4);
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;	//giriş	
}

//1 byte veri gönderir, ack sinyalini okur
char __attribute__((optimize(0))) softi2c_yaz(char veri)
{
	char i,temp;
	SOFT_SCL=0;
	for(i=8;i>0;i--)
	{
		veri=veri<<1;
		if(CARRY==0)
		{
			SOFT_SDA_TRIS=0;
			SOFT_SDA=0;
		}	
		else
		{
			SOFT_SDA_TRIS=1;
			SOFT_SDA=1;
		}	
		SOFT_SCL=1;
		__delay_us(4);
		SOFT_SCL=0;
		SOFT_SDA_TRIS=1;
	}	
	//0 dönerse ack alınmış demektir.
		SOFT_SCL=0;
		SOFT_SDA_TRIS=1;
		__delay_us(4);
		SOFT_SCL=1;
		temp=SOFT_SDA;	//ack değerini al.
		SOFT_SCL=0;
		
		return temp;
		
}

//1 byte veri okur, ack sinyali gönderir.
char __attribute__((optimize(0))) softi2c_oku(char onay)
{
	char i,veri=0;
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;
	for(i=8;i>0;i--)
	{
		veri=veri<<1;
		SOFT_SCL=1;
		__delay_us(4);
		if(SOFT_SDA==1)
		{
			veri= veri | 0x01;
		}	
		SOFT_SCL=0;
        __delay_us(2);	
	}	
	//onay kodunu gönder..
	if(onay==0)
	{
		SOFT_SDA_TRIS=0;
		SOFT_SDA=0;
	}	
	else
	{
		SOFT_SDA_TRIS=1;
		SOFT_SDA=1;
	}	
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;
	
	return veri;
}
	

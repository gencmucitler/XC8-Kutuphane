/**********************************************************
*  Yazar 	: sigmoid
*  Ýlk		: 9 Temmuz 2017
*  Düzenleme: Yok 
*  Versiyon : 0.11
*  Açýklama :  software i2c master mode
*  100KHz baðlantý hýzý..
***********************************************************/

#ifndef softI2C
#define softI2C
#endif

#ifndef ack	
	#define ack	0	//acknowledge
#endif

#ifndef noack 
	#define noack	1	//not acknowledge
#endif


//kullanýlacak pinler tanýmlanýr
#define SOFT_SCL	LATDbits.LATD2
#define SOFT_SDA	PORTDbits.RD3


#define SOFT_SCL_TRIS   TRISDbits.TRISD2
#define SOFT_SDA_TRIS	TRISDbits.TRISD3

void softi2c_kur(void);
void softi2c_baslat(void);
void softi2c_durdur(void);
void softi2c_yenidenbaslat(void);
char softi2c_yaz(char veri);
char softi2c_oku(char onay);

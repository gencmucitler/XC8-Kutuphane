/**********************************************************
*  Yazar 	: sigmoid
*  ?lk		: Eylül 2017
*  Düzenleme: Yok 
*  Versiyon : 0.1
*  Açıklama : Yazılımsal olarak gerçekleştirilmiş RS232
*    8 bit data no parity
***********************************************************/

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 4000000
#endif

#define USARTHIZ 9600	//istenilen bağlantı hızını yazın.      
#define usartdelaycyc (_XTAL_FREQ/4) / USARTHIZ  //bağlantı hızını hesapla
#define usartdelaycycyarim usartdelaycyc/2

#define softrxpintris	TRISIO5
#define softtxpintris	TRISIO4
#define softrxpin	GPIO5
#define softtxpin	GPIO4

//soft usart içindeki kullanınan fonksiyonlardan komutların çalışma süresinin çıkartılması
#define sucyc1 21
#define sucyc2 19

#define sucyc1rcv 20
#define sucyc2rcv 29

void softusart_baslat(void);
char softusart_oku(void);
void softusart_yaz(char veri);
void putch(unsigned char byte);

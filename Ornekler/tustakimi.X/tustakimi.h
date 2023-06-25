/*******************************************************************************
 * Kütüphane     : 4x4 Tuş Takımı Okuma Kütüphanesi                            *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * 4x4 matriks tuş takımı kütüphanesi                                          *
 ******************************************************************************/

//Portun 0..3 çıkış 4..7 giriş yapılmalı. Kısaca Satırlar çıkış, sutünlar giriş 
//yapılmalı. Giriş portları pull-up direnci takılmalı veya internal pull-up 
//aktif edilmelidir.

#define SATIR1  LATBbits.LATB0        //satırlar
#define SATIR2  LATBbits.LATB1
#define SATIR3  LATBbits.LATB2
#define SATIR4  LATBbits.LATB3

#define SUTUN1  PORTBbits.RB4        //sütunlar
#define SUTUN2  PORTBbits.RB5
#define SUTUN3  PORTBbits.RB6
#define SUTUN4  PORTBbits.RB7


// tuş takımı patterni
const char tuslar[]={   '1','2','3','A',
                        '4','5','6','B',
                        '7','8','9','C',
                        '*','0','#','D'    
};

#define debounce_suresi 20u         // 20ms
#define cift_tiklama_suresi 250u    // iki kez tıklama için gereken maksimum süre.
#define kisa_basma_suresi   300u    // kısa basma süresi çift tıklama süresinden 
                                    // uzun girilmeli.
#define uzun_basma_suresi   1500u   //2saniye

typedef enum _buton_durum_e
{
    SERBEST=0,          //buton basılmadığında boşta ise.
    DEBOUNCE,           //buton basılma anındaki kontak sıcraması(debounce) testi için
    BASILDI,            //1 kez çalışır
    BASILI_TUTULUYOR,   //butona basılıyor
    CIFT_TIKLAMA,       //iki kez peş peşe butona basılıp bırakılınca tetiklenir.
    KISA_BASILDI,       //butona kısa bir süre basılınca 1 kez tetiklenir.
    UZUN_BASILDI,       //buton belirtilen süre boyunca basılırsa 1 kez çalışır.
    DEBOUNCE2,          //buton bırakılma anındaki kontak sıcraması(debounce) testi için
    BIRAKILDI           //1 kez çalışır.
}buton_durum_e;

//Değişken Tanımlamaları
buton_durum_e butonDurumu=SERBEST;

//fonksiyon prototipleri
char tustakimi_oku(void);
char buton_kontrol(void);

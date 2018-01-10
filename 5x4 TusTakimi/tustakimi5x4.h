/*******************************************************************************
 * Kütüphane     : 5x4 Tuþ Takýmý Okuma Kütüphanesi                            *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * 4x4 matriks tuþ takýmý kütüphanesi                                          *
 ******************************************************************************/

//SATIRLAR çýkýþ, SUTUNLAR giriþ yapýlmalý.  Giriþ portlarý pull-up direnci 
//takýlmalý veya internal pull-up aktif edilmelidir.

#define SATIR1  LATCbits.LATC7        //satýrlar
#define SATIR2  LATDbits.LATD4
#define SATIR3  LATDbits.LATD5
#define SATIR4  LATDbits.LATD6
#define SATIR5  LATDbits.LATD7

#define SUTUN1  PORTBbits.RB3        //sütunlar
#define SUTUN2  PORTBbits.RB2
#define SUTUN3  PORTBbits.RB1
#define SUTUN4  PORTBbits.RB0


// tuþ takýmý patterni
const char tuslar[]={   'Q','W','#','*',    //F1   F2  #    *   
                        '1','2','3','Y',    //1    2   3     Yukarý
                        '4','5','6','A',    //4    5   6     Aþaðý
                        '7','8','9','C',    //7    8   9     Çýkýþ /ESC
                        'L','0','R','G'     //Left 0   Right Giriþ/Enter
};

#define debounce_suresi 20u         // 20ms
#define cift_tiklama_suresi 250u    // iki kez týklama için gereken maksimum süre.
#define kisa_basma_suresi   300u    // kýsa basma süresi çift týklama süresinden 
                                    // uzun girilmeli.
#define uzun_basma_suresi   1500u   //2saniye

typedef enum _buton_durum_e
{
    SERBEST=0,          //buton basýlmadýðýnda boþta ise.
    DEBOUNCE,           //buton basýlma anýndaki kontak sýcramasý(debounce) testi için
    BASILDI,            //1 kez çalýþýr
    BASILI_TUTULUYOR,   //butona basýlýyor
    CIFT_TIKLAMA,       //iki kez peþ peþe butona basýlýp býrakýlýnca tetiklenir.
    KISA_BASILDI,       //butona kýsa bir süre basýlýnca 1 kez tetiklenir.
    UZUN_BASILDI,       //buton belirtilen süre boyunca basýlýrsa 1 kez çalýþýr.
    DEBOUNCE2,          //buton býrakýlma anýndaki kontak sýcramasý(debounce) testi için
    BIRAKILDI           //1 kez çalýþýr.
}buton_durum_e;

//Deðiþken Tanýmlamalarý
buton_durum_e butonDurumu=SERBEST;

//fonksiyon prototipleri
char tustakimi_oku(void);
char buton_kontrol(void);

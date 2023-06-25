/*******************************************************************************
 * Kütüphane     : Gelişmiş Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 18 Haziran 2017                                             *
 * Düzenleme     : 22 Haziran 2017                                             *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 * Butonların kontak sıçrama durumlarınıda dikkate alarak buton durumunu okur. *
 * Bu fonksiyon ile butona basılma, bırakılma, uzun basılma,basılı tutulma     *
 * durumları kolayca okunabilmektedir.                                         * 
 ******************************************************************************/
// v0.2 Basılı Tutuluyor kodu sonuna return butonNo eklendi.
//      Çift tıklama ve Kısa Basma durumları eklendi.
// v0.1 ilk düzenleme.

#ifndef BUTON_H
#define	BUTON_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#define buton1 PORTBbits.RB0
#define buton2 PORTBbits.RB1
#define buton3 PORTBbits.RB2

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
char buton_oku(void);
char buton_kontrol(void);
#endif	/* BUTON_H */


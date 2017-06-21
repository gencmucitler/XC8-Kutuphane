/*******************************************************************************
 * Kütüphane     : Geliþmiþ Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 18 Haziran 2017                                             *
 * Düzenleme     : 22 Haziran 2017                                             *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 * Butonlarýn kontak sýçrama durumlarýnýda dikkate alarak buton durumunu okur. *
 * Bu fonksiyon ile butona basýlma, býrakýlma, uzun basýlma,basýlý tutulma     *
 * durumlarý kolayca okunabilmektedir.                                         * 
 ******************************************************************************/
// v0.2 Basýlý Tutuluyor kodu sonuna return butonNo eklendi.
//      Çift týklama ve Kýsa Basma durumlarý eklendi.
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
char buton_oku(void);
char buton_kontrol(void);
#endif	/* BUTON_H */


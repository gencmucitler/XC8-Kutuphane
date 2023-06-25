/*******************************************************************************
 * Kütüphane     : Gelişmiş Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * Butonların kontak sıçrama durumlarınıda dikkate alarak buton durumunu okur. *
 * Bu fonksiyon ile butona basılma, bırakılma, uzun basılma,basılı tutulma     *
 * durumları kolayca okunabilmektedir.                                         * 
 ******************************************************************************/

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

#define debounce_suresi 20u         //20ms
#define uzun_basma_suresi   2000u   //2saniye

typedef enum _buton_durum_e
{
    SERBEST=0,          //buton basılmadığında boşta ise.
    DEBOUNCE,           //buton basılma anındaki kontak sıcraması(debounce) testi için
    BASILDI,            //1 kez çalışır
    BASILI_TUTULUYOR,   //butona basılıyor
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


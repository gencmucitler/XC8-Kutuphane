/*******************************************************************************
 * Kütüphane     : PCF8574 I2C I/O Expander                                    *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 4 Temmuz 2017                                               *
 * Düzenleme     : 9 Temmuz 2017
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 * PCF8574 giriş/çıkış port çoğullayıcı                                        *
 ******************************************************************************/

//pcf_adres değeri ile chip in adres kodu girilmelidir. Adres bilgisi datasheetten 
//öğrenebilirsiniz. PCF8574 ile PCF8574A nın adres kodları farklıdır. Bu sayede 
//aynı hatta 8 adet PCF8574 ve 8 adet PCF8574A bağlanabilir. Böylece toplamda
//16 adet port çoğaltıcı bağlanılabilinir.

//v0.2 softI2C ilede çalışabilecek şekilde düzenleme yapıldı.


#ifndef PCF8574_H
#define	PCF8574_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#ifndef pcf_adres
#define pcf_adres   0x3F    //entegrenin adresi
#endif

#define softI2C             //yazılımsal I2C fonksiyonlarını kullan.

#define pcf_tekrar   10     //hatalı gönderimde tekrar deneme sayısı

//fonksiyon prototipleri

void pcf8574_yaz(char veri);


#endif	/* PCF8574_H */


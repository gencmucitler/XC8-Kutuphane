/*******************************************************************************
 * Kütüphane     : PCF8574 I2C I/O Expander                                    *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 4 Temmuz 2017                                               *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * PCF8574 giriþ/çýkýþ port çoðullayýcý                                        *
 ******************************************************************************/

//pcf_adres deðeri ile chip in adres kodu girilmelidir. Adres bilgisi datasheetten 
//öðrenebilirsiniz. PCF8574 ile PCF8574A nýn adres kodlarý farklýdýr. Bu sayede 
//ayný hatta 8 adet PCF8574 ve 8 adet PCF8574A baðlanabilir. Böylece toplamda
//16 adet port çoðaltýcý baðlanýlabilinir.


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

#define pcf_tekrar   10     //hatalý gönderimde tekrar deneme sayýsý

//fonksiyon prototipleri

void pcf8574_yaz(char veri);


#endif	/* PCF8574_H */


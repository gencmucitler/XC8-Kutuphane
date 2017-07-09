/*******************************************************************************
 * Kütüphane     : PCF8574 I2C I/O Expander                                    *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 4 Temmuz 2017                                               *
 * Düzenleme     : 9 Temmuz 2017
 * Versiyon      : 0.2                                                        *
 *                                                                             *
 * PCF8574 giriþ/çýkýþ port çoðullayýcý                                        *
 ******************************************************************************/

//pcf_adres deðeri ile chip in adres kodu girilmelidir. Adres bilgisi datasheetten 
//öðrenebilirsiniz. PCF8574 ile PCF8574A nýn adres kodlarý farklýdýr. Bu sayede 
//ayný hatta 8 adet PCF8574 ve 8 adet PCF8574A baðlanabilir. Böylece toplamda
//16 adet port çoðaltýcý baðlanýlabilinir.

//v0.2 softI2C ilede çalýþabilecek þekilde düzenleme yapýldý.

#include <xc.h>
#include "pcf8574.h"

#ifdef softI2C
#include "softi2c.h"
#endif

void pcf8574_yaz(char veri) {
    
#ifdef softI2C
    
    softi2c_baslat();
    softi2c_yaz(pcf_adres <<1);
    softi2c_yaz(veri);
    softi2c_durdur();   
#else
    
    I2C1_MESSAGE_STATUS status;
    uint8_t writeBuffer[1];
    uint16_t timeOut;

    writeBuffer[0] = veri;
    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        
        //1 byte gönder
        I2C1_MasterWrite(writeBuffer,
                1,
                pcf_adres,
                &status);

        // veri gönderilene kadar bekle.
        while (status == I2C1_MESSAGE_PENDING);

        //baþarýlý olarak gönderildi isi çýk
        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        //Veri gönderilmediyse tekrar gönder.
        //Baþarýsýz tekrar sayýsýna ulaþýldýysa da çýk.
        if (timeOut == pcf_tekrar)
            break;
        else
            timeOut++;
    }
#endif

}


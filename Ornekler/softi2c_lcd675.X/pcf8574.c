/*******************************************************************************
 * Kütüphane     : PCF8574 I2C I/O Expander                                    *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 4 Temmuz 2017                                               *
 * Düzenleme     : 9 Temmuz 2017
 * Versiyon      : 0.2                                                        *
 *                                                                             *
 * PCF8574 giriş/çıkış port çoğullayıcı                                        *
 ******************************************************************************/

//pcf_adres değeri ile chip in adres kodu girilmelidir. Adres bilgisi datasheetten 
//öğrenebilirsiniz. PCF8574 ile PCF8574A nın adres kodları farklıdır. Bu sayede 
//aynı hatta 8 adet PCF8574 ve 8 adet PCF8574A bağlanabilir. Böylece toplamda
//16 adet port çoğaltıcı bağlanılabilinir.

//v0.2 softI2C ilede çalışabilecek şekilde düzenleme yapıldı.

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

        //başarılı olarak gönderildi isi çık
        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        //Veri gönderilmediyse tekrar gönder.
        //Başarısız tekrar sayısına ulaşıldıysa da çık.
        if (timeOut == pcf_tekrar)
            break;
        else
            timeOut++;
    }
#endif

}


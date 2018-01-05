/*******************************************************************************
 * Kütüphane     : Easydriver Adým motor kütüphanesi                           *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 4 Ocak 2018                                                 *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 ******************************************************************************/

#include "mcc_generated_files/mcc.h"
#include "easydriver.h"
#include <math.h>

void adimMotor(unsigned int adimSayisi, char adimYonu) {
    unsigned int i, j, adim;
    unsigned int maxAdimAdeti, hizlanmaAdimAdeti, yavaslamaAdimAdeti, yavaslamaadim;
    unsigned int minbekleme,maxbekleme,farkbekleme,bekleme;
    
    //hýzlanma yavaþlama ve maksimum hýzda gidecek adým sayýlarýný hesapla.
    minbekleme=_sure/_minumum_hiz;      //minumum hýz için bekleme süresini hesapla
    maxbekleme=_sure/_maksimum_hiz;     //maksimum hýz için bekleme süresini hesapla
 
    //çýkýþ ve iniþ rampalarýndaki adým sayýsýný hesapla
    farkbekleme=minbekleme-maxbekleme;   
    
    hizlanmaAdimAdeti=farkbekleme*_hizlanmaadimi;
    yavaslamaAdimAdeti=farkbekleme*_yavaslamaadimi;

    //atýlacak adým sayýsý maksimum hýza ulaþmak için yeterli mi?
    if(adimSayisi<(hizlanmaAdimAdeti+yavaslamaAdimAdeti))
    {
        hizlanmaAdimAdeti=(unsigned int)(((unsigned long)adimSayisi*_hizlanmaadimi)/(_hizlanmaadimi+_yavaslamaadimi));
        yavaslamaAdimAdeti=adimSayisi-hizlanmaAdimAdeti;
        maxAdimAdeti=0;
    }
    else
    {
        
        maxAdimAdeti=adimSayisi-hizlanmaAdimAdeti-yavaslamaAdimAdeti;
    }
    
    

    //adým yönünü ayarla.
    step_DIR = adimYonu;

    adim = 0;
    bekleme=minbekleme;

    //hizlanma bölümü
    while (adim <hizlanmaAdimAdeti) {
        for (i = 0; i < _hizlanmaadimi; i++) {
            step_PULSE = 1;
            step_bekle(bekleme);
            step_PULSE = 0;
            step_bekle(bekleme);
            
            adim++;            
            if(adim>=hizlanmaAdimAdeti)
                break;   //döngüden çýk
        }
        
        bekleme--;  //bir kademe hýzlan.
        if(bekleme==maxbekleme)
            break;

    }

    //maksimum hýzda gideceði bölüm
    if (maxAdimAdeti > 0) {
        bekleme=maxbekleme;
        for (i = 0; i < maxAdimAdeti; i++) {
            step_PULSE = 1;
            step_bekle(bekleme);
            step_PULSE = 0;
            step_bekle(bekleme);
        }
        adim = adim + maxAdimAdeti;
    }

    //yavaþlama bölümü
    yavaslamaadim=0;
    while (yavaslamaadim < yavaslamaAdimAdeti) {
        for (i = 0; i < _yavaslamaadimi; i++) {
            step_PULSE = 1;
            step_bekle(bekleme);
            step_PULSE = 0;
            step_bekle(bekleme);
            adim++;

            if (adim>=adimSayisi) //atýlacak adým adeti dolunca fonksiyondan çýk.
                return;
        }
        yavaslamaadim = yavaslamaadim + _yavaslamaadimi;
        bekleme++;
    }
}

//------------------------------------------------------------------------------

void adimMotorDerece(unsigned int adimDerece, char adimYonu) {
    unsigned int adimSayisiSonuc;    
    adimSayisiSonuc=(unsigned int)(((unsigned long)adimDerece*motorAdimi)/360);    
    adimMotor(adimSayisiSonuc,adimYonu);    
}

//------------------------------------------------------------------------------

void step_bekle(unsigned int sure) {
    unsigned int i;

    for (i = 0; i < sure; i++)
        __delay_us(10);
}
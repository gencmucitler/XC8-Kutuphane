/*******************************************************************************
 * Kütüphane     : 28BYJ-48 Adým motor kütüphanesi                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 17 Aralýk  2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 ******************************************************************************/

#include "mcc_generated_files/mcc.h"
#include "step28byj-48.h"

char adim=0;
    
//adým motoru kaç adýmla gideceðini belirtir.
void adimMotor(unsigned int adimSayisi,char adimYonu,unsigned int adimHizi)
{
    unsigned int i,j;

    for (i = 0; i < adimSayisi; i++) {

        //1 adým at
        if (adimYonu == saatYonunde) {
            adim++;
            if (adim == 8)
                adim = 0;
        } else {
            adim--;
            if (adim == 0xFF)
                adim = 7;

        }

        switch (adim) {
            case 0:
                motorPin_Turuncu = 1;
                motorPin_Sari = 0;
                motorPin_Pembe = 0;
                motorPin_Mavi = 0;
                break;
            case 1:
                motorPin_Turuncu = 1;
                motorPin_Sari = 1;
                motorPin_Pembe = 0;
                motorPin_Mavi = 0;
                break;
            case 2:
                motorPin_Turuncu = 0;
                motorPin_Sari = 1;
                motorPin_Pembe = 0;
                motorPin_Mavi = 0;
                break;
            case 3:
                motorPin_Turuncu = 0;
                motorPin_Sari = 1;
                motorPin_Pembe = 1;
                motorPin_Mavi = 0;
                break;
            case 4:
                motorPin_Turuncu = 0;
                motorPin_Sari = 0;
                motorPin_Pembe = 1;
                motorPin_Mavi = 0;
                break;
            case 5:
                motorPin_Turuncu = 0;
                motorPin_Sari = 0;
                motorPin_Pembe = 1;
                motorPin_Mavi = 1;
                break;
            case 6:
                motorPin_Turuncu = 0;
                motorPin_Sari = 0;
                motorPin_Pembe = 0;
                motorPin_Mavi = 1;
                break;
            case 7:
                motorPin_Turuncu = 1;
                motorPin_Sari = 0;
                motorPin_Pembe = 0;
                motorPin_Mavi = 1;
                break;
        }

        for(j=0;j<adimHizi;j++)
                __delay_ms(1);
    }
}

//derece vererek kontrol saðlanýr.  
void adimMotorDerece(unsigned int adimDerece,char adimYonu,unsigned int adimHizi)
{
    unsigned int adimSayisiSonuc;
    
    adimSayisiSonuc=(unsigned int)(((unsigned long)adimDerece*motorAdimi)/360);
    
    adimMotor(adimSayisiSonuc,adimYonu,adimHizi);
}
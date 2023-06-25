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

#include "mcc_generated_files/mcc.h"
#include "buton.h"
#include "zaman.h"

unsigned long butonSure;
char butonNo,oncekiButon;
bit uzunBasildi;

//Basılan butonun numarasını döndürür. Hiç bir butona basılmadı ise 0x00 döner.
char buton_oku(void)
{
    butonNo=0;
    
    //basılı olan butonu bul.
    if(!buton1)
        butonNo=1;
    else if(!buton2)
        butonNo=2;
//    else if(!buton3)
//        butonNo=3;
                
    return buton_kontrol();
}


//Buton durumunu ve kontak sıçramasını test eder.
char buton_kontrol(void)
{
    switch(butonDurumu)
    {
        case SERBEST:   //ilk defa basıldığında 
            if(butonNo>0) 
            {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE;
                oncekiButon = butonNo;
                uzunBasildi=0;
            }
            else
            {
                oncekiButon=0;
                return 0x00;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE:
            //aynı butona basılmaya devam mı ediliyor?
            //kontak sıçramasını atla
            if(butonNo>0) 
            {
                if (butonNo == oncekiButon) 
                {
                    if (miliSaniye() - butonSure > debounce_suresi) 
                    {
                        butonDurumu = BASILDI;      //bir defalık pals üret.
                        butonSure = miliSaniye();
                        return butonNo;
                    }
                } 
                else
                {
                    //farklı butona basılmış.
                    oncekiButon=butonNo;
                    butonSure=miliSaniye();
                }
            }
            else
            {
                //kontak anlık 0'a düştüyse veya bırakıldıysa
                butonDurumu=SERBEST;
            }
            break; 
            //------------------------------------------------------------------
        case BASILDI:   
            if(butonNo>0)
            {
                butonDurumu=BASILI_TUTULUYOR;
                butonSure=miliSaniye();
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case BASILI_TUTULUYOR:
            if(butonNo>0)
            {
                if(butonNo==oncekiButon)
                {
                    if (uzunBasildi==0)
                    {
                        if(miliSaniye()-butonSure > uzun_basma_suresi)
                        {
                            uzunBasildi=1;
                            butonDurumu=UZUN_BASILDI;   //bir defalık pals üret.
                            return butonNo;
                        }
                    }
                }                
            }
            else
            {
                butonSure=miliSaniye();
                butonDurumu=DEBOUNCE2;
            }
            break;
            //------------------------------------------------------------------
        case UZUN_BASILDI:
            if(butonNo>0)
            {
                butonDurumu=BASILI_TUTULUYOR;
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE2:
            //aynı butona basılmaya devam mı ediliyor?
            //kontak sıçramasını atla
            if(butonNo==0) 
            { 
                if (miliSaniye() - butonSure > debounce_suresi) 
                {
                    butonDurumu = BIRAKILDI;        //bir defalık pals üret.            
                    return oncekiButon;
                }                
            }
            else
            {
                butonDurumu=BASILI_TUTULUYOR;
            }
            break; 
            //------------------------------------------------------------------
        case BIRAKILDI:
            butonDurumu=SERBEST;
            return oncekiButon;
            break;    
            //------------------------------------------------------------------
    }
    
    return 0x00;
    
}

/*******************************************************************************
 * Kütüphane     : Geliþmiþ Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * Butonlarýn kontak sýçrama durumlarýnýda dikkate alarak buton durumunu okur. *
 * Bu fonksiyon ile butona basýlma, býrakýlma, uzun basýlma,basýlý tutulma     *
 * durumlarý kolayca okunabilmektedir.                                         * 
 ******************************************************************************/

#include "mcc_generated_files/mcc.h"
#include "buton.h"
#include "zaman.h"

unsigned long butonSure;
char butonNo,oncekiButon;
bit uzunBasildi;

//Basýlan butonun numarasýný döndürür. Hiç bir butona basýlmadý ise 0x00 döner.
char buton_oku(void)
{
    butonNo=0;
    
    //basýlý olan butonu bul.
    if(!buton1)
        butonNo=1;
    else if(!buton2)
        butonNo=2;
//    else if(!buton3)
//        butonNo=3;
                
    return buton_kontrol();
}


//Buton durumunu ve kontak sýçramasýný test eder.
char buton_kontrol(void)
{
    switch(butonDurumu)
    {
        case SERBEST:   //ilk defa basýldýðýnda 
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
            //ayný butona basýlmaya devam mý ediliyor?
            //kontak sýçramasýný atla
            if(butonNo>0) 
            {
                if (butonNo == oncekiButon) 
                {
                    if (miliSaniye() - butonSure > debounce_suresi) 
                    {
                        butonDurumu = BASILDI;      //bir defalýk pals üret.
                        butonSure = miliSaniye();
                        return butonNo;
                    }
                } 
                else
                {
                    //farklý butona basýlmýþ.
                    oncekiButon=butonNo;
                    butonSure=miliSaniye();
                }
            }
            else
            {
                //kontak anlýk 0'a düþtüyse veya býrakýldýysa
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
                            butonDurumu=UZUN_BASILDI;   //bir defalýk pals üret.
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
            //ayný butona basýlmaya devam mý ediliyor?
            //kontak sýçramasýný atla
            if(butonNo==0) 
            { 
                if (miliSaniye() - butonSure > debounce_suresi) 
                {
                    butonDurumu = BIRAKILDI;        //bir defalýk pals üret.            
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
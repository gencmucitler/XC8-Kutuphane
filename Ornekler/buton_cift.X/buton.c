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

#include "mcc_generated_files/mcc.h"
#include "buton.h"
#include "zaman.h"

unsigned long butonSure,ciftTiklamaSure;
char butonNo,butonNo_kayit,oncekiButonNo;
bit uzunBasildi,kisaBasildi;

//Basýlan butonun numarasýný döndürür. Hiç bir butona basýlmadý ise 0x00 döner.
char buton_oku(void)
{
    butonNo=0;
    
    //basýlý olan butonu bul.
    if(!buton1)
        butonNo=1;
//    else if(!buton2)
//        butonNo=2;
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
            if(butonNo) 
            {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE;
                butonNo_kayit = butonNo;    //ButonNo yu kaydet, sürekli butona 
                                            //basýlýyor mu diye kontrol edilecek
                uzunBasildi=0;
                kisaBasildi=0;
            }
            else
            {
                butonNo_kayit=0;
                return 0x00;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE:
            //ayný butona basýlmaya devam mý ediliyor?
            //kontak sýçramasýný atla
            if(butonNo) 
            {
                if (butonNo == butonNo_kayit) 
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
                    butonNo_kayit=butonNo;
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
            if(butonNo)
            {
                butonDurumu=BASILI_TUTULUYOR;
                butonSure=miliSaniye();
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case BASILI_TUTULUYOR:
            if(butonNo)
            {
                if(butonNo==butonNo_kayit)
                {
                    if(kisaBasildi==0)
                    {
                        if(miliSaniye()-butonSure >kisa_basma_suresi)
                        {
                            kisaBasildi=1;
                            butonDurumu=KISA_BASILDI;
                            return butonNo;
                        }
                    }
                    if (uzunBasildi==0)
                    {
                        if(miliSaniye()-butonSure > uzun_basma_suresi)
                        {
                            uzunBasildi=1;
                            butonDurumu=UZUN_BASILDI;   //bir defalýk pals üret.
                            return butonNo;
                        }
                    }
                    
                    return butonNo;
                }                
            }
            else
            {
                butonSure=miliSaniye();
                butonDurumu=DEBOUNCE2;
            }
            break;
            //------------------------------------------------------------------            
        case KISA_BASILDI:
        case UZUN_BASILDI:
            if(butonNo)
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
                    return butonNo_kayit;
                }                
            }
            else
            {
                butonDurumu=BASILI_TUTULUYOR;
            }
            break; 
            //------------------------------------------------------------------
        case CIFT_TIKLAMA:
            butonDurumu = SERBEST;
            return butonNo_kayit;     
            break;
            //------------------------------------------------------------------
        case BIRAKILDI:

            //çift týklamada kullanýlacak kodlar
            //önceden de ayný butona mý basýldý? Ýki kere butona basma süresi 
            //istenildiði süre kadar kýsa mý?
            if(butonNo_kayit==oncekiButonNo && miliSaniye()-ciftTiklamaSure<cift_tiklama_suresi)
            {
                butonDurumu=CIFT_TIKLAMA;
                return butonNo_kayit;
            }
            //bir sonraki týklama için kaydet
            oncekiButonNo=butonNo_kayit;
            ciftTiklamaSure=miliSaniye();
            
            butonDurumu=SERBEST;
            return butonNo_kayit;
            break;    
            //------------------------------------------------------------------
    }
    
    return 0x00;
    
}
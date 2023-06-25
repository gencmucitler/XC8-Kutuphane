/*******************************************************************************
 * Kütüphane     : Gelişmiş Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 18 Haziran 2017                                             *
 * Düzenleme     : 22 Haziran 2017                                             *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 * Butonların kontak sıçrama durumlarınıda dikkate alarak buton durumunu okur. *
 * Bu fonksiyon ile butona basılma, bırakılma, uzun basılma,basılı tutulma     *
 * durumları kolayca okunabilmektedir.                                         * 
 ******************************************************************************/
// v0.2 Basılı Tutuluyor kodu sonuna return butonNo eklendi.
//      Çift tıklama ve Kısa Basma durumları eklendi.
// v0.1 ilk düzenleme.

#include "mcc_generated_files/mcc.h"
#include "buton.h"
#include "zaman.h"

unsigned long butonSure,ciftTiklamaSure;
char butonNo,butonNo_kayit,oncekiButonNo;
bit uzunBasildi,kisaBasildi;

//Basılan butonun numarasını döndürür. Hiç bir butona basılmadı ise 0x00 döner.
char buton_oku(void)
{
    butonNo=0;
    
    //basılı olan butonu bul.
    if(!buton1)
        butonNo=1;
//    else if(!buton2)
//        butonNo=2;
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
            if(butonNo) 
            {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE;
                butonNo_kayit = butonNo;    //ButonNo yu kaydet, sürekli butona 
                                            //basılıyor mu diye kontrol edilecek
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
            //aynı butona basılmaya devam mı ediliyor?
            //kontak sıçramasını atla
            if(butonNo) 
            {
                if (butonNo == butonNo_kayit) 
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
                    butonNo_kayit=butonNo;
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
                            butonDurumu=UZUN_BASILDI;   //bir defalık pals üret.
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
            //aynı butona basılmaya devam mı ediliyor?
            //kontak sıçramasını atla
            if(butonNo==0) 
            { 
                if (miliSaniye() - butonSure > debounce_suresi) 
                {
                    butonDurumu = BIRAKILDI;        //bir defalık pals üret.            
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

            //çift tıklamada kullanılacak kodlar
            //önceden de aynı butona mı basıldı? İki kere butona basma süresi 
            //istenildiği süre kadar kısa mı?
            if(butonNo_kayit==oncekiButonNo && miliSaniye()-ciftTiklamaSure<cift_tiklama_suresi)
            {
                butonDurumu=CIFT_TIKLAMA;
                return butonNo_kayit;
            }
            //bir sonraki tıklama için kaydet
            oncekiButonNo=butonNo_kayit;
            ciftTiklamaSure=miliSaniye();
            
            butonDurumu=SERBEST;
            return butonNo_kayit;
            break;    
            //------------------------------------------------------------------
    }
    
    return 0x00;
    
}

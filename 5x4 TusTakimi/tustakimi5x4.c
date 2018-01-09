/*******************************************************************************
 * Kütüphane     : 5x4 Tuþ Takýmý Okuma Kütüphanesi                            *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * 4x4 matriks tuþ takýmý kütüphanesi                                          *
 ******************************************************************************/

//SATIRLAR çýkýþ, SUTUNLAR giriþ yapýlmalý.  Giriþ portlarý pull-up direnci 
//takýlmalý veya internal pull-up aktif edilmelidir.

#include "mcc_generated_files/mcc.h"
#include "tustakimi5x4.h"
#include "zaman.h"

unsigned long butonSure, ciftTiklamaSure;
char butonNo, butonNo_kayit, oncekiButonNo;
bit uzunBasildi, kisaBasildi;
char satirno, sutunno;

//basýlan tuþu oku

char tustakimi_oku(void) {
    //tüm satýlar çýkýþ olmalý
    SATIR1 = 0;
    SATIR2 = 0;
    SATIR3 = 0;
    SATIR4 = 0;
    SATIR5 =0 ;
    
    sutunno = 0;
    satirno=0;

    if (!SUTUN1)
        sutunno = 1;
    else if (!SUTUN2)
        sutunno = 2;
    else if (!SUTUN3)
        sutunno = 3;
    else if (!SUTUN4)
        sutunno = 4;


    //bir butona basýldýysa basýlan satýrýda bul.
    if (sutunno) {
        for (satirno = 1; satirno <= 5; satirno++) {
            switch (satirno) {
                case 1:
                    SATIR1 = 0;
                    SATIR2 = 1;
                    SATIR3 = 1;
                    SATIR4 = 1;
                    SATIR5 = 1;
                    break;
                case 2:
                    SATIR1 = 1;
                    SATIR2 = 0;
                    SATIR3 = 1;
                    SATIR4 = 1;
                    SATIR5 = 1;
                    break;
                case 3:
                    SATIR1 = 1;
                    SATIR2 = 1;
                    SATIR3 = 0;
                    SATIR4 = 1;
                    SATIR5 = 1;
                    break;
                case 4:
                    SATIR1 = 1;
                    SATIR2 = 1;
                    SATIR3 = 1;
                    SATIR4 = 0;
                    SATIR5 = 1;
                    break;
                case 5:
                    SATIR1 = 1;
                    SATIR2 = 1;
                    SATIR3 = 1;
                    SATIR4 = 1;
                    SATIR5 = 0;                    
                    break;  
            }

            //bu satýrda ki tuþ mu basýlý ?
            if (!SUTUN1)
                break;
            else if (!SUTUN2)
                break;
            else if (!SUTUN3)
                break;
            else if (!SUTUN4)
                break;                        
        }
    }

    
    //satýr ve sütün bulundu mu?
    
    if(satirno && sutunno)
    {
        butonNo=tuslar[(satirno-1)*4+(sutunno-1)];
    }
    else
    {
        butonNo=0;
    }
    return buton_kontrol();
}


//Buton durumunu ve kontak sýçramasýný test eder.
char buton_kontrol(void) {
    switch (butonDurumu) {
        case SERBEST: //ilk defa basýldýðýnda 
            if (butonNo) {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE;
                butonNo_kayit = butonNo; //ButonNo yu kaydet, sürekli butona 
                //basýlýyor mu diye kontrol edilecek
                uzunBasildi = 0;
                kisaBasildi = 0;
            } else {
                butonNo_kayit = 0;
                return 0x00;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE:
            //ayný butona basýlmaya devam mý ediliyor?
            //kontak sýçramasýný atla
            if (butonNo) {
                if (butonNo == butonNo_kayit) {
                    if (miliSaniye() - butonSure > debounce_suresi) {
                        butonDurumu = BASILDI; //bir defalýk pals üret.
                        butonSure = miliSaniye();
                        return butonNo;
                    }
                }
                else {
                    //farklý butona basýlmýþ.
                    butonNo_kayit = butonNo;
                    butonSure = miliSaniye();
                }
            } else {
                //kontak anlýk 0'a düþtüyse veya býrakýldýysa
                butonDurumu = SERBEST;
            }
            break;
            //------------------------------------------------------------------
        case BASILDI:
            if (butonNo) {
                butonDurumu = BASILI_TUTULUYOR;
                butonSure = miliSaniye();
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case BASILI_TUTULUYOR:
            if (butonNo) {
                if (butonNo == butonNo_kayit) {
                    if (kisaBasildi == 0) {
                        if (miliSaniye() - butonSure > kisa_basma_suresi) {
                            kisaBasildi = 1;
                            butonDurumu = KISA_BASILDI;
                            return butonNo;
                        }
                    }
                    if (uzunBasildi == 0) {
                        if (miliSaniye() - butonSure > uzun_basma_suresi) {
                            uzunBasildi = 1;
                            butonDurumu = UZUN_BASILDI; //bir defalýk pals üret.
                            return butonNo;
                        }
                    }

                    return butonNo;
                }
            } else {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE2;
            }
            break;
            //------------------------------------------------------------------            
        case KISA_BASILDI:
        case UZUN_BASILDI:
            if (butonNo) {
                butonDurumu = BASILI_TUTULUYOR;
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE2:
            //ayný butona basýlmaya devam mý ediliyor?
            //kontak sýçramasýný atla
            if (butonNo == 0) {
                if (miliSaniye() - butonSure > debounce_suresi) {
                    butonDurumu = BIRAKILDI; //bir defalýk pals üret.            
                    return butonNo_kayit;
                }
            } else {
                butonDurumu = BASILI_TUTULUYOR;
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
            if (butonNo_kayit == oncekiButonNo && miliSaniye() - ciftTiklamaSure < cift_tiklama_suresi) {
                butonDurumu = CIFT_TIKLAMA;
                return butonNo_kayit;
            }
            //bir sonraki týklama için kaydet
            oncekiButonNo = butonNo_kayit;
            ciftTiklamaSure = miliSaniye();

            butonDurumu = SERBEST;
            return butonNo_kayit;
            break;
            //------------------------------------------------------------------
    }

    return 0x00;

}
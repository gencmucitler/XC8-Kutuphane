/*******************************************************************************
 * Kütüphane     : miliSaniye                                                  *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * PIC kaç miliSaniyedir enerjili olduðunu sayar. Yaklaþýk 50 gün sonra sayaç  * 
 * sýfýrlanýr.                                                                 * 
 ******************************************************************************/

volatile unsigned long _msaniye=0;

//her milisaniyede bir artacak. maksimum 50 güne kadar sayabiliyor.
//2^32 /1000 = x saniye  x/60/60/24 =49,71 gün
void _miliSaat(void)        //Timer2/4/6 kesmesi tarafýndan tetiklenmelidir.
{
    _msaniye++;
}

//mili saniye cinsinden mikrodenetleyicinin ne kadar süre çalýþtýðý bilgisini döndürür.
unsigned long miliSaniye(void)
{    
    return _msaniye;
}

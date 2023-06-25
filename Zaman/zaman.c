/*******************************************************************************
 * Kütüphane     : miliSaniye                                                  *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * PIC kaç miliSaniyedir enerjili olduğunu sayar. Yaklaşık 50 gün sonra sayaç  * 
 * sıfırlanır.                                                                 * 
 ******************************************************************************/

volatile unsigned long _msaniye=0;

//her milisaniyede bir artacak. maksimum 50 güne kadar sayabiliyor.
//2^32 /1000 = x saniye  x/60/60/24 =49,71 gün
void _miliSaat(void)        //Timer2/4/6 kesmesi tarafından tetiklenmelidir.
{
    _msaniye++;
}

//mili saniye cinsinden mikrodenetleyicinin ne kadar süre çalıştığı bilgisini döndürür.
unsigned long miliSaniye(void)
{    
    return _msaniye;
}

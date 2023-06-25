/*******************************************************************************
 * Kütüphane     : Easydriver Adım motor kütüphanesi                           *
 * Yazar         : sigmoid                                                     *
 * Başlangıç     : 4 Ocak 2018                                                 *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 ******************************************************************************/

//pin tanımlamaları
#define step_DIR   LATB0
#define step_PULSE LATB1

//motor 360 derecelik tam turunu kaç adımda tamamlıyor8ı
#define motorAdimi  1600

//motor yönü
#define saatYonunde     0
#define saatTersYonunde 1
#define CW              0
#define CCW             1

//Hız ayarları - Hz olarak girilmeli
#define _maksimum_hiz    16000  //1 saniyedeki maksimum adım sayısı 
#define _minumum_hiz     800    //1 saniyedeki minumum adım sayısı 
#define _hizlanmaadimi   4    //kaç adim da bir hızlanacak
#define _yavaslamaadimi  10    //kaç adim da bir yavaşlayacak

#define _sure          100000UL

#define C 3.141592/180.0

void adimMotor(unsigned int adimSayisi,char adimYonu);
void adimMotorDerece(unsigned int adimDerece,char adimYonu);
void step_bekle(unsigned int sure);

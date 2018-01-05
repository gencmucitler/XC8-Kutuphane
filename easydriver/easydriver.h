/*******************************************************************************
 * Kütüphane     : Easydriver Adým motor kütüphanesi                           *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Baþlangýç     : 4 Ocak 2018                                                 *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 ******************************************************************************/

//pin tanýmlamalarý
#define step_DIR   LATB0
#define step_PULSE LATB1

//motor 360 derecelik tam turunu kaç adýmda tamamlýyor8ý
#define motorAdimi  1600

//motor yönü
#define saatYonunde     0
#define saatTersYonunde 1
#define CW              0
#define CCW             1

//Hýz ayarlarý - Hz olarak girilmeli
#define _maksimum_hiz    16000  //1 saniyedeki maksimum adým sayýsý 
#define _minumum_hiz     800    //1 saniyedeki minumum adým sayýsý 
#define _hizlanmaadimi   4    //kaç adim da bir hýzlanacak
#define _yavaslamaadimi  10    //kaç adim da bir yavaþlayacak

#define _sure          100000UL

#define C 3.141592/180.0

void adimMotor(unsigned int adimSayisi,char adimYonu);
void adimMotorDerece(unsigned int adimDerece,char adimYonu);
void step_bekle(unsigned int sure);

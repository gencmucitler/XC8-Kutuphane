/*******************************************************************************
 * Kütüphane     : 28BYJ-48 Adým motor kütüphanesi                             *
 * Yazar         : sigmoid                                                     *
 * Baþlangýç     : 17 Aralýk  2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 ******************************************************************************/

//pin tanýmlamalarý
#define motorPin_Turuncu    LATB0
#define motorPin_Sari       LATB1
#define motorPin_Pembe      LATB2
#define motorPin_Mavi       LATB3

//motor yönü
#define saatYonunde     0
#define saatTersYonunde 1
#define CW              0
#define CCW             1


//motorun 360 derecelikönüþ için gereken adým sayýsý
#define motorAdimi  4096

//fonksiyon prototipleri
void adimMotor(unsigned int adimSayisi,char adimYonu,unsigned int adimHizi);
void adimMotorDerece(unsigned int adimDerece,char adimYonu,unsigned int adimHizi);

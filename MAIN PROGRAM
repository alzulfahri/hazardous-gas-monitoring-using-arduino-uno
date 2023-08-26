#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include <AverageValue.h> 

LiquidCrystal_I2C lcd(0x27, 20, 4);   //inisialisasi lcd i2c

//CO2 MQ135 variable
int MQ135_co2= A1;
int Rload_co2 = 10000;
float rO_co2= 190000;
double ppm_co2=423.68;
float a_co2 = 110.7432567;
float b_co2 = -2.856935538;
float minppm_co2=0;
float maxppm_co2=1000;
const long MAX_VALUES_NUM_CO2 = 10;
AverageValue<long> AverageValue_co2(MAX_VALUES_NUM_CO2);

//NH3 MQ135 Variable
int MQ135_nh3=A2;
int Rload_nh3 = 10000;
float rO_nh3= 3400000;
double ppm_nh3=5.0;
float a_nh3 = 0.858;
float b_nh3 = -0.417;
float minppm_nh3=10;
float maxppm_nh3=300;
const long MAX_VALUES_NUM_NH3 = 10;
AverageValue<long> AverageValue_nh3(MAX_VALUES_NUM_NH3);

const int relayPin = 7;
const int buzzerPin = 8;

//CH4 MQ4 Variable
int MQ4_ch4=A0;
int Rload_ch4 = 20000;
float rO_ch4=6300;
double ppm_ch4=1.9;
float a_ch4 = 192.361;
float b_ch4 = -1.477;
float minppm_ch4=100;
float maxppm_ch4=10000;
const long MAX_VALUES_NUM_CH4 = 10;
AverageValue<long> AverageValue_ch4(MAX_VALUES_NUM_CH4);

    //Nilai ambang batas 
    const int co2Threshold = 350.0;
    const int ammoniaThreshold = 5.0;
    const int methaneThreshold = 5.0;
    
float ppmToPercentageCO2(float ppm_co2) {
  return (ppm_co2 / co2Threshold) * 100.0;
}

float ppmToPercentageNH3(float ppm_nh3) {
  return (ppm_nh3 / ammoniaThreshold) * 100.0;
}

float ppmToPercentageCH4(float ppm_ch4) {
  return (ppm_ch4 / methaneThreshold) * 100.0;
}

void setup() {
    //Inisialisasi Pin
    pinMode(MQ4_ch4, INPUT);
    pinMode(MQ135_nh3, INPUT);
    pinMode(MQ135_co2, INPUT);
    pinMode(relayPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  
  //TAMPILAN AWAL LCD
  lcd.setCursor(2, 0);
  lcd.print("Monitoring Kadar");
  lcd.setCursor(3, 1);
  lcd.print("Gas Berbahaya");
  lcd.setCursor(5, 2);
  lcd.print("pada TPSS");
  lcd.setCursor(0, 3);
  lcd.print("Oleh: Alief Zulfahri");
  delay(5000);
  lcd.clear();
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Kalibrasi Sensor Gas");
  lcd.setCursor(3, 1);
  lcd.print("CO2 - NH3 - CH4");
  lcd.setCursor(3, 2);
  lcd.print("Mohon Ditunggu");
  for (int i = 10; i >= 0; i--){
  lcd.setCursor(6, 3);
  lcd.print(i);
  lcd.print(" detik ");
  delay(1000);
  }
  lcd.clear();

      //CO2
     //min[Rs/Ro]=(max[ppm]/a)^(1/b)
       minppm_co2=pow((1000/110.7432567),1/-2.856935538);
      //max[Rs/Ro]=(min[ppm]/a)^(1/b)
       maxppm_co2=pow((10/110.7432567),1/-2.856935538);

    //NH3
         //min[Rs/Ro]=(max[ppm]/a)^(1/b)
       minppm_nh3=pow((300/0.858),1/-0.417);
      //max[Rs/Ro]=(min[ppm]/a)^(1/b)
       maxppm_nh3=pow((10/0.858),1/-0.417);

       //CH4
         //min[Rs/Ro]=(max[ppm]/a)^(1/b)
       minppm_ch4=pow((10000/192.361),1/-1.477);
      //max[Rs/Ro]=(min[ppm]/a)^(1/b)
       maxppm_ch4=pow((100/192.361),1/-1.477);

}

void loop() {
    //PEMBACAAN SATUAN PERSEN
  lcd.setCursor(0, 0);
  lcd.print("Monitoring Kadar Gas");

  lcd.setCursor(0, 1);
  lcd.print("NH3 Amonia: ");
  lcd.print(ppmToPercentageNH3(AverageValue_nh3.average()), 1);
  lcd.setCursor(19, 1);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("CH4 Metana: ");
  lcd.print(ppmToPercentageCH4(AverageValue_ch4.average()), 1);
  lcd.setCursor(19, 2);
  lcd.print("%");

    lcd.setCursor(0, 3);
  lcd.print("CO2       : ");
  lcd.print(ppmToPercentageCO2(AverageValue_co2.average()), 1);
  lcd.setCursor(19, 3);
  lcd.print("%");
  delay(1000);
  lcd.clear();
  
 //PEMBACAAN SATUAN PPM
  lcd.setCursor(0, 0);
  lcd.print("Monitoring Kadar Gas");

  lcd.setCursor(0, 1);
  lcd.print("NH3 Amonia: ");
  lcd.print(AverageValue_nh3.average(), 1);
  lcd.setCursor(17, 1);
  lcd.print("ppm");

  lcd.setCursor(0, 2);
  lcd.print("CH4 Metana: ");
  lcd.print(AverageValue_ch4.average(), 1);
  lcd.setCursor(17, 2);
  lcd.print("ppm");

  lcd.setCursor(0, 3);
  lcd.print("CO2       : ");
  lcd.print(AverageValue_co2.average(), 1);
  lcd.setCursor(17, 3);
  lcd.print("ppm");
  delay(1000);



    //co2
    int adcRaw_co2 = analogRead(MQ135_co2);
    double rS_co2 = ((1024.0 * Rload_co2) / adcRaw_co2) - Rload_co2;
   
    float rSrO_co2= rS_co2/rO_co2;
    rSrO_co2 < (maxppm_co2 && rSrO_co2 > minppm_co2);
    {
    float ppm_co2 = a_co2 * pow((float)rS_co2 / (float)rO_co2, b_co2);
    AverageValue_co2.push(ppm_co2);
    }


    //nh3
    int adcRaw_nh3 = analogRead(MQ135_nh3);
    double rS_nh3 = ((1024.0 * Rload_nh3) / adcRaw_nh3) - Rload_nh3;
   
    float rSrO_nh3= rS_nh3/rO_nh3;
    rSrO_nh3 < (maxppm_nh3 && rSrO_nh3 > minppm_nh3);
    {
    float ppm_nh3 = a_nh3 * pow((float)rS_nh3 / (float)rO_nh3, b_nh3);
    AverageValue_nh3.push(ppm_nh3);
    }


    //ch4
    int adcRaw_ch4 = analogRead(MQ4_ch4);
    double rS_ch4 = ((1024.0 * Rload_ch4) / adcRaw_ch4) - Rload_ch4;
   
    float rSrO_ch4= rS_ch4/rO_ch4;
    rSrO_ch4 < (maxppm_ch4 && rSrO_ch4 > minppm_ch4);
    {
    float ppm_ch4 = a_ch4 * pow((float)rS_ch4 / (float)rO_ch4, b_ch4);
    AverageValue_ch4.push(ppm_ch4);
     }

    if (AverageValue_co2.average() >= co2Threshold 
    || AverageValue_ch4.average() >= methaneThreshold 
    || AverageValue_nh3.average() >= ammoniaThreshold) {
    tone(buzzerPin,5000);
    delay(50);
    noTone(buzzerPin);
    delay(50);
    tone(buzzerPin,5000);
    delay(50);
    noTone(buzzerPin);
    delay(50);
    tone(buzzerPin,5000);
    delay(50);
    noTone(buzzerPin);
    delay(50);
    digitalWrite(relayPin, LOW);
    
  }else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, HIGH);
  }
  delay(500);
  lcd.clear();
}

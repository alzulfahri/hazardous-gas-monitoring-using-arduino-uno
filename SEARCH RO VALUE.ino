#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include <AverageValue.h>
LiquidCrystal_I2C lcd(0x27,20,4); 

int MQ135_CO2=A1;
int Rload_CO2 = 10000;
double ppm_CO2=423.68;
float a_CO2 = 110.7432567;
float b_CO2 = -2.856935538;
const long MAX_VALUES_NUM_CO2 = 10;
AverageValue<long> AverageValue_CO2(MAX_VALUES_NUM_CO2);

int MQ135_NH3=A2;
int Rload_NH3 = 10000;
double ppm_NH3= 4.0;
float a_NH3 = 0.858;
float b_NH3 = -0.417;
const long MAX_VALUES_NUM_NH3 = 10;
AverageValue<long> AverageValue_NH3(MAX_VALUES_NUM_NH3);

int MQ4_CH4=A0;
int Rload_CH4 = 20000;
double ppm_CH4= 1.9;
float a_CH4 = 192.361;
float b_CH4 = -1.477;
const long MAX_VALUES_NUM_CH4 = 10;
AverageValue<long> AverageValue_CH4(MAX_VALUES_NUM_CH4);

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  float adcRaw_CO2 = analogRead(MQ135_CO2);
  float adcRaw_NH3 = analogRead(MQ135_NH3);
  float adcRaw_CH4 = analogRead(MQ4_CH4); 

  //CO2 KARBON DIOKSIDA
  float rS_CO2 = ((1024.0 * Rload_CO2) / adcRaw_CO2) - Rload_CO2;
  float rO_CO2=rS_CO2 * exp(log(a_CO2/ppm_CO2) / b_CO2 );
  AverageValue_CO2.push(rO_CO2);
  
  //NH3 AMONIA
  float rS_NH3 = ((1024.0 * Rload_NH3) / adcRaw_NH3) - Rload_NH3;
  float rO_NH3=rS_NH3 * exp(log(a_NH3/ppm_NH3) / b_NH3 );
  AverageValue_NH3.push(rO_NH3);

  //CH4 METANA
  float rS_CH4 = ((1024.0 * Rload_CH4) / adcRaw_CH4) - Rload_CH4;
  float rO_CH4=rS_CH4 * exp(log(a_CH4/ppm_CH4) / b_CH4 );
  AverageValue_CH4.push(rO_CH4);

  //TAMPILAN
  lcd.setCursor(0,0);
  lcd.print("CO2 RO: ");
  lcd.setCursor(8,0);
  lcd.print(AverageValue_CO2.average());
  lcd.setCursor(16,0);
  lcd.print("Ohm");

  lcd.setCursor(0,1);
  lcd.print("NH3 RO: ");
  lcd.setCursor(8,1);
  lcd.print(AverageValue_NH3.average());
  lcd.setCursor(16,1);
  lcd.print("Ohm");

  lcd.setCursor(0,2);
  lcd.print("CH4 RO: ");
  lcd.setCursor(8,2);
  lcd.print(AverageValue_CH4.average());
  lcd.setCursor(16,2);
  lcd.print("Ohm");

  delay(1000);
}

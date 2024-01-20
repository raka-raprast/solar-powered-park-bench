// Title  : Rancang Bangun Bangku Taman Ruang Terbuka Hijau Menggunakan Solar Panel Berbasis Arduino Uno di Taman Tiga Genearsi Balikpapan\\
// by     : Raka Ramadhani Aulia Prasetyo \\
// D3 Final Year Project \\

// formula to count the lux \\
// this expresses Rldr in kiloOhm and is for a 10kOhm reference resistor:
//Vout=(5Rldr)/(Rldr+10)
//5Rldr=Vout(Rldr+10)        // multiplied both sides with (Rldr+10) and switch left and right
//5Rldr=Vout*Rldr+10out     // executed the right side multiplication
//5Rldr+(-Vout*Rldr)=(Vout*Rldr+10Vout)+(-Vout*Rldr)   //added equal value (-Vout*Rldr) to both sides
//5Rldr+(-Vout*Rldr)=Vout*Rldr+10Vout-Vout*Rldr        // work out right side  additions and subtractions
//5Rldr-Vout*Rldr=Vout*Rldr+10Vout-Vout*Rldr           //work out left side additions and subtractions
//5Rldr-Vout*Rldr=Vout*Rldr-Vout*Rldr+10Vout           // ditto
//5Rldr-Vout*Rldr=10Vout     //ditto
//Rldr(5-Vout)=10Vout        //expressed left side as multiplication of Rldr
//Rldr=10Vout/(5-Vout)       // divided both sides by equal value (5-Vout)

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //assign LCD pin
int analogInput = 0; //voltage value in
int usb = 5; // assign USB controller pin
int led = 6; // assign LED controller pin
float vout = 0.0;
float vin = 0.0; 
float R1 = 100000.0; // resistance of R1 (100K)-see text!
float R2 = 10000.0; // resistance of R2 (10K)-see text!
int value = 0;
// formula designed to calculate the lux
double Light (int RawADC0)
{
double Voutldr=RawADC0*0.0048828125; 
int lux=(2500/Voutldr-500)/10;
return lux;
int chy = Light(analogRead(1));
}

void setup() 
{
  pinMode(analogInput, INPUT);
  pinMode(usb, OUTPUT);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
}

void loop()
{
  // showing lux value
  int chy = Light(analogRead(1));
  lcd.setCursor(0, 0);
  lcd.print("Light= ");
  lcd.print(chy);
  lcd.print("Lux");
  delay(1000);
  // calculating the voltage from 0-30v
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0; // see text
  vin = vout / (R2/(R1+R2)); 
// statement to quash undesired reading!
   if (vin<0.09) 
   {
   vin=0.0;
   } 
  if (vin < 10.5)
   {
   lcd.setCursor(0, 1);
   lcd.print("Battery= ");
   lcd.print("0");
   lcd.print("%");
   delay(1000);
   }
   else if (vin > 13.1)
   {
   lcd.setCursor(0, 1);
   lcd.print("Battery= ");
   lcd.print("100");
   lcd.print("%");
   delay(500);
   }
   else
   {
   lcd.setCursor(0, 1);
   lcd.print("Battery= ");
   lcd.print(volts);
   lcd.print("%");
   delay(500);
   }  
// controlling charging port
   if (volts <= 15 && chy <= 60)
    {
      digitalWrite(led, LOW);
      digitalWrite(usb, HIGH);
    }
    if (volts <= 15 && chy > 60)
    {
      digitalWrite(led, LOW);
      digitalWrite(usb, HIGH);
    }
    else if (digitalRead(usb) == HIGH && volts >= 30 && chy <= 60)
    {
      digitalWrite(led, HIGH):
      digitalWrite(usb, LOW);   
    }
    else if (digitalRead(usb) == HIGH && volts >= 30 && chy > 60)
    {
      digitalWrite(led, LOW):
      digitalWrite(usb, LOW);   
    }
    else if (volts > 15 && chy <= 60)
    {
      digitalWrite(led, HIGH):
      digitalWrite(usb, LOW);   
    }
    else
    {
      digitalWrite(led, LOW);
      digitalWrite(usb, LOW);
    }
}

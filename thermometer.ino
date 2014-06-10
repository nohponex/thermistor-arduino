/*
School of Electrical & Computer Engineering — AUTh
"Ηλεκτρικές Μετρήσεις ΙΙ"
Arduino thermometer using thermistor sensor
22/5/2013
   
  Group 23 :
  Spatharidis Xenophon
  Kalvoutzis Athanasios
*/

//Required libraries
#include <math.h>
#include <LiquidCrystal.h>

//Define constants
#define RESISTANCE_R1 9950
#define CONST_A 0.003354016 
#define CONST_B 0.000256985 
#define CONST_C 0.000002620131 
#define CONST_D 0.00000006383091 
#define RESISTANCE_REF 8600 

#define INPUT_PIN 0
#define OUTPUT_PIN_V0 9


//Calculate temperature for given input voltage
double Temperature( int InputVoltage ){

  //Calculate Resistance
  float R = ( ( ( 1023.0*RESISTANCE_R1 ) / InputVoltage ) - RESISTANCE_R1 );
  
  double logarithm = log( R / RESISTANCE_REF );
  
  return ( 1 / (CONST_A + CONST_B * logarithm + CONST_C * logarithm * logarithm +  CONST_D * logarithm * logarithm * logarithm ) ) - 273.15; 
  
}

//Define LCD object using selected pins
LiquidCrystal lcd( 12, 11, 5, 4, 3, 2 );

//Arduino setup function
void setup(){
  //Setup digital pins
  pinMode( OUTPUT_PIN_V0 , OUTPUT);  // LCD Vo Voltage
  
  analogWrite( OUTPUT_PIN_V0, 1 ); // 50/1023 of Vcc
  
  //Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Temperature");
}

//Arduono loop function
void loop() {
  //Read input voltage
  int InputVoltage = analogRead( INPUT_PIN );
  //Calculate temperature
  double T = Temperature( InputVoltage );
  //Display result
  lcd.setCursor(0, 1);
  //Print temperature
  lcd.print( T );
  lcd.print(" *C      ");
  
  delay(500);
}

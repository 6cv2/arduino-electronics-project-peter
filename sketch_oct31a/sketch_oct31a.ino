#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int analogInPin = A0;
const int analogOutPin = 9;
const int ledPin1 = 11;
const int ledPin2 = 10;
const int ledPin3 = 9;
const int ledPin4 = 8;
const int ledPin5 = 7;

int sensorValue = 0;
int outputValue = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  lcd.init();
}

void loop() {

  unsigned long rollingAverage = 0;

  for(int i=0; i<500; i++){
    sensorValue = analogRead(analogInPin);
    rollingAverage += sensorValue;

    outputValue = rollingAverage/500;}

    if (outputValue > 410) {
      digitalWrite(ledPin1, HIGH);
    } else {
      digitalWrite(ledPin1, LOW);}
    if (outputValue > 425) {
      digitalWrite(ledPin2, HIGH);
    } else {
      digitalWrite(ledPin2, LOW);}
    if (outputValue > 460) {
      digitalWrite(ledPin3, HIGH);
    } else {
      digitalWrite(ledPin3, LOW);}
    if (outputValue > 500) {
      digitalWrite(ledPin4, HIGH);
    } else {
      digitalWrite(ledPin4, LOW);}
    if (outputValue > 600) {
      digitalWrite(ledPin5, HIGH);
    } else {
      digitalWrite(ledPin5, LOW);}
  
  Serial.print("sensor = ");
  Serial.println(outputValue);

  lcd.setCursor(0, 0);
  lcd.print("Value: ");
  lcd.print(outputValue);
  lcd.print("   ");
}

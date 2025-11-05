#include <LiquidCrystal_I2C.h>

const int analogInPin = A0;
const int analogOutPin = 9;
const int ledPin1 = 11;
const int ledPin2 = 10;
const int ledPin3 = 9;
const int ledPin4 = 8;
const int ledPin5 = 7;
const int interruptPin = 2;
bool thresholdExceeded = false;
int sensorValue = 0;
int outputValue = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(interruptPin, INPUT);
  lcd.init();
  attachInterrupt(digitalPinToInterrupt(interruptPin), tooLoud, RISING);
}

void loop() {
  unsigned long rollingAverage = 0;
  for (int i = 0; i < 500; i++) {
    sensorValue = analogRead(analogInPin);
    rollingAverage += sensorValue;
  }
  outputValue = rollingAverage / 500;

  if (outputValue > 400) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
  }
  if (outputValue > 450) {
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }
  if (outputValue > 510) {
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin3, LOW);
  }
  if (outputValue > 550) {
    digitalWrite(ledPin4, HIGH);
  } else {
    digitalWrite(ledPin4, LOW);
  }
  if (outputValue > 630) {
    digitalWrite(ledPin5, HIGH);
  } else {
    digitalWrite(ledPin5, LOW);
  }

  Serial.print("sensor = ");
  Serial.println(outputValue);

  lcd.setCursor(0, 0);
  lcd.print("Value: ");
  lcd.print(outputValue);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print("state: ");
  lcd.print(thresholdExceeded);
}

void tooLoud() {
  thresholdExceeded = true;
}

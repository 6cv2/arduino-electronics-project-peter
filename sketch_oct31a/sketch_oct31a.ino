#include <LiquidCrystal_I2C.h>    // Include the Liquid crystal library for the LCD display

const int ANALOG_IN_PIN = A0;     // input from sound sensor

const int LED_PIN_1 = 11;         // setting up all led pin locations
const int LED_PIN_2 = 10;
const int LED_PIN_3 = 9;
const int LED_PIN_4 = 8;
const int LED_PIN_5 = 7;

const int THRESHOLD_1 = 400;      // setting up all volume level thresholds
const int THRESHOLD_2 = 450;
const int THRESHOLD_3 = 510;
const int THRESHOLD_4 = 550;
const int THRESHOLD_5 = 630;

bool isThresholdExceeded = false;  // sets starting state for the interrupt threshold
const int INTERRUPT_PIN = 2;       // interrupt pin location

int sensorValue = 0;
int averageSensorValue = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);// configures the displays text dimensions

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN_1, OUTPUT);      // LED pins
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_5, OUTPUT);

  pinMode(INTERRUPT_PIN, INPUT);   // sets up the interrupts pin mode
  lcd.init();                      // initializes LCD display
  lcd.backlight();

  // Attaches interrupt, defines pin, and triggers tooLoud interrupt on rising signal of INTERRUPT_PIN
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), tooLoud, RISING); 
}

void loop() {
  // takes 500 readings from sensor and averages it out for a smoother volume variable
  unsigned long totalSensorValue = 0;
  for (int i = 0; i < 500; i++) {
    sensorValue = analogRead(ANALOG_IN_PIN);
    totalSensorValue += sensorValue;
  }
  averageSensorValue = totalSensorValue / 500;


  // If the sensors volume value is over the threshold for the specific led turn it on
  if (averageSensorValue > THRESHOLD_1) {
    digitalWrite(LED_PIN_1, HIGH);
  } else {
    digitalWrite(LED_PIN_1, LOW);
  }
  if (averageSensorValue > THRESHOLD_2) {
    digitalWrite(LED_PIN_2, HIGH);
  } else {
    digitalWrite(LED_PIN_2, LOW);
  }
  if (averageSensorValue > THRESHOLD_3) {
    digitalWrite(LED_PIN_3, HIGH);
  } else {
    digitalWrite(LED_PIN_3, LOW);
  }
  if (averageSensorValue > THRESHOLD_4) {
    digitalWrite(LED_PIN_4, HIGH);
  } else {
    digitalWrite(LED_PIN_4, LOW);
  }
  if (averageSensorValue > THRESHOLD_5) {
    digitalWrite(LED_PIN_5, HIGH);
  } else {
    digitalWrite(LED_PIN_5, LOW);
  }

  // Prints the average sensor value to the serial monitor
  Serial.print("sensor = ");
  Serial.println(averageSensorValue);


  // Prints the average sensor value to the LCD display
  lcd.setCursor(0, 0);
  lcd.print("Volume: ");
  lcd.print(averageSensorValue);
  lcd.print("    ");
  // Then on second line prints if the interrupt has been activated or not
  lcd.setCursor(0, 1);
  lcd.print("Too loud?: ");
  if (isThresholdExceeded) {
    lcd.print("Yes");
  } else {
      lcd.print("no");
}}

  // Interrupt activated if volume threshold reached
void tooLoud() {
  // sets the variable to true changing what's displayed on the second line of the LCD display
  isThresholdExceeded = true;
}
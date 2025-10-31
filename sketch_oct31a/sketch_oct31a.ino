
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9;
const int ledPin = 2;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  unsigned long rollingAverage = 0;

  for(int i=0; i<500; i++){
    sensorValue = analogRead(analogInPin);
    rollingAverage += sensorValue;
    delay(10);
  }
  float outputValue = rollingAverage/500;

  Serial.print("sensor = ");
  Serial.println(outputValue);
}

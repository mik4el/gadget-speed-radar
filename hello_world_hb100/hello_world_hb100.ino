const int analogInPin = A0; // Analog input pin for amplified hb100

int sensorValue = 0; // value read from the amplifier output

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // print the results to the serial monitor:
  Serial.print("hb100 = ");
  Serial.print(sensorValue);
  Serial.println("");

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(2);
}

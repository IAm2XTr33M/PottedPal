
// Sensor pins pin D6 LED output, pin A0 analog Input
#define sensorPin A0
#define sensorLicht A1
#define sensorTemp A2

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(sensorLicht, INPUT);
  pinMode(sensorTemp, INPUT);
}


void loop() {
  //Serial.print("Analog output: ");
  Serial.print(analogRead(sensorPin));
  Serial.print(",");
  Serial.print(analogRead(sensorLicht));
  Serial.print(",");
  Serial.println(analogRead(sensorTemp)); 	
  delay(100);
}

int readSensor() {
  int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
  int outputValue = map(sensorValue, 0, 1023, 100, 0); // map the 10-bit data to 8-bit data
  return sensorValue;             // Return analog moisture value
}
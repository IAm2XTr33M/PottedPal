
// Sensor pins pin D6 LED output, pin A0 analog Input
#define sensorPin 32 //D32
#define sensorLicht 34 //D34
#define sensorTemp 35 //D35

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(sensorLicht, INPUT);
  pinMode(sensorTemp, INPUT);
}


void loop() {
  Serial.print("mois:");
  Serial.print(map(analogRead(sensorPin), 0, 4095, 0, 100));
  Serial.print(",");
  Serial.print("licht:");
  Serial.print(map(analogRead(sensorLicht), 0, 4095, 0, 100));
  Serial.print(",");
  Serial.print("temp:");
  int sensorVal = analogRead(sensorTemp);
  float voltage = (sensorVal / 4095.0) * 5.0;
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);
  delay(100);
}


float temp(){
  float voltage = (sensorTemp / 1024.0) * 5.0;

}
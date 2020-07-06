int airValue = 600;
int waterValue = 230;

int soilMoistureAnalogReading = 0;
int soilMoisturePercentage = 0;

bool pumpOn = false;
int moistureSensor = A2;
int waterRelay = 9;

void setup() {
  Serial.begin(57600);
  
  pinMode(moistureSensor, INPUT);
  pinMode(waterRelay, OUTPUT);

  // Ensure pump is switched off on startup
  analogWrite(waterRelay, 255);
}

void loop() {
  soilMoistureAnalogReading = analogRead(moistureSensor);
  soilMoisturePercentage = map(soilMoistureAnalogReading, airValue, waterValue, 0, 100);
  Serial.println(soilMoistureAnalogReading);
  Serial.print(soilMoisturePercentage);
  Serial.println("% moisture\n");

  if (soilMoisturePercentage < 30) {
    togglePump(true);
  } else if (soilMoisturePercentage > 90) {
    togglePump(false);
  }
  
  delay(500);
}

void togglePump(bool on) {
  int analogValue = on ? 0 : 255;
  analogWrite(waterRelay, analogValue);
}

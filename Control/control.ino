const int AIR_VALUE = 600;
const int WET_VALUE = 220;
const int PUMP_TIMER = 2000;
const int PAUSE_TIME = 3000;
const int BAUD = 9600;
const int WATERING_THRESHOLD = 95;
const int MONITORING_THRESHOLD = 30;

int soilMoistureAnalogReading = 0;
int soilMoisturePercentage = 0;
int dryReading = 0;

int moistureSensor = A2;
int waterRelay = 9;

void setup() {
  Serial.begin(BAUD);

  pinMode(moistureSensor, INPUT);
  pinMode(waterRelay, OUTPUT);

  // Ensure pump is switched off on startup
  analogWrite(waterRelay, 255);
}

void loop() {
  bool needsWater = checkMoisture(false);
  if (needsWater) {
    handleLowMoisture();
  }
  delay(500);
}

void handleLowMoisture() {
  int counter = 0;
  bool cont = true;
  dryReading = soilMoisturePercentage;

  while (cont) {
    ++counter;
    togglePump(true);
    delay(PUMP_TIMER);
    togglePump(false);
    delay(PAUSE_TIME);
    cont = checkMoisture(true);
    delay(500);
  }

  sendSerialMessage(counter * PUMP_TIMER, true);
}

bool checkMoisture(bool isWatering) {
  const int comparator = isWatering ? WATERING_THRESHOLD : MONITORING_THRESHOLD;
  int previousPercentage = soilMoisturePercentage;
  soilMoistureAnalogReading = analogRead(moistureSensor);
  soilMoisturePercentage = map(soilMoistureAnalogReading, AIR_VALUE, WET_VALUE, 0, 100);
  if (soilMoisturePercentage != previousPercentage) {
    sendSerialMessage(0, false);
  }
  return soilMoisturePercentage < comparator;
}

void togglePump(bool on) {
  int analogValue = on ? 0 : 255;
  analogWrite(waterRelay, analogValue);
  delay(200);
}

void sendSerialMessage(int duration, bool isWatering) {
  if (isWatering) {
    Serial.print(dryReading);
    Serial.print(",");
    Serial.print(soilMoisturePercentage);
    Serial.print(",");
    Serial.println(duration);
  } else {
    Serial.println(soilMoisturePercentage);
  }
}

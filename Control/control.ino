int counter = 0;

void setup() {
  // LED_BUILDIN is an alias to pin 13 on the Arduino Uno.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(57600);
}

void loop() {
  if (counter == 5) {
    counter = 0;
  } else {
    ++counter;
  }
  Serial.print("TEST");
  Serial.println(counter);
  delay(500);
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(1000);
//
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(1000);
}

const int soilPin = A0;
const int blueLED = 8;
const int redLED = 9;
const int buzzer = 10;

// Adjust this after testing
const int threshold = 500;

void setup() {
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int soilValue = analogRead(soilPin);

  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  if (soilValue >= threshold) {
    // Soil is dry
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
  } else {
    // Soil is wet
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(500);
}
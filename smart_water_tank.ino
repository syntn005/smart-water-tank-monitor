
const float tankHeight = 120.0;

// Set true to simulate filling and draining in Tinkercad.
// Set false to use the actual HC-SR04 sensor.
const bool simulationMode = true;

const int trigPin = 9;
const int echoPin = 10;

const int pumpLed = 5;
const int greenLed = 6;
const int redLed = 7;
const int buzzer = 8;

float waterLevel = 5.0;
float distance = 115.0;
float duration = 0.0;

bool pumpOn = true;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(pumpLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // 1. Get the ultrasonic travel time
  if (simulationMode) {
    // Simulate the distance from sensor to water
    distance = tankHeight - waterLevel;

    // Generate the equivalent sound travel time
    duration = (distance * 2.0) / 0.0343;
  } else {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0) {
      Serial.println("No echo detected. Check sensor.");
      delay(500);
      return;
    }
  }

  // 2. Calculate distance using the ultrasonic formula
  float distance = duration * 0.0343 / 2.0;

  // 3. Calculate water level from tank height
  waterLevel = tankHeight - distance;
  waterLevel = constrain(waterLevel, 0.0, tankHeight);

  float percentage = (waterLevel / tankHeight) * 100.0;

  // 4. Automatic pump control
  if (percentage <= 20.0) {
    pumpOn = true;
  }

  if (percentage >= 90.0) {
    pumpOn = false;
  }

  // 5. Simulate water filling and everyday water usage
  if (simulationMode) {
    if (pumpOn) {
      waterLevel += 1.0;  // Water enters the tank
    } else {
      waterLevel -= 0.5;  // Water is used
    }

    waterLevel = constrain(waterLevel, 0.0, tankHeight);
  }

  // 6. Control the indicator LEDs
  digitalWrite(pumpLed, pumpOn ? HIGH : LOW);
  digitalWrite(greenLed, percentage < 80.0 ? HIGH : LOW);
  digitalWrite(redLed, percentage >= 80.0 ? HIGH : LOW);

  // 7. Overflow warning
  if (percentage >= 90.0) {
    tone(buzzer, 1000);
  } else {
    noTone(buzzer);
  }

  // 8. Display readings
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Water Level: ");
  Serial.print(percentage);
  Serial.print("% | Pump: ");
  Serial.println(pumpOn ? "ON" : "OFF");

  delay(500);
}

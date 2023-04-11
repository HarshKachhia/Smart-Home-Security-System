// Pinout definitions
int PSD_PIN = A5;
int PHOTOC_PIN = A0;
int LED_PIN = 13;
int SPEAKER_PIN = 10;
int ALARM_DELAY = 5000;
int IR_PIN = 4;
int BUTTON_PIN = 9;
int TOUCH_PIN = 3;
int SENSOR_PIN = 2;

int lastIrValue = 0;
boolean sensorValue = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TOUCH_PIN, INPUT);
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // Read PSD distance sensor value
  int distance = analogRead(PSD_PIN);
  Serial.print("Distance: ");
  Serial.println(distance);

  // Read photocell sensor value
  int lightLevel = analogRead(PHOTOC_PIN);
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  // Check if an object is detected within a certain distance
  if (distance < 300) {
    // Trigger alarm and turn on LED
    digitalWrite(LED_PIN, HIGH);
    tone(SPEAKER_PIN, 1000);
    delay(ALARM_DELAY);
    noTone(SPEAKER_PIN);
    digitalWrite(LED_PIN, LOW);
  }

  // Check for changes in ambient light
  if (lightLevel > 300) {
    // Trigger alarm and turn on LED
    digitalWrite(LED_PIN, HIGH);
    tone(SPEAKER_PIN, 1000);
    delay(ALARM_DELAY);
    noTone(SPERAKE_PIN);
    digitalWrite(LED_PIN, LOW);
  }

  // Check if button is not pressed
  if (digitalRead(BUTTON_PIN) != 1) {
    // Check if IR sensor value changes
    if (digitalRead(IR_PIN) != lastIrValue) {
      // Turn on speaker for 1 second
      digitalWrite(SPEAKER_PIN, HIGH);
      delay(1000);
      digitalWrite(SPEAKER_PIN, LOW);
      
      // Print out IR sensor value
      Serial.print("IR sensor value: ");
      Serial.println(digitalRead(IR_PIN));
    }
  }

  // Update IR sensor value
  lastIrValue = digitalRead(IR_PIN);

  // Check if touch sensor is triggered
  if (digitalRead(TOUCH_PIN) == HIGH) {
    // Turn on speaker
    digitalWrite(SPEAKER_PIN, HIGH);
    delay(1500);
    // Turn off speaker
    digitalWrite(SPEAKER_PIN, LOW);
    delay(1500);
    
    // Print out touch sensor value
    Serial.print("Touch sensor value: ");
    Serial.println(digitalRead(TOUCH_PIN));
  }

  // Read generic sensor value
  sensorValue = digitalRead(SENSOR_PIN);
  Serial.println(sensorValue);

  // Check if generic sensor value is HIGH
  if (sensorValue == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    tone(SPEAKER_PIN, 2000);
    delay(1000);
    noTone(SPEAKER_PIN);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(SPEAKER_PIN, LOW);
  }

  // Add delay for next loop iteration
  delay(100);
}

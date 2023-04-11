#include <Adafruit_NeoPixel.h>

// Pinout definitions
int PSD_PIN = A5;
int PHOTOC_PIN = A0;
int NEOPIXEL_PIN = 13;
int SPEAKER_PIN = 10;
int ALARM_DELAY = 5000;
int IR_PIN = 4;
int BUTTON_PIN = 9;
int TOUCH_PIN = 3;
int SENSOR_PIN = 2;

int lastIrValue = 0;
boolean sensorValue = 0;

// Define NeoPixel stick object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Function to turn on speaker sound and NeoPixel with given color
void turnOnAlarm(int r, int g, int b) {
  // Turn on NeoPixel
  strip.setPixelColor(0, r, g, b);
   strip.setPixelColor(1, r, g, b);
    strip.setPixelColor(2, r, g, b);
     strip.setPixelColor(3, r, g, b);
      strip.setPixelColor(4, r, g, b);
       strip.setPixelColor(5, r, g, b);
        strip.setPixelColor(6, r, g, b);

  strip.show();

  // Turn on speaker
  tone(SPEAKER_PIN, 1000);
  delay(ALARM_DELAY);
  noTone(SPEAKER_PIN);

  // Turn off NeoPixel
  strip.setPixelColor(0, 0, 0, 0);
  strip.setPixelColor(1, 0, 0, 0);
  strip.setPixelColor(2, 0, 0, 0);
  strip.setPixelColor(3, 0, 0, 0);
  strip.setPixelColor(4, 0, 0, 0);
  strip.setPixelColor(5, 0, 0, 0);
  strip.setPixelColor(6, 0, 0, 0);
  strip.show();
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TOUCH_PIN, INPUT);
  pinMode(SENSOR_PIN, INPUT);

  // Initialize NeoPixel
  strip.begin();
  strip.setBrightness(50);
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
  if (distance < 200) {
    // Trigger alarm and turn on NeoPixel
   Serial.println("PSD Triggered: Intruder Alert");
    turnOnAlarm(255, 0, 0); // Red
  }

  // Check for changes in ambient light
  if (lightLevel > 300) {
    // Trigger alarm and turn on NeoPixel
    Serial.println("Photcell Sensor Triggered: Intruder Alert");
    turnOnAlarm(255, 255, 255); // White
  }
  //if button is pressed
 if (digitalRead(BUTTON_PIN) == 1)
  {
    Serial.println("Passcode Inputted: Welcome Homeowner");
    delay(1000);
  }
  // Check if button is not pressed
  if (digitalRead(BUTTON_PIN) != 1) {
    // Check if IR sensor value changes
    if (digitalRead(IR_PIN) != lastIrValue) {
      // Turn on speaker for 1 second
      Serial.print("IR sensor Triggered: Intruder Alert");
       turnOnAlarm(0, 255, 0); // Green

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
   Serial.println("Touch Sensor Triggered: Back Door Break-in Detected");
   turnOnAlarm(0, 255, 255); //Cyan color

    // Print out touch sensor value
    Serial.print("Touch sensor value: ");
    Serial.println(digitalRead(TOUCH_PIN));
  }

  // Read sound sensor value
  sensorValue = digitalRead(SENSOR_PIN);
  Serial.print("Sound Sensor Value: ");
 Serial.println(sensorValue);

  // Check if sound sensor value is HIGH
  if (sensorValue == HIGH) {
    Serial.println("Sound Sensor Triggered: Window Break-in Detected");
    turnOnAlarm(255, 0, 255); //magenta color
  }
  else {
    digitalWrite(NEOPIXEL_PIN, LOW);
    digitalWrite(SPEAKER_PIN, LOW);
  }

  // Add delay for next loop iteration
  delay(100);
}

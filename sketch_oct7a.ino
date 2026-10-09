/*************************************************************
  Blynk Motor & Speed Control Setup
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID        "TMPL6oeKqd1eD"
#define BLYNK_TEMPLATE_NAME      "Quickstart Template"
#define BLYNK_AUTH_TOKEN        "uFIFXGEbxxgpg-VevbTt18x1aRrHtBv3"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "HOTSPOT@UPNJATIM.AC.ID";
char pass[] = "belanegara";

// Pin Definitions
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 12;
int blueLedPin = 2; // Built-in Blue LED

// PWM Settings
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
bool motorStatus = false;
bool lampStatus = false;

BlynkTimer timer;

// Control Motor ON/OFF via Virtual Pin V0
BLYNK_WRITE(V0) {
  int value = param.asInt();
  if (value == 1) {
    motorStatus = true;
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel, dutyCycle);
    Serial.println("Motor ON");
  } else {
    motorStatus = false;
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel, 0);
    Serial.println("Motor OFF");
  }
}

// Control Motor Speed via Virtual Pin V4 (Range 0 - 255)
BLYNK_WRITE(V4) {
  int speed = param.asInt();
  dutyCycle = constrain(speed, 0, 255);
  Serial.print("Speed updated: ");
  Serial.println(dutyCycle);

  if (motorStatus) {
    ledcWrite(pwmChannel, dutyCycle);
  }
}

// Control Blue Lamp Blink via Virtual Pin V5
BLYNK_WRITE(V5) {
  lampStatus = param.asInt();
  if (!lampStatus) {
    digitalWrite(blueLedPin, LOW); // Turn off LED immediately when V5 is 0
    Serial.println("Lamp OFF");
  } else {
    Serial.println("Lamp ON (Blinking)");
  }
}

// Non-blocking timer task to handle LED blinking (200ms ON / 200ms OFF)
void blinkLampEvent() {
  if (lampStatus) {
    digitalWrite(blueLedPin, !digitalRead(blueLedPin)); // Toggle LED state
  }
}

BLYNK_CONNECTED() {
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent() {
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  Serial.begin(115200);

  // Configure Pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  // Configure ESP32 PWM
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer Setups
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(1000L, blinkLampEvent); // Toggles LED every 200ms
}

void loop() {
  Blynk.run();
  timer.run();
}
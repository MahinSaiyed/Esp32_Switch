#define BLYNK_TEMPLATE_ID "TMPL3i5sLU3P5"
#define BLYNK_TEMPLATE_NAME "myesp32switch"
#define BLYNK_AUTH_TOKEN "JY8ctbY0wpsmJiDCGZxszeo5P2T65HpF"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// -------- WIFI DETAILS ----------
char ssid[] = "JioAirfiber";
char pass[] = "0987654321";

// ---------- RELAY PIN ----------
#define RELAY1_PIN 33   // Relay 1
#define RELAY2_PIN 32   // Relay 2

BlynkTimer timer;

// -------- APP WRITE HANDLER FOR RELAY 1 (V1) ----------
BLYNK_WRITE(V1) {
  int value = param.asInt();

  Serial.print("Relay 1 Value: ");
  Serial.println(value);

  digitalWrite(RELAY1_PIN, value == 1 ? LOW : HIGH);

  Blynk.virtualWrite(V3, digitalRead(RELAY1_PIN)); // Optional feedback
}

// -------- APP WRITE HANDLER FOR RELAY 2 (V2) ----------
BLYNK_WRITE(V2) {
  int value = param.asInt();

  Serial.print("Relay 2 Value: ");
  Serial.println(value);

  digitalWrite(RELAY2_PIN, value == 1 ? LOW : HIGH);

  Blynk.virtualWrite(V4, digitalRead(RELAY2_PIN)); // Optional feedback
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  // Boot par dono relay OFF
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  Serial.println("Boot Status: Relay1 OFF, Relay2 OFF");

  // Blynk connect
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
}

#define BLYNK_TEMPLATE_ID "TMPL3i5sLU3P5"
#define BLYNK_TEMPLATE_NAME "myesp32switch"
#define BLYNK_AUTH_TOKEN "JY8ctbY0wpsmJiDCGZxszeo5P2T65HpF"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// -------- WIFI DETAILS ----------
char ssid[] = "Saiyed House_4G";
char pass[] = "8347874084SAIYEDF3";

// ---------- RELAY PIN ----------
#define RELAY1_PIN 33
#define RELAY2_PIN 32

// ---------- ESP32 BLUE LED ----------
#define WIFI_LED 2

BlynkTimer timer;

// -------- RELAY 1 (V1) ----------
BLYNK_WRITE(V1) {
  int value = param.asInt();

  Serial.print("Relay 1 Value: ");
  Serial.println(value);

  digitalWrite(RELAY1_PIN, value == 1 ? LOW : HIGH);
  Blynk.virtualWrite(V3, digitalRead(RELAY1_PIN));
}

// -------- RELAY 2 (V2) ----------
BLYNK_WRITE(V2) {
  int value = param.asInt();

  Serial.print("Relay 2 Value: ");
  Serial.println(value);

  digitalWrite(RELAY2_PIN, value == 1 ? LOW : HIGH);
  Blynk.virtualWrite(V4, digitalRead(RELAY2_PIN));
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);

  // Relay OFF at startup
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  // LED OFF at startup
  digitalWrite(WIFI_LED, LOW);

  Serial.println("Boot Status: Relay1 OFF, Relay2 OFF");

  // Connect Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {

  // Check WiFi/Blynk connection
  if (Blynk.connected()) {

    int rssi = WiFi.RSSI(); // Signal strength

    Serial.print("WiFi Signal: ");
    Serial.println(rssi);

    // Level 1: Strong signal
    if (rssi >= -55) {
      digitalWrite(WIFI_LED, HIGH);
    }

    // Level 2: Slightly weak
    else if (rssi >= -65) {
      digitalWrite(WIFI_LED, HIGH);
      delay(2000);
      digitalWrite(WIFI_LED, LOW);
      delay(2000);
    }

    // Level 3: Weak
    else if (rssi >= -75) {
      digitalWrite(WIFI_LED, HIGH);
      delay(700);
      digitalWrite(WIFI_LED, LOW);
      delay(700);
    }

    // Level 4: Very weak
    else {
      digitalWrite(WIFI_LED, HIGH);
      delay(200);
      digitalWrite(WIFI_LED, LOW);
      delay(200);
    }

  } else {
    // WiFi disconnected
    digitalWrite(WIFI_LED, LOW);
  }

  Blynk.run();
  timer.run();
}

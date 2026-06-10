#define BLYNK_TEMPLATE_ID "TMPL3i5sLU3P5"
#define BLYNK_TEMPLATE_NAME "myesp32switch"
#define BLYNK_AUTH_TOKEN "JY8ctbY0wpsmJiDCGZxszeo5P2T65HpF"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// ---------- 3 WIFI NETWORKS ----------
char* ssids[] = {
  "Saiyed House_4G",
  "JioAirfiber",
  "Saiyed House_5G"
};

char* passwords[] = {
  "8347874084SAIYED--",
  "09876543--",
  "MAHIN@%003%--"
};

const int totalNetworks = 3;

// ---------- RELAY PIN ----------
#define RELAY1_PIN 33
#define RELAY2_PIN 32

// ---------- STATUS LED ----------
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

// ---------- CONNECT WIFI ----------
void connectWiFi() {

  bool connected = false;

  while (!connected) {

    for (int i = 0; i < totalNetworks; i++) {

      Serial.print("Trying WiFi: ");
      Serial.println(ssids[i]);

      WiFi.begin(ssids[i], passwords[i]);

      int attempt = 0;

      while (WiFi.status() != WL_CONNECTED && attempt < 10) {
        delay(1000);
        Serial.print(".");
        attempt++;
      }

      if (WiFi.status() == WL_CONNECTED) {

        Serial.println("\nWiFi Connected!");
        Serial.print("Connected to: ");
        Serial.println(ssids[i]);

        connected = true;
        break;
      }
    }

    if (!connected) {
      Serial.println("Retrying all WiFi networks...");
      delay(3000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);

  // Boot par relay OFF
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  // LED OFF startup
  digitalWrite(WIFI_LED, LOW);

  Serial.println("Boot Status: Relay1 OFF, Relay2 OFF");

  // Connect WiFi
  connectWiFi();

  // Connect Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();
}

void loop() {

  // If WiFi disconnected → reconnect
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(WIFI_LED, LOW);
    connectWiFi();
  }

  // ---------- WiFi Signal LED ----------
  int rssi = WiFi.RSSI();

  if (WiFi.status() == WL_CONNECTED) {

    // Strong signal → LED always ON
    if (rssi >= -55) {
      digitalWrite(WIFI_LED, HIGH);
    }

    // Slight weak
    else if (rssi >= -65) {
      digitalWrite(WIFI_LED, !digitalRead(WIFI_LED));
      delay(2000);
    }

    // Weak
    else if (rssi >= -75) {
      digitalWrite(WIFI_LED, !digitalRead(WIFI_LED));
      delay(700);
    }

    // Very weak
    else {
      digitalWrite(WIFI_LED, !digitalRead(WIFI_LED));
      delay(200);
    }

  } else {
    digitalWrite(WIFI_LED, LOW);
  }

  Blynk.run();
  timer.run();
}

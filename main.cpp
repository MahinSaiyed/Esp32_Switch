
#define BLYNK_TEMPLATE_ID "TMPL3x-9CE7Tg"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "YUowSKf7hkBzmNE0lJeI03hOdKQdh6Ua"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// ---------- 3 WIFI NETWORKS ----------
const char* ssids[] = {
  "Saiyed House_4G",
  "JioAirfiber",
  "Saiyed-56 5G"
};

const char* passwords[] = {
  "8347874084SAIYEDF3",
  "0987654321",
  "?@890000"
};

const int totalNetworks = 3;

// ---------- RELAY PINS ----------
#define RELAY1_PIN 13
#define RELAY2_PIN 12
#define RELAY3_PIN 14
#define RELAY4_PIN 27
#define RELAY5_PIN 26
#define RELAY6_PIN 25
#define RELAY7_PIN 33
#define RELAY8_PIN 32
#define RELAY9_PIN 4
#define RELAY10_PIN 5
// ---------- BATTERY SENSOR ----------
#define BATTERY_PIN 34

// ---------- STATUS LED ----------
#define WIFI_LED 2

BlynkTimer timer;

// ---------- BATTERY VOLTAGE ----------
void sendBatteryVoltage() {

  int adcValue = analogRead(BATTERY_PIN);

  // ESP32 ADC Voltage
  float adcVoltage = adcValue * (3.3 / 4095.0);

  // 0-25V Voltage Sensor Module
  float batteryVoltage = adcVoltage * 5.0;

  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage, 2);
  Serial.println(" V");

  Blynk.virtualWrite(V13, batteryVoltage);
}

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

// -------- RELAY 3 to 10 STATUS (V3 to V11) ----------

// -------- RELAY 3 (V4) ----------
BLYNK_WRITE(V4) {
  int value = param.asInt();

  Serial.print("Relay 3 Value: ");
  Serial.println(value);

  digitalWrite(RELAY3_PIN, value == 1 ? LOW : HIGH);
}

// -------- RELAY 4 (V5) ----------
BLYNK_WRITE(V5) {
  int value = param.asInt();

  Serial.print("Relay 4 Value: ");
  Serial.println(value);

  digitalWrite(RELAY4_PIN, value == 1 ? LOW : HIGH);
}

// -------- RELAY 5 (V6) ----------
BLYNK_WRITE(V6) {
  int value = param.asInt();

  Serial.print("Relay 5 Value: ");
  Serial.println(value);

  digitalWrite(RELAY5_PIN, value == 1 ? LOW : HIGH);
}

// -------- RELAY 6 (V7) ----------
BLYNK_WRITE(V7) {
  int value = param.asInt();

  Serial.print("Relay 6 Value: ");
  Serial.println(value);

  digitalWrite(RELAY6_PIN, value == 1 ? LOW : HIGH);
}

// -------- RELAY 7 (V8) ----------
BLYNK_WRITE(V8) {
  int value = param.asInt();

  Serial.print("Relay 7 Value: ");
  Serial.println(value);

  digitalWrite(RELAY7_PIN, value == 1 ? LOW : HIGH);
}

// -------- RELAY 8 (V9) ----------
BLYNK_WRITE(V9) {
  int value = param.asInt();

  Serial.print("Relay 8 Value: ");
  Serial.println(value);

  digitalWrite(RELAY8_PIN, value == 1 ? LOW : HIGH);
}

// -------- RELAY 9 (V10) ----------
BLYNK_WRITE(V10) {
  int value = param.asInt();

  Serial.print("Relay 9 Value: ");
  Serial.println(value);

  digitalWrite(RELAY9_PIN, value == 1 ? LOW : HIGH);
}

// -------- RELAY 10 (V11) ----------
BLYNK_WRITE(V11) {
  int value = param.asInt();

  Serial.print("Relay 10 Value: ");
  Serial.println(value);

  digitalWrite(RELAY10_PIN, value == 1 ? LOW : HIGH);
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
pinMode(RELAY3_PIN, OUTPUT);
pinMode(RELAY4_PIN, OUTPUT);
pinMode(RELAY5_PIN, OUTPUT);
pinMode(RELAY6_PIN, OUTPUT);
pinMode(RELAY7_PIN, OUTPUT);
pinMode(RELAY8_PIN, OUTPUT);
pinMode(RELAY9_PIN, OUTPUT);
pinMode(RELAY10_PIN, OUTPUT);


pinMode(BATTERY_PIN, INPUT);
pinMode(WIFI_LED, OUTPUT);

timer.setInterval(1000L, sendBatteryVoltage);

  // Boot par relay 

digitalWrite(RELAY1_PIN, HIGH);
digitalWrite(RELAY2_PIN, HIGH);
digitalWrite(RELAY3_PIN, HIGH);
digitalWrite(RELAY4_PIN, HIGH);
digitalWrite(RELAY5_PIN, HIGH);
digitalWrite(RELAY6_PIN, HIGH);
digitalWrite(RELAY7_PIN, HIGH);
digitalWrite(RELAY8_PIN, HIGH);
digitalWrite(RELAY9_PIN, HIGH);
digitalWrite(RELAY10_PIN, HIGH);

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

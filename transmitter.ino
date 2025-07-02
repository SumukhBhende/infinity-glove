#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SmartController";
const char* password = "12345678";

const int flex1Pin = 36; // GPIO36 - ADC1_CH0
const int flex2Pin = 39; // GPIO39 - ADC1_CH3

int threshold = 1500; // Adjust based on your flex sensor readings
bool relay1Sent = false;
bool relay2Sent = false;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to ESP8266 AP");
}

void loop() {
  int flex1Value = analogRead(flex1Pin);
  int flex2Value = analogRead(flex2Pin);

  Serial.printf("Flex1: %d  Flex2: %d\n", flex1Value, flex2Value);

  // Relay 1 trigger
  if (flex1Value > threshold && !relay1Sent) {
    sendRelayToggle(1);
    relay1Sent = true;
  } else if (flex1Value < threshold - 100) {
    relay1Sent = false;
  }

  // Relay 2 trigger
  if (flex2Value > threshold && !relay2Sent) {
    sendRelayToggle(2);
    relay2Sent = true;
  } else if (flex2Value < threshold - 100) {
    relay2Sent = false;
  }

  delay(100);
}

void sendRelayToggle(int relayNum) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://192.168.4.1/toggle" + String(relayNum);
    http.begin(url);
    int response = http.POST("");
    Serial.printf("Relay %d toggle sent. Response: %d\n", relayNum, response);
    http.end();
  }
}

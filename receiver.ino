#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

#define RELAY1_PIN 5  // GPIO5 (D1)
#define RELAY2_PIN 4  // GPIO4 (D2)
#define EEPROM_SIZE 2

WebServer server(80);

// Relay state variables
bool relay1State = false;
bool relay2State = false;

void setupWiFi() {
  WiFi.softAP("SmartController", "12345678");
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void setupEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  relay1State = EEPROM.read(0);
  relay2State = EEPROM.read(1);
}

void saveState() {
  EEPROM.write(0, relay1State);
  EEPROM.write(1, relay2State);
  EEPROM.commit();
}

void updateRelays() {
  digitalWrite(RELAY1_PIN, relay1State ? LOW : HIGH);
  digitalWrite(RELAY2_PIN, relay2State ? LOW : HIGH);
}

void handleRoot() {
  String page = R"=====(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body { font-family: Arial; text-align: center; padding: 20px; background: #f0f0f0; }
        .btn { font-size: 22px; padding: 15px 30px; margin: 20px; border: none; border-radius: 8px; }
        .on { background: #4CAF50; color: white; }
        .off { background: #f44336; color: white; }
      </style>
    </head>
    <body>
      <h2>ESP32 Relay Controller</h2>
      <form action="/toggle1" method="get">
        <button class="btn %STATE1%">Relay 1: %STATE1_TEXT%</button>
      </form>
      <form action="/toggle2" method="get">
        <button class="btn %STATE2%">Relay 2: %STATE2_TEXT%</button>
      </form>
    </body>
    </html>
  )=====";

  page.replace("%STATE1%", relay1State ? "on" : "off");
  page.replace("%STATE1_TEXT%", relay1State ? "ON" : "OFF");
  page.replace("%STATE2%", relay2State ? "on" : "off");
  page.replace("%STATE2_TEXT%", relay2State ? "ON" : "OFF");

  server.send(200, "text/html", page);
}

void handleToggle1() {
  relay1State = !relay1State;
  saveState();
  updateRelays();
  handleRoot();
}

void handleToggle2() {
  relay2State = !relay2State;
  saveState();
  updateRelays();
  handleRoot();
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  setupEEPROM();
  updateRelays();
  setupWiFi();

  server.on("/", handleRoot);
  server.on("/toggle1", handleToggle1);
  server.on("/toggle2", handleToggle2);
  server.begin();
  Serial.println("Web server running");
}

void loop() {
  server.handleClient();
}

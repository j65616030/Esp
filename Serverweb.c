#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "tu_red_wifi";
const char* password = "tu_contraseña_wifi";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a Wi-Fi...");
  }
  Serial.println("Conectado a Wi-Fi");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/plain", "Hola, mundo!");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

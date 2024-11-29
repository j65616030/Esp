#include <ESP8266WiFi.h>

const char* ssid = "Red_Falsa";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.setPhyMode(WIFI_PHY_MODE_11B);
  WiFi.setChannel(1);
  WiFi.macAddress();
  WiFi.printDiag(Serial);
  WiFi.sniff(true); // Activar el modo de escucha de paquetes
}

void loop() {
  uint8_t* packet = WiFi.getSnifferPacket();
  if (packet != NULL) {
    Serial.println("Paquete capturado:");
    Serial.print("Fuente: ");
    Serial.println(packet[12], HEX);
    Serial.print("Destino: ");
    Serial.println(packet[15], HEX);
    Serial.print("Protocolo: ");
    Serial.println(packet[23], HEX);
    Serial.print("Longitud: ");
    Serial.println(packet[24], HEX);
  }
  delay(1000);
}

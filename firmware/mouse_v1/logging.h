#ifndef LOGGING_H
#define LOGGING_H


#define BLUETOOTH_DEBUGGING
//#define WIFI_DEBUGGING

#ifdef BLUETOOTH_DEBUGGING
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void initBluetooth(){
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");  // Bluetooth name
  Serial.println("Bluetooth ready. Connect to ESP32_BT");
}

#endif

#ifdef WIFI_DEBUGGING
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);
const char* ssid = "Phone 1_4549";      // WiFi SSID
const char* password = "ggboisss";      // WiFi Password

void initWebServer() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  WebSerial.begin(&server);
  server.begin();
}
#endif

void initLogging() {
#ifdef BLUETOOTH_DEBUGGING
  initBluetooth();
#endif

#ifdef WIFI_DEBUGGING
  initWebServer();
#endif
}


#endif
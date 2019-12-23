//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial Serial_BT;

#define sensourPIN A4 //GPIO32
int sensourThreshold_LOW = 0;
int sensourThreshold_HIGH = 4900;
// Bluetooth Device Name
const char* deviceName = "ESP32";


void setup() {
  //Serial.begin(115200);
  //Serial.println("The device started, now you can pair it with bluetooth!");
  String deviceNameSerial = String(deviceName);
  deviceNameSerial  += "_Serial_BT";
  Serial_BT.begin(deviceNameSerial); //Bluetooth device name
}

void loop() {
  int sensourValue = analogRead(sensourPIN);
  if (Serial_BT.available()) {
    if (sensourValue > sensourThreshold_LOW&& sensourThreshold_HIGH > sensourValue) {
      Serial_BT.println(sensourValue);
      delay(80);
    }
  }
  delay(20);
}

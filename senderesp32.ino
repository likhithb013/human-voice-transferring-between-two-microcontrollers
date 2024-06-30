#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <driver/adc.h>

BLEServer *pServer;
BLECharacteristic *pCharacteristic;

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32-A");
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  pServer->getAdvertising()->start();
}

void loop() {
  // Read microphone input and send over Bluetooth
  int micValue = analogRead(A0); // Read analog microphone input
  pCharacteristic->setValue((uint8_t*)&micValue, sizeof(micValue));
  pCharacteristic->notify();

  delay(10); // Reduce delay to minimize latency
}

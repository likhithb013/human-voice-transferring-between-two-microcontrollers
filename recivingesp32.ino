#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>

BLEClient*  pClient;
BLERemoteCharacteristic* pRemoteCharacteristic;

bool connected = false;
bool newData = false;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32-B");

  pClient  = BLEDevice::createClient();
  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remote BLE Server
  pClient->connect(BLEAddress("ESP32-A"));

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(SERVICE_UUID.toString().c_str());
    return;
  }

  // Obtain a reference to the characteristic in the service of the remote BLE server.
  pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(CHARACTERISTIC_UUID.toString().c_str());
    return;
  }

  // Read the initial value from the remote characteristic.
  std::string value = pRemoteCharacteristic->readValue();
  Serial.print("Initial characteristic value: ");
  Serial.println(value.c_str());

  // Register a callback function to be invoked when new data is received.
  pRemoteCharacteristic->registerForNotify(notifyCallback);
}

void loop() {
  if (newData) {
    // Process new data received from ESP32-A
    int micValue = *((int*)pRemoteCharacteristic->getData());
    // Implement speech filtering logic here (e.g., if needed)
    
    // Output to speaker
    analogWrite(DAC_PIN, micValue);

    newData = false;
  }
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pClient) {
    connected = true;
  }

  void onDisconnect(BLEClient* pClient) {
    connected = false;
  }
};

void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
  newData = true;
}

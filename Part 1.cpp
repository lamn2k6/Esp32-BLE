#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <RF24.h>

#define SERVICE_UUID "e5d25641-6d62-467e-8194-c2a1b6f703f6"
#define LED_CHAR_UUID "127a319c-89be-41cb-bc70-5072119cbd75"
#define SENSOR_CHAR_UUID "fd776028-0926-41bb-aaa1-5b877daab630"

BLECharacteristic *pLedCharacteristic;
String x ="";

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

BLEDevice::init("ESP_BLE");
BLEServer *pServer= BLEDevice::createServer();
BLEService *pService= pServer -> createService(SERVICE_UUID);
pLedCharacteristic= pService -> createCharacteristic(LED_CHAR_UUID,
BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

BLECharacteristic *pSensorCharacteristic= pService -> createCharacteristic(SENSOR_CHAR_UUID,
BLECharacteristic::PROPERTY_READ);
pSensorCharacteristic -> setValue("30.0");

pService -> start();
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
BLEDevice::startAdvertising();

Serial.print("BLE bắt đầu");


}

void loop() {
String n= pLedCharacteristic -> getValue();
if (n!=x){
  Serial.println(n);
}

 if(n=="1"){
 digitalWrite(2, HIGH);
 }else if(n=="0"){
  digitalWrite(2,LOW);
 }
x=n;
}

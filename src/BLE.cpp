#include "BLE.h"

#include "Common.h"

class Callbacks : public BLEServerCallbacks {
public:
    void onConnect(BLEServer *pServer) override {
        pServer->getAdvertising()->stop();
    }

    void onDisconnect(BLEServer *pServer) override {
        pServer->startAdvertising();
    }
};

void BLE::start() {
    BLEDevice::init(std::string(name));
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(PSYDUCK_SERVICE_UUID);
    for (auto characteristic: characteristics) {
        auto bleCharacteristic = pService->createCharacteristic(
                characteristic->getUUID(),
                characteristic->getProperties()
        );
        bleCharacteristic->setCallbacks(characteristic);
    }
    pService->start();
    pServer->setCallbacks(new Callbacks());
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->addServiceUUID(PSYDUCK_SERVICE_UUID);
    pAdvertising->setAppearance(0x0840);
    pAdvertising->setScanResponse(true);
//    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
//    pAdvertising->setMinPreferred(0x12);
    pAdvertising->start();
}

void BLE::addCharacteristic(Characteristic *characteristic) {
    characteristics.push_back(characteristic);
}

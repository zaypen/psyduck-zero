#ifndef PSYDUCK_KFC_BLE_H
#define PSYDUCK_KFC_BLE_H

#include <BLEDevice.h>
#include "Common.h"

class Characteristic : public BLECharacteristicCallbacks {
public:
    virtual const char *getUUID() = 0;

    virtual uint32_t getProperties() = 0;
};

template<const char *UUID, uint32_t properties>
class BaseCharacteristic : public Characteristic {
public:
    const char *getUUID() override {
        return UUID;
    }

    uint32_t getProperties() override {
        return properties;
    }
};

class BLE {
public:
    explicit BLE(const char *name) : name(name) {}

    void addCharacteristic(Characteristic *characteristic);

    void start();

private:
    const char *name;
    std::vector<Characteristic *> characteristics;
};


#endif //PSYDUCK_KFC_BLE_H

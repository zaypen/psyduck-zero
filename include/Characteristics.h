#ifndef PSYDUCK_CHARACTERISTICS_H
#define PSYDUCK_CHARACTERISTICS_H

#include "BLE.h"
#include "Arm.h"
#include "Foot.h"

class ArmEnabled : public BaseCharacteristic<
        PSYDUCK_ARM_ENABLED_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
> {
public:
    explicit ArmEnabled(Arm &arm) : arm(arm) {}

    void onRead(BLECharacteristic *pCharacteristic) override {
        pCharacteristic->setValue(&arm.getEnabled(), 1);
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        arm.setEnabled(*pCharacteristic->getData()); // FIXME: only first byte is used
    }

private:
    Arm &arm;
};

class ArmWait : public BaseCharacteristic<
        PSYDUCK_ARM_WAIT_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
> {
public:
    explicit ArmWait(Arm &arm) : arm(arm) {}

    void onRead(BLECharacteristic *pCharacteristic) override {
        pCharacteristic->setValue(arm.getCoolDown());
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        arm.setCoolDown(*reinterpret_cast<uint32_t *>(pCharacteristic->getData()));
    }

private:
    Arm &arm;
};

class FootEnabled : public BaseCharacteristic<
        PSYDUCK_FOOT_ENABLED_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
> {
public:
    explicit FootEnabled(Foot &foot) : foot(foot) {}

    void onRead(BLECharacteristic *pCharacteristic) override {
        pCharacteristic->setValue(&foot.getEnabled(), 1);
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        foot.setEnabled(*pCharacteristic->getData()); // FIXME: only first byte is used
    }

private:
    Foot &foot;
};

class FootSpeed : public BaseCharacteristic<
        PSYDUCK_FOOT_SPEED_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
> {
public:
    explicit FootSpeed(Foot &foot) : foot(foot) {}

    void onRead(BLECharacteristic *pCharacteristic) override {
        pCharacteristic->setValue(&foot.getSpeed(), 1);
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        foot.setSpeed(*pCharacteristic->getData()); // FIXME: only first byte is used
    }

private:
    Foot &foot;
};

class Mode : public BaseCharacteristic<
        PSYDUCK_MODE_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
> {
public:
    explicit Mode(Body &body) : body(body) {}

    void onRead(BLECharacteristic *pCharacteristic) override {
        pCharacteristic->setValue(&body.getMode(), 1);
    }

    void onWrite(BLECharacteristic *pCharacteristic) override {
        body.setMode(*pCharacteristic->getData()); // FIXME: only first byte is used
    }

private:
    Body &body;
};

#endif //PSYDUCK_CHARACTERISTICS_H

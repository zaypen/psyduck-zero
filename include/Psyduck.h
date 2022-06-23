#ifndef PSYDUCK_PSYDUCK_H
#define PSYDUCK_PSYDUCK_H

#include <Arduino.h>

class BluetoothA2DPSink;

class BLE;

class Arm;

class Foot;

class Body;

class Player;

class Psyduck {
public:
    explicit Psyduck();

    virtual ~Psyduck();

    void start();

    void loop();

private:
    BLE *ble;
    BluetoothA2DPSink *a2dp;
    Arm *arm;
    Foot *foot;
    Body *body;
    Player *player;
};


#endif //PSYDUCK_PSYDUCK_H

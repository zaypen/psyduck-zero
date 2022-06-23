#ifndef PSYDUCK_KFC_PLAYER_H
#define PSYDUCK_KFC_PLAYER_H

#include <Arduino.h>
#include <A2DP.h>

class Player {
public:
    explicit Player(const char *name, BluetoothA2DPSink &a2dp, void (*signal)());

    void start();

private:
    const char *name;
    BluetoothA2DPSink &a2dp;
};


#endif //PSYDUCK_KFC_PLAYER_H

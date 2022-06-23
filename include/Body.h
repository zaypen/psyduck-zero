#ifndef PSYDUCK_BODY_H
#define PSYDUCK_BODY_H

#include <Arduino.h>
#include "Arm.h"
#include "Foot.h"

enum ControlMode {
    Manual = 0,
    Auto
};

class Body {
public:
    explicit Body(Arm &arm, Foot &foot) : arm(arm), foot(foot), mode(ControlMode::Manual) {}

    uint8_t &getMode() {
        return mode;
    }

    void setMode(uint8_t value) {
        mode = value;
        stop();
    }

    void start() {
        arm.start();
        foot.start();
    }

    void stop() {
        arm.stop();
        foot.stop();
    }

    void notify(uint8_t isPlaying) {
        if (mode != Auto) {
            return;
        }
        if (isPlaying) {
            start();
        } else {
            stop();
        }
    }

private:
    Arm &arm;
    Foot &foot;
    uint8_t mode;
};

#endif //PSYDUCK_BODY_H

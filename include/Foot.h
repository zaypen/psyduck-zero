#ifndef PSYDUCK_FOOT_H
#define PSYDUCK_FOOT_H

#include <Arduino.h>

class Foot {
public:
    explicit Foot(uint8_t pin) : pin(pin), speed(127), enabled(0) {
        dacDisable(pin);
    }

    void start() {
        enabled = 1;
        update();
    }

    void stop() {
        enabled = 0;
        update();
    }

    uint8_t &getSpeed() {
        return speed;
    }

    void setSpeed(uint32_t value) {
        speed = value;
        update();
    }

    uint8_t &getEnabled() {
        return enabled;
    }

    void setEnabled(uint8_t value) {
        enabled = value ? 1 : 0;
        update();
    }

private:
    void update() const {
        if (enabled) {
            dacWrite(pin, speed);
        } else {
            dacDisable(pin);
        }
    }

private:
    uint8_t pin;
    uint8_t enabled;
    uint8_t speed;
};

#endif //PSYDUCK_FOOT_H

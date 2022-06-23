#ifndef PSYDUCK_ARM_H
#define PSYDUCK_ARM_H

#include <Arduino.h>

void on_touched(void *value) {
    auto touched = reinterpret_cast<uint8_t *>(value);
    *touched = 1;
}

class Arm {
public:
    explicit Arm(uint8_t top_sensor, uint8_t bottom_sensor, uint8_t out_a, uint8_t out_b) : top_sensor(top_sensor),
                                                                                            bottom_sensor(
                                                                                                    bottom_sensor),
                                                                                            out_a(out_a), out_b(out_b) {
        pinMode(top_sensor, INPUT_PULLUP);
        pinMode(bottom_sensor, INPUT_PULLUP);
        attachInterruptArg(top_sensor, on_touched, &top_touched, FALLING);
        attachInterruptArg(bottom_sensor, on_touched, &bottom_touched, FALLING);
        pinMode(out_a, OUTPUT);
        pinMode(out_b, OUTPUT);
        not_util = millis() + cool_down;
    }

    void start() {
        enabled = 1;
        update();
    }

    void stop() {
        enabled = 0;
        update();
    }

    uint8_t &getEnabled() {
        return enabled;
    }

    void setEnabled(uint8_t value) {
        enabled = value ? 1 : 0;
        update();
    }

    uint32_t &getCoolDown() {
        return cool_down;
    }

    void setCoolDown(uint32_t value) {
        cool_down = value;
    }

    void tick() {
        top_touched = digitalRead(top_sensor) ? 0 : 1;
        bottom_touched = digitalRead(bottom_sensor) ? 0 : 1;
        direction = nextDirection();
        update();
    }

private:
    uint8_t nextDirection() {
        if (top_touched && direction != 0) {
            top_touched = 0;
            resetNotUtil();
            return 0;
        } else if (bottom_touched && direction != 1) {
            bottom_touched = 0;
            resetNotUtil();
            return 1;
        }
        return direction;
    }

    void resetNotUtil() {
        not_util = millis() + cool_down;
    }

    void update() const {
        uint8_t en = enabled && (millis() >= not_util);
        digitalWrite(out_a, en ? direction : 0);
        digitalWrite(out_b, en ? direction ^ 0x1 : 0);
    }

private:
    uint32_t cool_down = 2000;
    uint32_t not_util;
    uint8_t top_sensor, bottom_sensor;
    uint8_t top_touched = 0, bottom_touched = 0;
    uint8_t out_a, out_b;
    uint8_t enabled = 0;
    uint8_t direction = 0; // 0 to lift left, 1 to lift right
};

#endif //PSYDUCK_ARM_H

#include "Psyduck.h"

#include "Common.h"
#include "Arm.h"
#include "Foot.h"
#include "Body.h"
#include "BLE.h"
#include "A2DP.h"
#include "Player.h"

#include "Characteristics.h"

void signal() {
    static uint8_t led = 0x0;
    digitalWrite(LED_BUILTIN, led);
    led ^= 0x1;
}

Psyduck::Psyduck() {
    pinMode(LED_BUILTIN, OUTPUT);
    a2dp = new BluetoothA2DPSink();
    player = new Player(BT_NAME, *a2dp, signal);
    arm = new Arm(RIGHT_ARM_TOP_SENSOR, RIGHT_ARM_BOTTOM_SENSOR, ARM_OUT_A, ARM_OUT_B);
    foot = new Foot(FOOT_OUT);
    body = new Body(*arm, *foot);
    ble = new BLE(BT_NAME);
}

Psyduck::~Psyduck() {
    delete player;
    delete a2dp;
    delete body;
    delete foot;
    delete arm;
    delete ble;
}

void Psyduck::start() {
    player->start();
    ble->addCharacteristic(new Mode(*body));
    ble->addCharacteristic(new ArmEnabled(*arm));
    ble->addCharacteristic(new ArmWait(*arm));
    ble->addCharacteristic(new FootEnabled(*foot));
    ble->addCharacteristic(new FootSpeed(*foot));
    ble->start();
}

void Psyduck::loop() {
    static uint32_t last = millis();
    arm->tick();
    body->notify(a2dp->get_audio_state() == ESP_A2D_AUDIO_STATE_STARTED);
    uint32_t elapsed = millis() - last;
    if (elapsed >= 1000) {
        signal();
        last = millis();
    }
}

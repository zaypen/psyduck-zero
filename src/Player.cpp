#include "Player.h"
#include "Common.h"

void on_connection_state_changed(esp_a2d_connection_state_t state, void *arg) {
    auto &a2dp = *reinterpret_cast<BluetoothA2DPSink *>(arg);
    if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
        a2dp.set_volume(a2dp.get_volume()); // FIXME: Fix uncontrolled volume
    }
}


Player::Player(const char *name, BluetoothA2DPSink &a2dp, void (*signal)()) : name(name), a2dp(a2dp) {
    i2s_pin_config_t my_pin_config = {
            .bck_io_num = I2S_BCK,
            .ws_io_num = I2S_WS,
            .data_out_num = I2S_DATA,
            .data_in_num = I2S_PIN_NO_CHANGE
    };
    a2dp.set_pin_config(my_pin_config);
    a2dp.set_on_data_received(signal);
    a2dp.set_on_connection_state_changed(on_connection_state_changed, &a2dp);
}

void Player::start() {
    a2dp.start(name);
}


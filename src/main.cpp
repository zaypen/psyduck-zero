#include <Arduino.h>
#include "Psyduck.h"

Psyduck *psyduck;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting");
    psyduck = new Psyduck();
    psyduck->start();
    Serial.println("Started");
}

void loop() {
    psyduck->loop();
    delay(50);
}

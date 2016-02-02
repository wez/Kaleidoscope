#include "Model01.h"
    KeyboardioScanner Model01::leftHand(0);
    KeyboardioScanner Model01::rightHand(3);

Model01::Model01(void) {

}

void Model01::setup(void) {
    Wire.begin();
}


void Model01::led_set_crgb_at(uint8_t i, cRGB crgb) {
}

void Model01::led_sync() {
}


void Model01::scan_matrix() {
    uint8_t key_data;

leftHand.sendLEDData();
// check if a key is ready, and if so, then read it.
key_t left_key = leftHand.readKey();
if (left_key.key>0) {
            handle_key_event(0,0, &key_data);
}


rightHand.sendLEDData();
// check if a key is ready, and if so, then read it.
key_t right_key = rightHand.readKey();
if (right_key.key>0) {
            handle_key_event(0,0, &key_data);
}




}


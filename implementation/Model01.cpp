#include "Model01.h"
    KeyboardioScanner Model01::leftHand(0);
    KeyboardioScanner Model01::rightHand(3);

Model01::Model01(void) {

}

void Model01::setup(void) {
    delay(5000);
    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    delay(1000);
    Wire.begin();
    Keyboard.println("USB OK");
}


void Model01::led_set_crgb_at(uint8_t i, cRGB crgb) {
}

void Model01::led_sync() {
}


void printBits(byte myByte){
 for(byte mask = 0x80; mask; mask >>= 1){
   if(mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
 }
}
void output_key_debug(uint8_t k) {

    uint8_t row = k & 0b0000011;
    uint8_t col = k & 0b0011100;
    col = col >> 2;

    Serial.print(" Row ");
    Serial.print(row);
    Serial.print(" Col ");
    Serial.print(col);
    if (0b0100000 & k ){
        Serial.print(" Pressed  ");
    } else {
        Serial.print(" Released ");
    }
    if (0b01000000 & k ){
        Serial.print("Key waiting ");
    } else {
        Serial.print("No waiting  ");
    }

    if (0b10000000 & k ){
        Serial.print("Event    ");
    } else {
        Serial.print("No event ");
    }




    printBits(k);
    Serial.println();

}
void Model01::scan_matrix() {
    uint8_t k = leftHand.readKeyRaw();
    if ( k >0 ) {

    Serial.print("left ");
    output_key_debug(k);
}
    k = rightHand.readKeyRaw();
    if ( k >0 ) {
    Serial.print("right ");
    output_key_debug(k);
}

}


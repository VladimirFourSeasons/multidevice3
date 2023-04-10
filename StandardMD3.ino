#include "MD3.h"

unsigned long time;

void setup() {
    StartDisplay();
}

void loop(){
    enc.tick();
    if (millis()-time>1000){
        PrintMainPage();
        time = millis();
    }
    if (enc.isSingle()){
        MainMenu();
    }
}

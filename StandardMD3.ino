#include "MD3.h"

void setup() {
    StartDisplay();
}
void loop(){
    bool stopMenu = false;
    while (!stopMenu){
        enc.tick();
        PrintMainPage();
        if (enc.isSingle()){
            stopMenu = MainMenu();
        }
    }
    
}

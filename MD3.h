#include "Settings.h"

void checkTurning(uint8_t *pointer);
void PrintPointer(int pointer);
void PrintNumString(uint8_t num);
void PrintMainMenuPage(uint8_t counterMainMenu);
bool checkPressing(uint8_t pointer);



// Функция для подготовки дисплея к работе
void StartDisplay(){
    lcd.begin(); // Инциализация дисплея 
    lcd.setContrast(255); // Макс. яркость 
    lcd.clearDisplay();
    lcd.display();
    }
/////////////////////////////////////



// Стартовая страница
void PrintMainPage(){
    lcd.clearDisplay();
    lcd.setCursor(0,0);
    lcd.println("Hello");
    lcd.println(millis());
    lcd.display();
}
// Функция отображения метеоданных

////////////////////////////////////


// Главное меню
void MainMenu(){
    bool stopMenu = false;
    uint8_t counterMainMenu = 1;
    PrintMainMenuPage(counterMainMenu);
    delay(100);
    while(!stopMenu){
        enc.tick();
        stopMenu = checkPressing (counterMainMenu);
        checkTurning(&counterMainMenu);
        if (enc.isTurn()){
            PrintMainMenuPage (counterMainMenu);
        }
    }
}
// Страница отображения меню
void PrintMainMenuPage(uint8_t counterMainMenu){
    lcd.clearDisplay();
    //lcd.println(counterMainMenu);
    PrintNumString(0);
    for(uint8_t stringNumber = 1; stringNumber < LINES+1;stringNumber++){
        PrintNumString(counterMainMenu > LINES ? stringNumber + (counterMainMenu - LINES) : stringNumber);
        }
    PrintPointer(constrain (counterMainMenu, 1, LINES));
    lcd.display();
}

// Печать строки пункта меню

void PrintNumString(uint8_t num){
    char buffer[14]; //Максимальная длина строки
    int ptr = pgm_read_word(&(names[num]));
    int i = 0;
    do {
        buffer[i] = (char)(pgm_read_byte(ptr++));
        } while (buffer[i++] != NULL);
    lcd.println(buffer);
}

// Печать указателя меню

void PrintPointer(int pointer) {
    lcd.drawBitmap(0, 8 * pointer, marker, 8, 7, BLACK);
    }

// Функция выполняемая при выборе пункта меню
bool Back(void){
    lcd.clearDisplay();
    lcd.display();
    return true;
}
void func1(void) { 
    lcd.clearDisplay(); 
    }

// Функция обработки нажатия кнопки
bool checkPressing(uint8_t counter){
    bool stopMenu = false;
    enc.tick();
    if (enc.isSingle()) {
        switch (counter) {
            case 1: 
stopMenu = Back();break;
            case 2: break; 
            case 3: break; 
            case 4: break; 
            case 5: break; 
            case 6: break; 
            case 7: break; 
        }
        lcd.clearDisplay();
        if(stopMenu) {return stopMenu;}
        PrintMainMenuPage (counter);
        PrintPointer(counter);
        lcd.display();
        
        }
    return stopMenu;
}

// Проверка поворота энкодера
void checkTurning(uint8_t *counter){
    if (enc.isLeft()) {
       *counter = constrain(*counter - 1, 1, ITEMS - 1);
        } 
    if (enc.isRight()){ 
       *counter = constrain(*counter + 1, 1, ITEMS - 1); 
        } 
}

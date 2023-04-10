#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <GyverEncoder.h>

// LCD pins
#define CLK_L 4
#define DIN 5
#define DC 6
#define CE 7
#define RST 8
// Encoder pins
#define CLK_E 15
#define DT 14
#define SW 9
// I2C,SPI
#define SDA A4 //SDA
#define SCL A5 //SCL
#define MISO 12
#define MOSI 11
#define SCK 13
#define SS 10
// Меню
#define ITEMS 10 // Общее кол во пунктов 
#define LINES 4 // Количество отображаемых строк

bool* enableMainMenu;

// Инициализация периферии
Adafruit_PCD8544 lcd = Adafruit_PCD8544(CLK_L,DIN,DC,CE,RST);
Encoder enc(CLK_E,DT , SW, TYPE2);
// Битмап с картинкой стрелочки
const unsigned char marker[] PROGMEM = {
    B00110000,
    B00011000,
    B11111100,
    B11111110,
    B11111100,
    B00011000,
    B00110000
    };

// Имена пунктов меню
const char i0[] PROGMEM = 
"     MENU    "; 
const char i1[] PROGMEM = 
"  Back       "; 
const char i2[] PROGMEM = 
"  Parameter 2"; 
const char i3[] PROGMEM = 
"  Parameter 3"; 
const char i4[] PROGMEM = 
"  Parameter 4"; 
const char i5[] PROGMEM = 
"  Parameter 5"; 
const char i6[] PROGMEM = 
"  Parameter 6"; 
const char i7[] PROGMEM = 
"  Parameter 7"; 
const char i8[] PROGMEM = 
"  Parameter 8"; 
const char i9[] PROGMEM = 
"  Parameter 9"; 

const char* const names[10] PROGMEM = 
{ i0, i1, i2, i3, i4, i5, i6, i7, i8, i9 }; 


static int pointer = 0; // указатель меню

// Функция для вывода на дисплей указателя меню
void printPointer(int pointer) {
    lcd.drawBitmap(0, 8 * pointer, marker, 8, 7, BLACK);
    }

// Функция для печати строки из PROGMEM
void printMenuItem(int num) {
    char buffer[14]; //Максимальная длина строки
    int ptr = pgm_read_word(&(names[num]));
    int i = 0;
    do {
        buffer[i] = (char)(pgm_read_byte(ptr++));
        } while (buffer[i++] != NULL);
    lcd.println(buffer);
    }

// Функция отображения меню
void showMenu(int pointer) {
    lcd.clearDisplay();
    for (int i = 0; i < LINES +1; i++) {
            printMenuItem(pointer > LINES ? i + (pointer - LINES) : i);
        }
    printPointer(constrain(pointer, 0, LINES));
    lcd.display();
    }

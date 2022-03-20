#include <Keypad.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

const byte ROWS = 6;
const byte COLS = 5;
char keys[ROWS][COLS] = {
{'-','2','1','d','c'},
{'a','-','-','-','0'},
{'-','6','5','f','b'},
{'-','8','7','e','g'},
{'-','l','9','-','o'},
{'-','4','3','h','-'},
};
byte rowPins[ROWS] = {16, 18, 33, 35, 37, 39}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {12, 11, 9, 7, 5}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;


void setup() {
	Serial.begin();
	Serial.print("Setup");
	
	loopCount = 0;
	startTime = millis();
	msg = "";

    kpd.setScanTime(4);

    /*for(uint8_t i=0; i<COLS; i++) {
		digitalWrite(colPins[i],HIGH);
		pinMode(colPins[i],INPUT);
    }

    for(uint8_t i=0; i<ROWS; i++) {
		pinMode(rowPins[i],INPUT_PULLUP);
    }

    pinMode(9, OUTPUT);
    digitalWrite(9, LOW);*/

	Keyboard.begin();
	USB.begin();
}


void loop() {
    //Serial.println(digitalRead(37));
    loopCount++;
    if((millis()-startTime)>5000) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys()) {
        for (int i=0; i<LIST_MAX; i++) {
            if ( kpd.key[i].stateChanged ) {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);
            }
        }
    }
}
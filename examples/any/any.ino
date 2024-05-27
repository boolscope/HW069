/*
HW-069
===========
ESP32 | HW-069
3v3 -> VCC
GND -> GND
P18 -> CLK
P19 -> DIO

P17 -> Button -> GND
*/
#include <hw069.h>

#define BUTTON_PIN 17

#define CLK_PIN 18
#define DIO_PIN 19
HW069 display(CLK_PIN, DIO_PIN);

void setup() {
    // Set the button pin as input with pull-up.
    // The button is connected to GND, so when pressed it will read LOW.
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    // The snake animation.
    for (int i = 10; i < 50; i++) {
        display.setSnake(i, 4);
        delay(100);
    }

    // Test the display with some Float values.
    const float floatTestArray[] = {1.0, 5.1, 99.35, 1.17, 77.7, 73.77, 788.188};
    for (int i = 0; i < sizeof(floatTestArray) / sizeof(floatTestArray[0]); i++) {
        display.setFloat(floatTestArray[i]);
        while (digitalRead(BUTTON_PIN) == HIGH) {}
        delay(10);
    }

    // Test the display with some Int values.
    const int intTestArray[] = {1, 5, 99, 121, 777, 7377, 88188};
    for (int i = 0; i < sizeof(intTestArray) / sizeof(intTestArray[0]); i++) {
        display.setInt(intTestArray[i]);
        while (digitalRead(BUTTON_PIN) == HIGH) {}
        delay(10);
    }

    // Test the display with some String values.
    const char* strTestArray[] = {
        "Er:36", "On:21", "7377", "SIZE",
        ":36", "On:", "  :On", "_-:-_",
        "S", "D", "L", "N", "P", "H", "U", "J", "h", "u", "j",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "A", "a", "B", "b", "C", "c", "D", "d", "E", "e",
        "F", "f", "S", "s", "L", "l", "-", "O", "o", "N", "n",
        ":0", ":1", ":2", ":3", ":4", ":5", ":6", ":7", ":8", ":9",
        ":A", ":a", ":B", ":b", ":C", ":c", ":D", ":d", ":E", ":e",
        ":F", ":f", ":S", ":s", ":L", ":l", ":O", ":o", ":N", ":n",
        "0:", "1:", "2:", "3:", "4:", "5:", "6:", "7:", "8:", "9:",
        "A:", "a:", "B:", "b:", "C:", "c:", "D:", "d:", "E:", "e:",
        "F:", "f:", "S:", "s:", "L:", "l:", "O:", "o:", "N:", "n:",
        "10:", "1:1", "2 :2", "3: L", ":O", ": O"
    };
    for (int i = 0; i < sizeof(strTestArray) / sizeof(strTestArray[0]); i++) {
        display.setStr(strTestArray[i]);
        while (digitalRead(BUTTON_PIN) == HIGH) {}
        delay(10);
    }
}
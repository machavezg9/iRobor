/*
Object-Oriented Programming Example

Hardware:
1* Arduino Uno board (Any Arduino board will do)
1* breadboard
4* LEDs (any color you want)
4* 220 Ohm resistors (one for each LED)
1* push button
1* 10k Ohm resistor (for the push button)
A few male-to-male wires

Wiring:
See OOP_Example_Circuit.jpg

Intention:
The goal of this tutorial will be to turn on LED 1 & 3, and turn off LED 2 & 4 when the button is pressed.
When the button is not pressed we’ll do the opposite – turn off LED 1 & 3, and turn on LED 2 & 4.

*/

#include "Led.h"
#include "Button.h"

#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12

#define BUTTON_PIN 5

Led led1(LED_1_PIN);
Led led2(LED_2_PIN);
Led led3(LED_3_PIN);
Led led4(LED_4_PIN);
Button button1(BUTTON_PIN);

void setup() { }

void loop() {
  if (button1.isPressed()) {
    led1.on();
    led2.off();
    led3.on();
    led4.off();
  }
  else {
    led1.off();
    led2.on();
    led3.off();
    led4.on();
  }
}

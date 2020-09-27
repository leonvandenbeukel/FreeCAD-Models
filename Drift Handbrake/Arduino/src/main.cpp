/*

  Emulate a joystick if switch is 0 and then set throttle 
  otherwise emulate a keyboard and send a 'space' key.

  Works with an Arduino Leonardo only

*/
#include <Arduino.h>
#include <Joystick.h>
#include "Keyboard.h"

int xPin = A1;
int buttonPin = 9;

int xPosition = 0;
int buttonState = 0;

Joystick_ Joystick;

void setup()
{
  Serial.begin(9600);

  pinMode(xPin, INPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  delay(100);

  buttonState = digitalRead(buttonPin);
  delay(10);

  Serial.print("ButtonState: ");
  Serial.println(buttonState);

  if (buttonState > 0)
  {
    Joystick.end();
    Keyboard.begin();
  }
  else
  {
    Keyboard.end();
    Joystick.setThrottleRange(0, 255);
    Joystick.begin();
  }
}

void loop()
{
  xPosition = analogRead(xPin);

  int mapped = map(xPosition, 511, 1023, 0, 255);

  if (buttonState > 0 && mapped > 100)
  {
    Keyboard.press(' ');
    delay(100);
    Keyboard.releaseAll();
  }
  else
  {
    Joystick.setThrottle(mapped);
  }

}

#include "Button.h"

#define RESTROOM_LIGHT 7      // Свет в сан. узле -- 7 пин

Button restroomSwitch(2); // Выключатель в сан. узле -- 2-й пин

// funtions that will be called whenever one of the XB(s)P's event occurs

void on_release() {
    Serial.print(String("button released immediately: ") + restroomSwitch.gap() + String(" milliseconds\n"));
}
void on_press() {
    Serial.print(String("button pressed immediately: ") + restroomSwitch.gap() + String(" milliseconds\n"));
}
void on_long_release() {
    Serial.print(String("button released after long time: ") + restroomSwitch.gap() + String(" milliseconds\n"));
    digitalWrite(RESTROOM_LIGHT, LOW);
}
void on_long_press() {
    Serial.print(String("button pressed after long time: ") + restroomSwitch.gap() + String(" milliseconds\n"));
    digitalWrite(RESTROOM_LIGHT, HIGH);
}
void on_bounced_release() {
    Serial.print(String("button released after a bounce: ") + restroomSwitch.gap() + String(" milliseconds\n"));
}
void on_bounced_press() {
    Serial.print(String("button pressed after a bounce: ") + restroomSwitch.gap() + String(" milliseconds\n"));
}


void setup() {
  pinMode(RESTROOM_LIGHT, OUTPUT);
  Serial.begin(9600);
  restroomSwitch.on_release(on_release);                      // on NBP (if not set nothing will be done)
  restroomSwitch.on_press(on_press);                          // on NBsP (if not set nothing will be done)
  restroomSwitch.on_long_press(on_long_press);                // on LBsP (if not set, on_press will be used for on_long_press events)
  restroomSwitch.on_long_release(on_long_release);            // on LBP (if not set, on_release will be used for on_long_release events)
  restroomSwitch.on_bounced_release(on_bounced_release);      // on BBP (junk, if not set nothing will be done)
  restroomSwitch.on_bounced_press(on_bounced_press);          // on BBsP (junk, if not set nothing will be done)
}

void loop() {
  restroomSwitch.init();
  Serial.print(restroomSwitch.timePressed() + String(" milliseconds\n"));
  //Serial.print(button.gap() + String(" milliseconds\n"));
  delay(1000);
}

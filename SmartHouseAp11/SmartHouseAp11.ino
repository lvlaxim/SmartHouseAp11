#include "Button.h"

#define RESTROOM_LIGHT_FORGOTTEN 8000       // Время в миллисекундах, после прохождения которого считается, что свет в сан. узле забыли выключить.
#define RESTROOM_VENT_START 4000            // Время, через которое после включения света в сан.узле, должна включиться вентиляция.
#define RESTROOM_VENT_AFTER 3000            // Время, через которое выключается вентиляция после выключения.

#define RESTROOM_VENT 6                     // Вентиляция в сан. узле -- 6 пин
#define RESTROOM_LIGHT 7                    // Свет в сан. узле -- 7 пин

Button restroomSwitch(2); // Выключатель в сан. узле -- 2-й пин

// funtions that will be called whenever one of the XB(s)P's event occurs

void on_long_release() {
    Serial.print(String("button released after long time: ") + restroomSwitch.gap() + String(" milliseconds\n"));
    digitalWrite(RESTROOM_LIGHT, LOW);
}
void on_long_press() {
    Serial.print(String("button pressed after long time: ") + restroomSwitch.gap() + String(" milliseconds\n"));
    digitalWrite(RESTROOM_LIGHT, HIGH);
}


void setup() {
  pinMode(RESTROOM_LIGHT, OUTPUT);
  pinMode(RESTROOM_VENT, OUTPUT);
  Serial.begin(9600);
  restroomSwitch.on_long_press(on_long_press);                // on LBsP (if not set, on_press will be used for on_long_press events)
  restroomSwitch.on_long_release(on_long_release);            // on LBP (if not set, on_release will be used for on_long_release events)
}

void loop() {
  restroomSwitch.init();

  // Включаем вентиляцию в сан.узле если прошло время RESTROOM_VENT_START, но еще не настало время "забытия"
  if((restroomSwitch.timePressed() >= RESTROOM_VENT_START) && (restroomSwitch.timePressed() < RESTROOM_LIGHT_FORGOTTEN)) digitalWrite(RESTROOM_VENT, HIGH);
  
  // Если прошло время RESTROOM_LIGHT_FORGOTTEN значит про сан узел забыли -- выключаем всё.
  if(restroomSwitch.timePressed() >= RESTROOM_LIGHT_FORGOTTEN){
    digitalWrite(RESTROOM_LIGHT, LOW);
    digitalWrite(RESTROOM_VENT, LOW);
  }

  // Включенная вентиляция должна отработать еще RESTROOM_VENT_AFTER после выключения света
  if((restroomSwitch.timeReleased() >= 1) && (restroomSwitch.timeReleased() >= RESTROOM_VENT_AFTER) && (restroomSwitch.gap() >= RESTROOM_VENT_START)){
    digitalWrite(RESTROOM_VENT, LOW);
  }
  
  delay(500);
}

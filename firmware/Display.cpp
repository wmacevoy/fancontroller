#include <Arduino.h>
#include "ConfigEditor.h"

void Display::setup() {
  state = 0;
}

static double t(double tempC) {
  if (config.mode == 'C') return tempC;
  return ((212.0-32.0)/100.0)*tempC+32.0;
}

void Display::loop() {
  switch(state) {
  case 0:
    lcd.gotoXY(0,0);
    lcd.print(temp()); lcd.print(config.mode);
    lcd.gotoXY(0,1);
    lcd.print(fan*100.0); lcd.print("%");
    break;
  case 1:
    lcd.print("FAN ON TEMP ("); lcd.print(config.mode); lcd.print(")");
    edit=&config.fanOnTempC;
    lcd.gotoXY(0,1);
    lcd.print(config.fanOnTempC);
    break;

  }


}

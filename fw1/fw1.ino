#include <OneWire.h>
#include <DallasTemperature.h>
#include <AStar32U4.h>

#include "Temp.h"
#include "Config.h"

Config config;
const uint8_t oneWireBus = 2;
const uint8_t resolution = 12;

Stream &out = Serial;
const long baud = 115200L;

Temp temp(config,oneWireBus,resolution);

uint32_t timeout = 0;

AStar32U4LCD lcd;

void setup() {
     Serial.begin(baud);
     while (!Serial) ; 
}

void loop() {
  temp.loop();
  if (int32_t(millis()-timeout) > 0) {
    timeout += 1000;
    out.print(temp.valid());
    out.print(" ");
    out.print(temp.current());
    out.println();
    lcd.clear();
    lcd.gotoXY(0,1);
    lcd.print(temp);
  }
}

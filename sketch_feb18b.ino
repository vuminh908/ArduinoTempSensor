#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int r = 255;
const int g = 255;
const int b = 125;

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0
const float adjust = 1.525;       // Adjustment for using sensor at 5V instead of 3.3V

int timestamp = 0;

void setup()
{
    Serial.begin(9600);

    timestamp = millis();

    lcd.begin(16, 2);
    lcd.setRGB(r, g, b);
    lcd.print("Temperature:");
    delay(1000);
}

void loop()
{
    int a = analogRead(pinTempSensor);

    //Serial.print("raw value = ");
    //Serial.println((float)a/adjust);
    
    float R = (1023.0/((float)a/adjust))-1.0;
    R = ((float)R0)*R;

    float temperature = (1.0/((log(R/((float)R0))/B)+(1/298.15)))-273.15; // convert to temperature via datasheet

    if(millis() - timestamp > 1000)
    {
        //Serial.print("temperature = ");
        Serial.println(temperature);
      
        lcd.setCursor(0, 1);
        lcd.print(temperature);
        lcd.setCursor(7, 1);
        lcd.print("C");
        timestamp = millis();
    }

    delay(100);
}

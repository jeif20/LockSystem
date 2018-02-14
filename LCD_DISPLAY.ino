/**
 * I2C/IIC LCD Serial Adapter Module Example
 * Tutorial by http://mklec.com
 * 
 * Instructions at http://blog.mklec.com/how-to-use-iici2c-serial-interface-module-for-1602-lcd-display
 *
 * This uses the Liquid Crystal library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads GNU General Public License, version 3 (GPL-3.0)
 * Pin Connections: 
 *      SCL = A5
 *      SDA = A4
 *      VCC = 5V
 *      GND = GND
 */
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x3F,2,1,0,4,5,6,7); // 0x3F is the I2C bus address for an unmodified module OR 0X27 for others

void setup()
{
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH); // NOTE: You can turn the backlight off by setting it to LOW instead of HIGH
    lcd.begin(16, 2);
    lcd.clear();
}

void loop()
{
    lcd.setCursor(0,0);
    lcd.print(" HELLO EVERYONE ");
    lcd.setCursor(0,1);
    lcd.print(" THIS IS A TEST  ");
    delay(100);
}

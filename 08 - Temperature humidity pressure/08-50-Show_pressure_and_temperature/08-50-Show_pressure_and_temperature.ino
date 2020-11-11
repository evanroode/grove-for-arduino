/*  Arduino for Beginners with Grove
 *
 * This code is part of a course from Tech Explorations.
 * For information about this course, please see
 *
 * https://techexplorations.com/so/grove/
 *
 * For information on hardware components and the wiring needed to
 * run this sketch, please see the relevant lecture in the course.
 *
 *
 *  Created by Peter Dalmaris
 *
 */

#include <U8g2lib.h>  // Install the U8g2 by searching it by name in the Library Manager.
                      // Documentation: https://github.com/olikraus/u8g2/wiki/u8g2reference
#include <Wire.h>
#include "Seeed_BME280.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);

BME280 bme280;

float temp = 0, pres = 0;

void setup() {
  if(!bme280.init()){
    Serial.println("Device error!");
  }

  u8g2.setBusClock(100000);   // Needed for Arduino Uno
  u8g2.begin();
}

void loop() {
  temp = bme280.getTemperature();
  pres = bme280.getPressure();
  print_bme280_readings();
  delay(2000);
}

void print_bme280_readings()
{
  u8g2_uint_t x_position_temp = 0;
  u8g2_uint_t y_position_temp = 22;
  int font_height = 18;

  u8g2_uint_t x_position_pres = 0;
  u8g2_uint_t y_position_pres = 42;

  char buffer_pres[10];
  dtostrf(pres, 4, 2, buffer_pres);

  char buffer_temp[10];
  dtostrf(temp, 4, 2, buffer_temp);
  u8g2.firstPage();           // Using the firstPage / nextPage method.
                              // Advantage: much faster then the partial redraw method.
                              // Dissadvantage: must reset the whole screen every time.
  do {
      u8g2.setFont(u8g2_font_logisoso18_tf);
      u8g2.setDrawColor(1);

      // Print temperature value
      u8g2.drawStr(x_position_temp, y_position_temp, buffer_temp);
      u8g2.setCursor(x_position_temp + 95, y_position_temp);
      u8g2.print(char(0xB0));   // This or one of the next two lines can print the degrees symbol
      u8g2.print("C");

      // Print pressure value
      u8g2.drawStr(x_position_pres, y_position_pres, buffer_pres);
      u8g2.setCursor(x_position_pres + 95, y_position_pres);
      u8g2.print("Pa");

      // Print a text label
      u8g2.setFont(u8g2_font_tenthinnerguys_t_all);
      u8g2.drawStr(0, 60,  "BME280");

  } while ( u8g2.nextPage() );

}

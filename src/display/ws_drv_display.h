/*!
 * @file ws_drv_display.h
 *
 * Wippersnapper display
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Copyright (c) Brent Rubell 2023 for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */
#ifndef WIPPERSNAPPER_DISPLAY_H
#define WIPPERSNAPPER_DISPLAY_H

#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <Adafruit_ST7789.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <lvgl.h>

struct displayConfig {
  char driver[10];
  int width;
  int height;
  int rotation;
  bool isSPI;
  bool isI2C;
  uint8_t pinCS;
  uint8_t pinDC;
  uint8_t pinMOSI;
  uint8_t pinSCK;
  uint8_t pinRST;
};

/***************************************************************************/
/*!
    @brief  Display driver for LVGL and LVGL_Glue in WipperSnapper.
*/
/***************************************************************************/
class ws_drv_display {
public:
  ws_drv_display(){};
  ws_drv_display(displayConfig config);
  ws_drv_display(uint8_t TFT_CS, uint8_t TFT_DC, uint8_t TFT_RESET);
  ~ws_drv_display();

  bool begin();
  void setResolution(uint16_t displayWidth, uint16_t displayHeight);
  void setRotation(uint8_t rotationMode);
  void enableLogging();

private:
  Adafruit_LvGL_Glue _glue;
  Adafruit_ST7789 *_tft_st7789 = nullptr;
  uint16_t _displayWidth;
  uint16_t _displayHeight;
  uint8_t _displayRotationMode;
};

#endif // WIPPERSNAPPER_DISPLAY_H
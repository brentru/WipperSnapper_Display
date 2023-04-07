/*!
 * @file ws_drv_display.cpp
 *
 * Wippersnapper LVGL Display Driver
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
#include "ws_drv_display.h"

/**************************************************************************/
/*!
    @brief    Callback for LVGL logging through USB serial
    @param    buf
              Data to write out to serial.
*/
/**************************************************************************/
static void my_log_cb(const char *buf) { Serial.printf(buf); }

/**************************************************************************/
/*!
    @brief    Creates a new WipperSnapper display driver object.
    @param    TFT_CS
              TFT CS pin.
    @param    TFT_DC
              TFT DC pin.
    @param    TFT_RESET
              TFT RESET pin.
*/
/**************************************************************************/
ws_drv_display::ws_drv_display(uint8_t TFT_CS, uint8_t TFT_DC,
                               uint8_t TFT_RESET) {
  // TODO: We'll probably need to detect tft display types somehow, not just
  // ST7789
  _tft_st7789 = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RESET);
}

/**************************************************************************/
/*!
    @brief    Deletes a new WipperSnapper display driver object.
*/
/**************************************************************************/
ws_drv_display::~ws_drv_display() { delete _tft_st7789; }

/**************************************************************************/
/*!
    @brief    Sets the display resolution, must be called BEFORE begin()!
    @param    displayWidth
              The width of the display, in pixels.
    @param    displayHeight
              The height of the display, in pixels.
*/
/**************************************************************************/
void ws_drv_display::setResolution(uint16_t displayWidth,
                                   uint16_t displayHeight) {
  _displayWidth = displayWidth;
  _displayHeight = displayHeight;
}

/**************************************************************************/
/*!
    @brief    Enables LVGL logging using the usb serial. Must be called
              AFTER calling Serial.begin().
*/
/**************************************************************************/
void ws_drv_display::enableLogging() { lv_log_register_print_cb(my_log_cb); }

/**************************************************************************/
/*!
    @brief    Begins the display and the lvgl_glue driver.
    @returns  True if LVGL_Glue began successfully, False otherwise.
*/
/**************************************************************************/
bool ws_drv_display::begin() {
  _tft_st7789->init(_displayWidth, _displayHeight);

  // TODO: Detect FH!
  // funhouse-specific initialization
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // Initialize glue, passing in address of display
  // TODO: Remove hardcoded _tft_st7789
  LvGLStatus status = _glue.begin(_tft_st7789);
  if (status != LVGL_OK) {
    Serial.printf("LVGL_Glue error %d\r\n", (int)status);
    return false;
  }
  return true;
}
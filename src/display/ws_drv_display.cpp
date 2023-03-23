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

/* Logger for USB serial */
void my_log_cb(const char *buf) { Serial.printf(buf); }

ws_drv_display::ws_drv_display() {
  // TODO
}

ws_drv_display::ws_drv_display(uint8_t TFT_CS, uint8_t TFT_DC,
                               uint8_t TFT_RESET) {
  // TODO: We'll probably need to detect tft display types, not just ST7789
  _tft_st7789 = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RESET);
}

ws_drv_display::~ws_drv_display() { delete _tft_st7789; }

void ws_drv_display::setResolution(uint16_t displayWidth,
                                   uint16_t displayHeight) {
  _displayWidth = displayWidth;
  _displayHeight = displayHeight;
}

void ws_drv_display::enableLogging() { lv_log_register_print_cb(my_log_cb); }

void ws_drv_display::begin() {
  _tft_st7789->init(_displayWidth, _displayHeight);

  // funhouse-specific initialization
  // TODO: Detect FH!
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // Initialize glue, passing in address of display
  // TODO: Remove hardcoded _tft_st7789
  LvGLStatus status = _glue.begin(_tft_st7789);
  if (status != LVGL_OK) {
    Serial.printf("Glue error %d\r\n", (int)status);
    for (;;)
      ;
  }
}
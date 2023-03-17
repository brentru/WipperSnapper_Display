#include <Arduino.h>
// Minimal "Hello" example for LittlevGL on Adafruit Funhouse. Requires
// LittlevGL, Adafruit_LvGL_Glue, Adafruit_GFX and Adafruit_ST7735
// libraries.

// Prior Adafruit_LvGL_Glue users: see hello_changes example for updates!

#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <Adafruit_ST7789.h>
#include <lvgl.h>

// FA symbol glyphs
#define SYMBOL_CODE "\xEF\x87\x89"
#define SYMBOL_WIFI "\xEF\x87\xAB"
#define SYMBOL_TURTLE30PX "\xEF\x9C\xA6"
#define SYMBOL_CLOUD "\xEF\x83\x82"
#define SYMBOL_CHECKMARK "\xEF\x81\x98"
#define SYMBOL_ERROR_TRIANGLE "\xEF\x81\xB1"

// images
LV_IMG_DECLARE(ws_icon_100px);
LV_IMG_DECLARE(ws_logo_200px);

// FA symbol properties
extern lv_font_t errorTriangle, circle_30px, cloud_30px, turtle_30px, wifi_30px,
    file_code;

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RESET);
Adafruit_LvGL_Glue glue;

void setup(void) {
  Serial.begin(115200);

  // Initialize display BEFORE glue setup
  tft.init(240, 240);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // Initialize glue, passing in address of display
  LvGLStatus status = glue.begin(&tft);
  if (status != LVGL_OK) {
    Serial.printf("Glue error %d\r\n", (int)status);
    for (;;)
      ;
  }

  // lvgl_setup(); // Call UI-building function above
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}
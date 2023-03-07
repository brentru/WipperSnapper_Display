#include <Arduino.h>
// Minimal "Hello" example for LittlevGL on Adafruit Funhouse. Requires
// LittlevGL, Adafruit_LvGL_Glue, Adafruit_GFX and Adafruit_ST7735
// libraries.

// Prior Adafruit_LvGL_Glue users: see hello_changes example for updates!

#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <lvgl.h>
#include <Adafruit_ST7789.h>

//extern lv_font_t turtle;
extern lv_font_t turtle2;
#define TURTLE_SYMBOL "\xEF\x9C\xA6"

#define BIRD_SYMBOL "\xEE\x91\xA9"

Adafruit_ST7789    tft(TFT_CS, TFT_DC, TFT_RESET);
Adafruit_LvGL_Glue glue;

// This example sketch's LittlevGL UI-building calls are all in this
// function rather than in setup(), so simple programs can just
// copy-and-paste this sketch as a starting point, then embellish here:
void lvgl_setup(void) {
 // make background black
 lv_obj_set_style_bg_color(lv_scr_act(), LV_COLOR_MAKE(0, 0, 0), LV_STATE_DEFAULT);

 lv_obj_t *label = lv_label_create(lv_scr_act());

  static lv_style_t style;
  lv_style_init(&style);
  //lv_style_set_text_font(&style, &turtle);
  lv_style_set_text_font(&style, &turtle2);
  lv_obj_add_style(label, &style, LV_PART_MAIN);

  // Turtle font
  lv_label_set_text(label, TURTLE_SYMBOL);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_t *labelAIO = lv_label_create(lv_scr_act());
  lv_label_set_text(labelAIO, "WipperSnapper");
  lv_obj_align(labelAIO, LV_ALIGN_TOP_MID, 0, 0);
}

void setup(void) {
  Serial.begin(115200);

  // Initialize display BEFORE glue setup
  tft.init(240, 240);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // Initialize glue, passing in address of display
  LvGLStatus status = glue.begin(&tft);
  if(status != LVGL_OK) {
    Serial.printf("Glue error %d\r\n", (int)status);
    for(;;);
  }

  lvgl_setup(); // Call UI-building function above
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}